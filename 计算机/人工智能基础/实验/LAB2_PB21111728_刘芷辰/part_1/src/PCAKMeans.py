from sklearn.datasets import load_wine
import numpy as np 
import matplotlib.pyplot as plt
from gensim.models import KeyedVectors

# 定义不同的核函数
def get_kernel_function(kernel: str, X):
    if kernel == "linear":
        return np.dot(X, X.T)  # 线性核函数
    elif kernel == "poly":
        return (np.dot(X, X.T) + 1) ** 2  # 多项式核函数
    elif kernel == "rbf":
        gamma = 1.0 / X.shape[1]
        sq_dists = -2 * np.dot(X, X.T) + np.sum(X**2, axis=1)[:, np.newaxis] + np.sum(X**2, axis=1)[np.newaxis, :]
        return np.exp(-gamma * sq_dists)  # 高斯核函数
    else:
        raise ValueError("Unknown kernel")

# 定义PCA类
class PCA:
    def __init__(self, n_components: int = 2, kernel: str = "linear") -> None:
        self.n_components = n_components
        self.kernel = kernel
        self.eigenvectors = None

    # 拟合PCA模型
    def fit(self, X: np.ndarray):
        # 中心化数据
        self.X_centered = X - np.mean(X, axis=0)
        # 计算核矩阵
        K = get_kernel_function(self.kernel, self.X_centered)
        # 计算特征值和特征向量
        eigenvalues, eigenvectors = np.linalg.eigh(K)
        # 按照特征值排序
        idx = np.argsort(eigenvalues)[::-1]
        self.eigenvectors = eigenvectors[:, idx][:, :self.n_components]

    # 转换数据
    def transform(self, X: np.ndarray):
        # 将数据投影到主成分上
        K = get_kernel_function(self.kernel, X - np.mean(X, axis=0))
        X_reduced = np.dot(K, self.eigenvectors)
        return X_reduced

# 定义KMeans类
class KMeans:
    def __init__(self, n_clusters: int = 3, max_iter: int = 10) -> None:
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.centers = None
        self.labels = None

    # 初始化聚类中心
    def initialize_centers(self, points):
        n, d = points.shape
        self.centers = np.zeros((self.n_clusters, d))
        for k in range(self.n_clusters):
            random_index = np.random.choice(n, size=10, replace=False)
            self.centers[k] = points[random_index].mean(axis=0)
        return self.centers
    
    # 分配样本到最近的聚类中心
    def assign_points(self, points):
        n_samples = points.shape[0]
        self.labels = np.zeros(n_samples, dtype=int)
        for i in range(n_samples):
            distances = np.linalg.norm(points[i] - self.centers, axis=1)
            self.labels[i] = np.argmin(distances)
        return self.labels

    # 更新聚类中心
    def update_centers(self, points):
        for k in range(self.n_clusters):
            cluster_points = points[self.labels == k]
            if len(cluster_points) > 0:
                self.centers[k] = np.mean(cluster_points, axis=0)
    
    # 拟合KMeans模型
    def fit(self, points):
        self.initialize_centers(points)
        for _ in range(self.max_iter):
            self.assign_points(points)
            self.update_centers(points)

    # 预测每个样本的聚类标签
    def predict(self, points):
        return self.assign_points(points)
    
# 加载数据
def load_data():
    words = [
        'computer', 'laptop', 'minicomputers', 'PC', 'software', 'Macbook',
        'king', 'queen', 'monarch','prince', 'ruler','princes', 'kingdom', 'royal',
        'man', 'woman', 'boy', 'teenager', 'girl', 'robber','guy','person','gentleman',
        'banana', 'pineapple','mango','papaya','coconut','potato','melon',
        'shanghai','HongKong','chinese','Xiamen','beijing','Guilin',
        'disease', 'infection', 'cancer', 'illness', 
        'twitter', 'facebook', 'chat', 'hashtag', 'link', 'internet',
    ]
    w2v = KeyedVectors.load_word2vec_format('./data/GoogleNews-vectors-negative300.bin', binary=True)
    vectors = []
    for w in words:
        vectors.append(w2v[w].reshape(1, 300))
    vectors = np.concatenate(vectors, axis=0)
    return words, vectors

# 主程序
if __name__=='__main__':
    words, data = load_data()
    pca = PCA(n_components=2)
    pca.fit(data)
    data_pca = pca.transform(data)

    kmeans = KMeans(n_clusters=7)
    kmeans.fit(data_pca)
    clusters = kmeans.predict(data_pca)

    # 绘制数据
    plt.figure()
    plt.scatter(data_pca[:, 0], data_pca[:, 1], c=clusters)
    for i in range(len(words)):
        plt.annotate(words[i], data_pca[i, :]) 
    plt.title("PB21111728")
    plt.savefig("PCA_KMeans.png")
