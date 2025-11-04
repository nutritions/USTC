import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
import matplotlib.pyplot as plt
from typing import List

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

class Tokenizer:
    def __init__(self, dataPath: str):
        with open(dataPath, "r", encoding="utf-8") as f:
            self.dataset = f.read()
        self.generate_vocabulary()

    def generate_vocabulary(self):
        self.char2index = {char: idx for idx, char in enumerate(sorted(set(self.dataset)), start=1)}
        self.char2index['<start>'] = 0  # 句子开始符号
        self.index2char = {idx: char for char, idx in self.char2index.items()}

    def encode(self, sentence: str) -> torch.Tensor:
        return torch.tensor([self.char2index.get(char, 0) for char in sentence], dtype=torch.long)

    def decode(self, tokens: torch.Tensor) -> str:
        return ''.join([self.index2char.get(token.item(), '') for token in tokens])

class ShakespeareDataset(Dataset):
    def __init__(self, filepath, tokenizer, chunk_size):
        self.tokenizer = tokenizer
        with open(filepath, 'r', encoding='utf-8') as file:
            text = file.read()
        self.encoded = self.tokenizer.encode(text)
        self.chunk_size = chunk_size  

    def __len__(self):
        return len(self.encoded) - self.chunk_size

    def __getitem__(self, idx):
        chunk = self.encoded[idx:idx + self.chunk_size]
        label = self.encoded[idx + 1:idx + 1 + self.chunk_size]
        return chunk, label

def create_dataloader(filepath, tokenizer, chunk_size, batch_size, shuffle=True):
    dataset = ShakespeareDataset(filepath, tokenizer, chunk_size)
    train_dataset, val_dataset = torch.utils.data.random_split(dataset, [int(len(dataset) * 0.8), len(dataset) - int(len(dataset) * 0.8)])
    train_dataloader = DataLoader(train_dataset, batch_size=batch_size, shuffle=shuffle)
    val_dataloader = DataLoader(val_dataset, batch_size=batch_size, shuffle=shuffle)
    return train_dataloader, val_dataloader

class HeadAttention(nn.Module):
    def __init__(self, seq_len: int, embed_size: int, head_size: int):
        super().__init__()
        self.head_size = head_size
        self.to_q = nn.Linear(embed_size, head_size, bias=False)
        self.to_k = nn.Linear(embed_size, head_size, bias=False)
        self.to_v = nn.Linear(embed_size, head_size, bias=False)
        self.register_buffer("tril", torch.tril(torch.ones(seq_len, seq_len)))

    def forward(self, inputs):
        B, T, C = inputs.shape
        q = self.to_q(inputs)  # (B, T, head_size)
        k = self.to_k(inputs)  # (B, T, head_size)
        v = self.to_v(inputs)  # (B, T, head_size)
        
        wei = torch.einsum('bth,bsh->bts', q, k) / self.head_size ** 0.5
        wei = wei.masked_fill(self.tril[:T, :T] == 0, float('-inf'))
        wei = F.softmax(wei, dim=-1)
        out = torch.einsum('bts,bsh->bth', wei, v)
        return out

class MultiHeadAttention(nn.Module):
    def __init__(self, n_heads: int, head_size: int, seq_len: int, embed_size: int):
        super().__init__()
        self.heads = nn.ModuleList([HeadAttention(seq_len, embed_size, head_size) for _ in range(n_heads)])
        self.proj = nn.Linear(n_heads * head_size, embed_size)

    def forward(self, inputs):
        out = torch.cat([head(inputs) for head in self.heads], dim=-1)
        return self.proj(out)

class Expert(nn.Module):
    def __init__(self, embed_size: int):
        super().__init__()
        self.fc1 = nn.Linear(embed_size, 4 * embed_size)
        self.fc2 = nn.Linear(4 * embed_size, embed_size)

    def forward(self, inputs):
        x = F.relu(self.fc1(inputs))
        return self.fc2(x)

class TopkRouter(nn.Module):
    def __init__(self, embed_size, num_experts, active_experts):
        super().__init__()
        self.num_experts = num_experts
        self.active_experts = active_experts
        self.linear = nn.Linear(embed_size, num_experts)

    def forward(self, inputs):
        scores = self.linear(inputs)
        topk_scores, indices = torch.topk(scores, self.active_experts, dim=-1)
        mask = torch.zeros_like(scores).scatter_(-1, indices, topk_scores)
        router_output = F.softmax(mask, dim=-1)
        return router_output, indices

class SparseMoE(nn.Module):
    def __init__(self, embed_size: int, num_experts: int, active_experts: int):
        super().__init__()
        self.experts = nn.ModuleList([Expert(embed_size) for _ in range(num_experts)])
        self.router = TopkRouter(embed_size, num_experts, active_experts)

    def forward(self, inputs):
        router_output, indices = self.router(inputs)
        B, T, E = router_output.size()
        expert_outputs = torch.zeros(B, T, E, inputs.size(-1), device=inputs.device)
        for i in range(self.router.num_experts):
            expert_outputs[:, :, i, :] = self.experts[i](inputs)
        final_output = torch.einsum('bte,btei->bti', router_output, expert_outputs)
        return final_output

class Block(nn.Module):
    def __init__(self, embed_size: int, n_heads: int, seq_len: int, num_experts: int, active_experts: int):
        super().__init__()
        self.ln1 = nn.LayerNorm(embed_size)
        self.ln2 = nn.LayerNorm(embed_size)
        self.attn = MultiHeadAttention(n_heads, embed_size // n_heads, seq_len, embed_size)
        self.ffn = SparseMoE(embed_size, num_experts, active_experts)

    def forward(self, inputs):
        x = inputs + self.attn(self.ln1(inputs))
        return x + self.ffn(self.ln2(x))

class SparseMoETransformer(nn.Module):
    def __init__(self, vocab_size: int, seq_len: int, embed_size: int, n_layers: int, n_heads: int, num_experts: int, active_experts: int):
        super().__init__()
        self.seq_len = seq_len
        self.token_embedding = nn.Embedding(vocab_size, embed_size)
        self.position_embedding = nn.Embedding(seq_len, embed_size)
        self.blocks = nn.ModuleList([Block(embed_size, n_heads, seq_len, num_experts, active_experts) for _ in range(n_layers)])
        self.ln = nn.LayerNorm(embed_size)
        self.fc = nn.Linear(embed_size, vocab_size)

    def forward(self, inputs, labels=None):
        B, T = inputs.shape
        token_emb = self.token_embedding(inputs)
        pos_emb = self.position_embedding(torch.arange(T, device=device))
        x = token_emb + pos_emb
        for block in self.blocks:
            x = block(x)
        logits = self.fc(self.ln(x))
        loss = None
        if labels is not None:
            logits = logits.view(-1, logits.size(-1))
            labels = labels.view(-1)
            loss = F.cross_entropy(logits, labels)
        return logits, loss

    def generate(self, start_text, max_new_tokens):
        self.eval()
        tokens = tokenizer.encode(start_text).unsqueeze(0).to(device)
        for _ in range(max_new_tokens):
            with torch.no_grad():
                logits, _ = self(tokens)
                next_token = torch.argmax(logits[:, -1, :], dim=-1, keepdim=True)
                tokens = torch.cat((tokens, next_token), dim=1)
        return tokens

def train(model, dataloader, optimizer, device):
    model.train()
    total_loss = 0
    for inputs, labels in dataloader:
        inputs, labels = inputs.to(device), labels.to(device)
        optimizer.zero_grad()
        logits, loss = model(inputs, labels)
        loss.backward()
        optimizer.step()
        total_loss += loss.item()
    return total_loss / len(dataloader)

def evaluate(model, dataloader, device):
    model.eval()
    total_loss = 0
    with torch.no_grad():
        for inputs, labels in dataloader:
            inputs, labels = inputs.to(device), labels.to(device)
            logits, loss = model(inputs, labels)
            total_loss += loss.item()
    return total_loss / len(dataloader)

def plot_losses(train_losses, val_losses):
    plt.plot(train_losses, label='Train Loss')
    plt.plot(val_losses, label='Validation Loss')
    plt.legend()
    plt.show()

def main():
    tokenizer = Tokenizer(dataPath="input.txt")
    train_dataloader, val_dataloader = create_dataloader('input.txt', tokenizer, chunk_size=200, batch_size=2)

    model = SparseMoETransformer(vocab_size=len(tokenizer.char2index), seq_len=200, embed_size=64, n_layers=6, n_heads=8, num_experts=4, active_experts=2).to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=3e-4)
    epochs = 10

    train_losses = []
    val_losses = []

    for epoch in range(1, epochs + 1):
        train_loss = train(model, train_dataloader, optimizer, device)
        val_loss = evaluate(model, val_dataloader, device)
        
        train_losses.append(train_loss)
        val_losses.append(val_loss)
        
        print(f'Epoch {epoch} | Training Loss: {train_loss} | Validation Loss: {val_loss}')

    plot_losses(train_losses, val_losses)

    generated_text = generate_text(model, "To be, or not to be", 100)
    print(generated_text)

if __name__ == "__main__":
    main()
