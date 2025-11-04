#include <algorithm>
#include <fstream>
#include <string>
#include "node.h"

using namespace ChineseChess;
// 博弈树搜索, depth为搜索深度
int alphaBeta(GameTreeNode* gameNode, int alpha, int beta, int depth, bool isMaximizer) {
    if (depth == 0) {
        gameNode->evaluationScore = gameNode->score;
        return gameNode->score;
    }
    // TODO: alpha-beta剪枝过程
    ChessBoard nBoard = gameNode->board;
    if (nBoard.judgeTermination()) {
        gameNode->evaluationScore = gameNode->score;
        return gameNode->score;
    }
    int val_max=std::numeric_limits<int>::min();
    int val_min=std::numeric_limits<int>::max();
    for(auto& child : gameNode->getChildList()){
        if(isMaximizer){
            val_max=std::max(val_max, alphaBeta(child, alpha, beta, depth - 1, false));
            if(beta<=val_max){
                gameNode->evaluationScore = val_max;
                return val_max;
            }
            alpha = std::max(alpha, val_max);
        }else{
            val_min = std::min(val_min, alphaBeta(child, alpha, beta, depth - 1, true));
            if (val_min <= alpha) {
                gameNode->evaluationScore = val_min;
                return val_min;
            }
            beta = std::min(beta, val_min);
        }
    }
    if(isMaximizer){
        gameNode->evaluationScore = val_max;
        return val_max;
    }else{
        gameNode->evaluationScore = val_min;
        return val_min;
    }
    
}



void output(const std::string output_file, Move& move, GameTreeNode& root) {
    std::ofstream file(output_file);
    if (file.is_open()) {
        char ch = root.board.getBoard()[move.init_y][move.init_x];
        file << ch << " "
             << "(" << move.init_x << "," << 9-move.init_y << ")"
             << " "
             << "(" << move.next_x << "," << 9-move.next_y << ")" << std::endl;

        file.close();
    } else {
        std::cout << "error opening file: " <<  std::endl;
    }
    return;
}
int main() {
    std::string input_base = "../input/";
    std::string output_base = "../output/output_";
    for (int i = 1; i <= 10; i++) {
        std::ifstream file(input_base + std::to_string(i) + ".txt");
        std::vector<std::vector<char>> board;

        std::string line;
        int n = 0;
        while (std::getline(file, line)) {
            std::vector<char> row;

            for (char ch : line) {
                row.push_back(ch);
            }

            board.push_back(row);
            n = n + 1;
            if (n >= 10)
                break;
        }

        file.close();
        GameTreeNode root(true, board, std::numeric_limits<int>::min());

        // TODO:
        int alpha=std::numeric_limits<int>::min();
        int beta=std::numeric_limits<int>::max();
        int val = alphaBeta(&root, alpha,beta, 3, true);
        for (auto it : root.children) {
            GameTreeNode *child=it;
            if (child->evaluationScore == val) {
                output(output_base + std::to_string(i) + ".txt", child->move, root);
                break;
            }
        }
    }
    return 0;
}