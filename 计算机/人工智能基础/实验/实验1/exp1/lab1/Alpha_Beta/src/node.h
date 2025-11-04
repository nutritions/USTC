#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace ChineseChess {
// 棋力评估，这里的棋盘方向和输入棋盘方向不同，在使用时需要仔细
// 生成合法动作代码部分已经使用，经过测试是正确的，大家可以参考
std::vector<std::vector<int>> JiangPosition = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
    {5, -8, -9, 0, 0, 0, 0, 0, 0, 0},
    {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

std::vector<std::vector<int>> ShiPosition = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

std::vector<std::vector<int>> XiangPosition = {
    {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
};

std::vector<std::vector<int>> MaPosition = {
    {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
    {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
    {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
    {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
    {2, -10, 4, 10, 15, 16, 12, 11, 6, 2},
    {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
    {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
    {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
    {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
};

std::vector<std::vector<int>> PaoPosition = {
    {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
    {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
    {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
    {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
    {3, 2, 5, 0, 4, 4, 4, -4, -7, -6},
    {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
    {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
    {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
};

std::vector<std::vector<int>> JuPosition = {
    {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
    {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
    {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
    {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
    {0, 0, 12, 14, 15, 15, 16, 16, 33, 14},
    {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
    {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
    {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
    {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
};

std::vector<std::vector<int>> BingPosition = {
    {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
    {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
    {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
    {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
    {0, 0, 0, 6, 7, 40, 42, 55, 70, 4},
    {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
    {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
    {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
    {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
};

// 棋子价值评估
std::map<std::string, int> piece_values = {
    {"Jiang", 10000},
    {"Shi", 10},
    {"Xiang", 30},
    {"Ma", 300},
    {"Ju", 500},
    {"Pao", 300},
    {"Bing", 90}};

// 行期可能性评估，这里更多是对下一步动作的评估
std::map<std::string, int> next_move_values = {
    {"Jiang", 9999},
    {"Shi", 80},
    {"Xiang", 30},
    {"Ma", 100},
    {"Ju", 500},
    {"Pao", 100},
    {"Bing", -20}};

// 动作结构体，每个动作设置score，可以方便剪枝
struct Move {
    int init_x;
    int init_y;
    int next_x;
    int next_y;
    int score;
};

// 定义棋盘上的棋子结构体
struct ChessPiece {
    char name;           // 棋子名称
    int init_x, init_y;  // 棋子的坐标
    bool color;          // 棋子阵营 true为红色、false为黑色
};

// 定义棋盘类
class ChessBoard {
   private:
    int sizeX, sizeY;                      // 棋盘大小，固定
    std::vector<ChessPiece> pieces;        // 棋盘上所有棋子
    std::vector<std::vector<char>> board;  // 当前棋盘、二维数组表示
    std::vector<Move> red_moves;           // 红方棋子的合法动作
    std::vector<Move> black_moves;         // 黑方棋子的合法动作
   public:
    // 初始化棋盘，提取棋盘上棋子，并生成所有合法动作
    void initializeBoard(const std::vector<std::vector<char>>& init_board) {
        board = init_board;
        sizeX = board.size();
        sizeY = board[0].size();

        for (int i = 0; i < sizeX; ++i) {
            for (int j = 0; j < sizeY; ++j) {
                char pieceChar = board[i][j];
                if (pieceChar == '.')
                    continue;

                ChessPiece piece;
                piece.init_x = j;
                piece.init_y = i;
                piece.color = (pieceChar >= 'A' && pieceChar <= 'Z');
                piece.name = pieceChar;
                pieces.push_back(piece);

                switch (pieceChar) {
                    case 'R':
                        generateJuMoves(j, i, piece.color);
                        break;
                    case 'C':
                        generatePaoMoves(j, i, piece.color);
                        break;
                    case 'N':
                        generateMaMoves(j, i, piece.color);
                        break;
                    case 'B':
                        generateXiangMoves(j, i, piece.color);
                        break;
                    case 'A':
                        generateShiMoves(j, i, piece.color);
                        break;
                    case 'K':
                        generateJiangMoves(j, i, piece.color);
                        break;
                    case 'P':
                        generateBingMoves(j, i, piece.color);
                        break;
                    case 'r':
                        generateJuMoves(j, i, piece.color);
                        break;
                    case 'c':
                        generatePaoMoves(j, i, piece.color);
                        break;
                    case 'n':
                        generateMaMoves(j, i, piece.color);
                        break;
                    case 'b':
                        generateXiangMoves(j, i, piece.color);
                        break;
                    case 'a':
                        generateShiMoves(j, i, piece.color);
                        break;
                    case 'k':
                        generateJiangMoves(j, i, piece.color);
                        break;
                    case 'p':
                        generateBingMoves(j, i, piece.color);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // 生成车的合法动作
    void generateJuMoves(int x, int y, bool color) {
        // 前后左右分别进行搜索，遇到棋子停止，不同阵营可以吃掉
        std::vector<Move> JuMoves;
        for (int i = x + 1; i < sizeY; i++) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = i;
            cur_move.next_y = y;
            cur_move.score = 0;
            if (board[y][i] != '.') {
                bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                if (cur_color != color) {
                    JuMoves.push_back(cur_move);
                }
                break;
            }
            JuMoves.push_back(cur_move);
        }

        for (int i = x - 1; i >= 0; i--) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = i;
            cur_move.next_y = y;
            cur_move.score = 0;
            if (board[y][i] != '.') {
                bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                if (cur_color != color) {
                    JuMoves.push_back(cur_move);
                }
                break;
            }
            JuMoves.push_back(cur_move);
        }

        for (int j = y + 1; j < sizeX; j++) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = x;
            cur_move.next_y = j;
            cur_move.score = 0;
            if (board[j][x] != '.') {
                bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                if (cur_color != color) {
                    JuMoves.push_back(cur_move);
                }
                break;
            }
            JuMoves.push_back(cur_move);
        }

        for (int j = y - 1; j >= 0; j--) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = x;
            cur_move.next_y = j;
            cur_move.score = 0;
            if (board[j][x] != '.') {
                bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                if (cur_color != color) {
                    JuMoves.push_back(cur_move);
                }
                break;
            }
            JuMoves.push_back(cur_move);
        }
        for (int i = 0; i < JuMoves.size(); i++) {
            if (color) {
                JuMoves[i].score = JuPosition[JuMoves[i].next_x][9 - JuMoves[i].next_y] - JuPosition[x][9 - y];
                red_moves.push_back(JuMoves[i]);
            } else {
                JuMoves[i].score = JuPosition[JuMoves[i].next_x][JuMoves[i].next_y] - JuPosition[x][y];
                black_moves.push_back(JuMoves[i]);
            }
        }
    }

    // 生成马的合法动作
    void generateMaMoves(int x, int y, bool color) {
        // 便利所有可能动作，筛选
        std::vector<Move> MaMoves;
        int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
        int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
        // 简化，不考虑拌马脚
        // TODO: 可以实现拌马脚过程
        for (int i = 0; i < 8; i++) {
            Move cur_move;
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10)
                continue;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = nx;
            cur_move.next_y = ny;
            cur_move.score = 0;
            if (board[ny][nx] != '.') {
                // 注意棋盘坐标系，这里nx、ny相反是正确的
                bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                if (cur_color != color) {
                    MaMoves.push_back(cur_move);
                }
                continue;
            }
            MaMoves.push_back(cur_move);
        }

        for (int i = 0; i < MaMoves.size(); i++) {
            if (color) {
                MaMoves[i].score = MaPosition[MaMoves[i].next_x][9 - MaMoves[i].next_y] - MaPosition[x][9 - y];
                red_moves.push_back(MaMoves[i]);
            } else {
                MaMoves[i].score = MaPosition[MaMoves[i].next_x][MaMoves[i].next_y] - MaPosition[x][y];
                black_moves.push_back(MaMoves[i]);
            }
        }
    }

    // 生成炮的合法动作
    void generatePaoMoves(int x, int y, bool color) {
        // 和车生成动作相似，需要考虑炮翻山吃子的情况
        // 炮不吃子时和车的行走规则完全相同
        // 炮吃子时必须隔着一个子(己方或者对方的)
        std::vector<Move> PaoMoves;
        // TODO:
        for (int i = x + 1; i < sizeY; i++) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = i;
            cur_move.next_y = y;
            cur_move.score = 0;
            if (board[y][i] != '.') {
                while (++i < sizeY) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = i;
                    cur_move.next_y = y;
                    cur_move.score = 0;
                    if (board[y][i] != '.') {
                        bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                        if (cur_color != color) {
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
                break;
            }
            // 不吃子时
            PaoMoves.push_back(cur_move);
        }

        for (int i = x - 1; i >= 0; i--) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = i;
            cur_move.next_y = y;
            cur_move.score = 0;
            if (board[y][i] != '.') {
                while (--i >= 0) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = i;
                    cur_move.next_y = y;
                    cur_move.score = 0;
                    if (board[y][i] != '.') {
                        bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                        if (cur_color != color) {
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
                break;
            }
            PaoMoves.push_back(cur_move);
        }

        for (int j = y - 1; j >= 0; j--) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = x;
            cur_move.next_y = j;
            cur_move.score = 0;
            if (board[j][x] != '.') {
                while (--j >= 0) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = x;
                    cur_move.next_y = j;
                    cur_move.score = 0;
                    if (board[j][x] != '.') {
                        bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                        if (cur_color != color) {
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
                break;
            }
            PaoMoves.push_back(cur_move);
        }
        for (int j = y + 1; j < sizeX; j++) {
            Move cur_move;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = x;
            cur_move.next_y = j;
            cur_move.score = 0;
            if (board[j][x] != '.') {
                while (++j < sizeX) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = x;
                    cur_move.next_y = j;
                    cur_move.score = 0;
                    if (board[j][x] != '.') {
                        bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                        if (cur_color != color) {
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
                break;
            }
            PaoMoves.push_back(cur_move);
        }

        for (int i = 0; i < PaoMoves.size(); i++) {
            if (color) {
                PaoMoves[i].score = PaoPosition[PaoMoves[i].next_x][9 - PaoMoves[i].next_y] - PaoPosition[x][9 - y];
                red_moves.push_back(PaoMoves[i]);
            } else {
                PaoMoves[i].score = PaoPosition[PaoMoves[i].next_x][PaoMoves[i].next_y] - PaoPosition[x][y];
                black_moves.push_back(PaoMoves[i]);
            }
        }
    }

    // 生成相的合法动作
    void generateXiangMoves(int x, int y, bool color) {
        std::vector<Move> XiangMoves;
        // TODO:
        //  简化,不考虑塞象眼
        int dx[] = {2, 2, -2, -2};
        int dy[] = {2, -2, -2, 2};

        for (int i = 0; i < 4; i++) {
            Move cur_move;
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10)
                continue;
            if ((color && ny < 5) || (!color && ny > 4))
                continue;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = nx;
            cur_move.next_y = ny;
            cur_move.score = 0;
            if (board[ny][nx] != '.') {
                // 注意棋盘坐标系，这里nx、ny相反是正确的
                bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                if (cur_color != color) {
                    XiangMoves.push_back(cur_move);
                }
                continue;
            }
            XiangMoves.push_back(cur_move);
        }

        for (int i = 0; i < XiangMoves.size(); i++) {
            if (color) {
                XiangMoves[i].score = XiangPosition[XiangMoves[i].next_x][9 - XiangMoves[i].next_y] - XiangPosition[x][9 - y];
                red_moves.push_back(XiangMoves[i]);
            } else {
                XiangMoves[i].score = XiangPosition[XiangMoves[i].next_x][XiangMoves[i].next_y] - XiangPosition[x][y];
                black_moves.push_back(XiangMoves[i]);
            }
        }
    }

    // 生成士的合法动作
    void generateShiMoves(int x, int y, bool color) {
        std::vector<Move> ShiMoves;
        // TODO:
        //  沿对角线移动且不能超过九宫格
        int dx[] = {1, 1, -1, -1};
        int dy[] = {1, -1, -1, 1};

        for (int i = 0; i < 4; i++) {
            Move cur_move;
            int nx = x + dx[i];
            int ny = y + dy[i];
            if ((color && (nx < 3 || nx > 5 || ny > 9 || ny < 7)) || (!color && (nx < 3 || nx > 5 || ny < 0 || ny > 2)))
                continue;

            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = nx;
            cur_move.next_y = ny;
            cur_move.score = 0;
            if (board[ny][nx] != '.') {
                // 注意棋盘坐标系，这里nx、ny相反是正确的
                bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                if (cur_color != color) {
                    ShiMoves.push_back(cur_move);
                }
                continue;
            }
            ShiMoves.push_back(cur_move);
        }

        for (int i = 0; i < ShiMoves.size(); i++) {
            if (color) {
                ShiMoves[i].score = ShiPosition[ShiMoves[i].next_x][9 - ShiMoves[i].next_y] - ShiPosition[x][9 - y];
                red_moves.push_back(ShiMoves[i]);
            } else {
                ShiMoves[i].score = ShiPosition[ShiMoves[i].next_x][ShiMoves[i].next_y] - ShiPosition[x][y];
                black_moves.push_back(ShiMoves[i]);
            }
        }
    }

    // 生成将的合法动作
    void generateJiangMoves(int x, int y, bool color) {
        std::vector<Move> JiangMoves;
        // TODO:
        //  将只能在九宫格的范围内前进后退横走
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};
        for (int i = 0; i < 4; i++) {
            Move cur_move;
            int nx = x + dx[i];
            int ny = y + dy[i];
            if ((color && (nx < 3 || nx > 5 || ny > 9 || ny < 7)) || (!color && (nx < 3 || nx > 5 || ny < 0 || ny > 2)))
                continue;
            cur_move.init_x = x;
            cur_move.init_y = y;
            cur_move.next_x = nx;
            cur_move.next_y = ny;
            cur_move.score = 0;
            if (board[ny][nx] != '.') {
                // 注意棋盘坐标系，这里nx、ny相反是正确的
                bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                if (cur_color != color) {
                    JiangMoves.push_back(cur_move);
                }
                continue;
            }
            JiangMoves.push_back(cur_move);
        }

        for (int i = 0; i < JiangMoves.size(); i++) {
            if (color) {
                JiangMoves[i].score = JiangPosition[JiangMoves[i].next_x][9 - JiangMoves[i].next_y] - JiangPosition[x][9 - y];
                red_moves.push_back(JiangMoves[i]);
            } else {
                JiangMoves[i].score = JiangPosition[JiangMoves[i].next_x][JiangMoves[i].next_y] - JiangPosition[x][y];
                black_moves.push_back(JiangMoves[i]);
            }
        }
    }

    // 生成兵的合法动作
    void generateBingMoves(int x, int y, bool color) {
        std::vector<Move> BingMoves;
        // TODO:
        int dx[] = {0, 1, -1};
        int dy_r[] = {-1, 0, 0};
        int dy_b[] = {1, 0, 0};

       switch(color) {
    case true: // 红色
        if (y <= 4) {  // 红子在黑方棋盘内
            for (int i = 0; i < 3; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy_r[i];
                if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10)
                    continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    // 注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        BingMoves.push_back(cur_move);
                    }
                    continue;
                }
                BingMoves.push_back(cur_move);
            }
        } else {  // 红子在自方棋盘内
            Move cur_move;
            int nx = x;
            int ny = y - 1;
            if (ny >= 0) {
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    // 注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        BingMoves.push_back(cur_move);
                    }
                }
                BingMoves.push_back(cur_move);
            }
        }
        break;
        
    case false: // 黑色
        if (y > 4) {  // 黑子在红方棋盘内
            for (int i = 0; i < 3; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy_b[i];
                if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10)
                    continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    // 注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        BingMoves.push_back(cur_move);
                    }
                    continue;
                }
                BingMoves.push_back(cur_move);
            }
        } else {  // 黑子在自方棋盘内
            Move cur_move;
            int nx = x;
            int ny = y + 1;
            if (ny < 10) {
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    // 注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        BingMoves.push_back(cur_move);
                    }
                }
                BingMoves.push_back(cur_move);
            }
        }
        break;
}


        for (int i = 0; i < BingMoves.size(); i++) {
            if (color) {
                BingMoves[i].score = BingPosition[BingMoves[i].next_x][9 - BingMoves[i].next_y] - BingPosition[x][9 - y];
                red_moves.push_back(BingMoves[i]);
            } else {
                BingMoves[i].score = BingPosition[BingMoves[i].next_x][BingMoves[i].next_y] - BingPosition[x][y];
                black_moves.push_back(BingMoves[i]);
            }
        }
    }

    // 终止判断
    bool judgeTermination() {
        // TODO:
        //  如果红方或者黑方将帅消失，说明博弈终止
        bool is_redking_alive = false;
        bool is_blackking_alive = false;
        for (int i = 0; i < sizeX; ++i) {
            if (find(board[i].begin(), board[i].end(), 'K') != board[i].end()) {
                is_redking_alive = true;
            }
            if (find(board[i].begin(), board[i].end(), 'k') != board[i].end()) {
                is_blackking_alive = true;
            }
        }
        return !is_redking_alive || !is_blackking_alive;
    }

    // 棋盘分数评估
    int evaluateNode() {
        // TODO:
        int red_val = 0;
        int black_val = 0;
        // 红色方棋子价值和棋力评估
        for (int i = 5; i < 10; i++) {
            for (int j = 0; j < 9; j++) {
                switch (board[i][j]) {
                    case 'K':
                        red_val += piece_values["Jiang"];
                        red_val += JiangPosition[j][9 - i];
                        break;
                    case 'A':
                        red_val += piece_values["Shi"];
                        red_val += ShiPosition[j][9 - i];
                        break;
                    case 'B':
                        red_val += piece_values["Xiang"];
                        red_val += XiangPosition[j][9 - i];
                        break;
                    case 'N':
                        red_val += piece_values["Ma"];
                        red_val += MaPosition[j][9 - i];
                        break;
                    case 'R':
                        red_val += piece_values["Ju"];
                        red_val += JuPosition[j][9 - i];
                        break;
                    case 'C':
                        red_val += piece_values["Pao"];
                        red_val += PaoPosition[j][9 - i];
                        break;
                    case 'P':
                        red_val += piece_values["Bing"];
                        red_val += BingPosition[j][9 - i];
                        break;
                    default:
                        break;
                }
            }
        }
        // 红色方棋子行棋可能性评估
        for (Move move : red_moves) {
            switch (board[move.next_y][move.next_x]) {
                case 'k':
                    red_val += next_move_values["Jiang"];
                    break;
                case 'a':
                    red_val += next_move_values["Shi"];
                    break;
                case 'b':
                    red_val += next_move_values["Xiang"];
                    break;
                case 'n':
                    red_val += next_move_values["Ma"];
                    break;
                case 'r':
                    red_val += next_move_values["Ju"];
                    break;
                case 'c':
                    red_val += next_move_values["Pao"];
                    break;
                case 'p':
                    red_val += next_move_values["Bing"];
                    break;
                default:
                    break;
            }
        }
        // 黑色方棋子价值和棋力评估
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                switch (board[i][j]) {
                    case 'k':
                        black_val += piece_values["Jiang"];
                        black_val += JiangPosition[j][i];
                        break;
                    case 'a':
                        black_val += piece_values["Shi"];
                        black_val += ShiPosition[j][i];
                        break;
                    case 'b':
                        black_val += piece_values["Xiang"];
                        black_val += XiangPosition[j][i];
                        break;
                    case 'n':
                        black_val += piece_values["Ma"];
                        black_val += MaPosition[j][i];
                        break;
                    case 'r':
                        black_val += piece_values["Ju"];
                        black_val += JuPosition[j][i];
                        break;
                    case 'c':
                        black_val += piece_values["Pao"];
                        black_val += PaoPosition[j][i];
                        break;
                    case 'p':
                        black_val += piece_values["Bing"];
                        black_val += BingPosition[j][i];
                        break;
                    default:
                        break;
                }
            }
        }
        // 黑色方棋子行棋可能性评估
        for (Move move : black_moves) {
            switch (board[move.next_y][move.next_x]) {
                case 'K':
                    black_val += next_move_values["Jiang"];
                    break;
                case 'A':
                    black_val += next_move_values["Shi"];
                    break;
                case 'B':
                    black_val += next_move_values["Xiang"];
                    break;
                case 'N':
                    black_val += next_move_values["Ma"];
                    break;
                case 'R':
                    black_val += next_move_values["Ju"];
                    break;
                case 'C':
                    black_val += next_move_values["Pao"];
                    break;
                case 'P':
                    black_val += next_move_values["Bing"];
                    break;
                default:
                    break;
            }
        }
        return red_val - black_val;
    }

    // 测试接口
    std::vector<Move> getMoves(bool color) {
        if (color)
            return red_moves;
        return black_moves;
    }

    std::vector<ChessPiece> getChessPiece() {
        return pieces;
    }

    std::vector<std::vector<char>> getBoard() {
        return board;
    }
};

// 定义博弈树节点类
class GameTreeNode {
   public:
    bool color;                           // 当前玩家类型，true为红色方、false为黑色方
    ChessBoard board;                     // 当前棋盘状态
    std::vector<GameTreeNode*> children;  // 子节点列表
    int evaluationScore;                  // 棋盘最终评估分数
    int score;                            // 棋盘评价分数
    Move move;                            // 记录导致该节点的动作

    // 构造函数
    GameTreeNode(bool color, std::vector<std::vector<char>> initBoard, int evaluationscore)
        : color(color), evaluationScore(evaluationScore) {
        board.initializeBoard(initBoard);
        // std::vector<Move> moves = board.getMoves(color);
        children.clear();
        score = board.evaluateNode();
        // std::vector<std::vector<char>> cur_board = board.getBoard();
    }

    // 根据当前棋盘和动作构建新棋盘（子节点）
    GameTreeNode* updateBoard(std::vector<std::vector<char>> cur_board, Move move, bool color) {
        // TODO:
        //  创建一个新的游戏树节点
        int x_n = move.init_x;
        int y_n = move.init_y;
        int x_ne = move.next_x;
        int y_ne = move.next_y;
        cur_board[y_ne][x_ne] = cur_board[y_n][x_n];
        cur_board[y_n][x_n] = '.';
        // 转换
        GameTreeNode* tNode = new GameTreeNode(!color, cur_board, std::numeric_limits<int>::min());
        return tNode;
    }

    // 创建子节点并添加到当前节点的子节点列表中
    std::vector<GameTreeNode*> getChildList() {
        std::vector<Move> moves = board.getMoves(color);
        for (const auto& move : moves) {
            std::vector<std::vector<char>> cur_board = board.getBoard();
            GameTreeNode* child = updateBoard(cur_board, move, color);
            child->move = move;
            children.push_back(child);
        }
        return children;
    }

    std::vector<GameTreeNode*> getChildren() {
        return children;
    }

    ~GameTreeNode() {
        for (GameTreeNode* child : children) {
            delete child;
        }
    }
};

}  