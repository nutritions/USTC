#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;
int M ;
int N ;
int T ;
pair<int, int> start_point;  // 起点
pair<int, int> end_point;    // 终点

//地图单元格
struct Map_Cell {
    int type;
    // TODO: 定义地图信息
};
Map_Cell** Map = NULL;

//搜索单元格
struct Search_Cell {
    int h;
    int g;
    // TODO: 定义搜索状态
    int rday;                       // 食物数量
    pair<int, int> point;        // 所处位置
    struct Search_Cell* come_from;  // 父结点
};
Search_Cell* cur_cell;           // 当前格
vector<Search_Cell*> next_cell;  // 相邻格集合

// 自定义比较函数对象，按照 Search_Cell 结构体的 g + h 属性进行比较
struct CompareF {
    bool operator()(const Search_Cell* a, const Search_Cell* b) const {
        return (a->g + a->h) > (b->g + b->h);  // 较小的 g + h 值优先级更高
    }
};

// TODO: 定义启发式函数
// 用曼哈顿距离作为启发函数
int Heuristic_Funtion(pair<int, int> point) {
    return abs(point.first - end_point.first) + abs(point.second - end_point.second);
    
}

//判断搜索格是否合法并且无阻碍
bool isValidCell(int x, int y) {
    if (x >= 0 && x < M && y >= 0 && y < N && Map[x][y].type!=1) {
        return true;
    }
    return false;
}

//更新相邻格信息
void update(int x,int y,Search_Cell* x_cell){
    x_cell->point = {x, y};                    // 位置更新
    x_cell->g = cur_cell->g + 1;                   // g++
    x_cell->h = Heuristic_Funtion(x_cell->point);  // 启发式函数更新
    if (Map[x][y].type == 2) {  // 食物维持时间更新
        x_cell->rday = T;
    } else {
        x_cell->rday = cur_cell->rday - 1;
    }
    next_cell.push_back(x_cell);

}

//得到路径
void getPath(Search_Cell *cur_cell,Search_Cell *parent_cell,string &way){
    if(parent_cell==NULL){
        reverse(way.begin(), way.end());
        return;
    }
    if(cur_cell->point>parent_cell->point){
        if(cur_cell->point.first>parent_cell->point.first){
            way += "D";
        }else{
            way += "R";
        }
    }else{
        if(cur_cell->point.first<parent_cell->point.first){
            way += "U";
        }else{
            way += "L";
        }
    }
    getPath(cur_cell->come_from,parent_cell->come_from,way);
}

void Astar_search(const string input_file, int& step_nums, string& way) {
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    getline(file, line);  // 读取第一行
    stringstream ss(line);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    M = stoi(words[0]);
    N = stoi(words[1]);
    T = stoi(words[2]);

    Map = new Map_Cell*[M];
    // 加载地图
    for (int i = 0; i < M; i++) {
        // 读完一行
        Map[i] = new Map_Cell[N];
        getline(file, line);
        stringstream ss(line);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        // 每行按列一个个读入
        for (int j = 0; j < N; j++) {
            Map[i][j].type = stoi(words[j]);
            if (Map[i][j].type == 3) {
                start_point = {i, j};
            } else if (Map[i][j].type == 4) {
                end_point = {i, j};
            }
        }
    }
    // 以上为预处理部分
    // ------------------------------------------------------------------

    // 初始搜索格创建
    Search_Cell* search_cell = new Search_Cell;
    search_cell->g = 0;
    search_cell->h = Heuristic_Funtion(start_point);  // Heuristic_Funtion();
    search_cell->point = start_point;
    search_cell->come_from = NULL;
    search_cell->rday = T;

    // 待扩展到状态，用优先队列每次选出评估函数最小的
    priority_queue<Search_Cell*, vector<Search_Cell*>, CompareF> open_list;
    //vector<Search_Cell*> close_list;  // 已经探索过的状态
    open_list.push(search_cell);
    
    while (!open_list.empty()) {
        // TODO: A*搜索过程实现
        cur_cell = open_list.top();//每次选出评估函数最小的格子扩展
        if (cur_cell->point == end_point){
            break;
        }
        if (!cur_cell->rday) {//到达这个格子时食物不足，无法行动，直接移出
            open_list.pop();
            continue;
        }
        int x = cur_cell->point.first;
        int y = cur_cell->point.second;
        next_cell.clear();
        //下相邻格
        if (isValidCell(x+1,y)) {
            Search_Cell* d_cell = new Search_Cell;
            update(x+1,y,d_cell);
        }
        //右相邻格
        if (isValidCell(x,y+1)) {
            Search_Cell* r_cell = new Search_Cell;
            update(x,y+1,r_cell);
        }
        //上相邻格
        if (isValidCell(x-1,y)) {
            Search_Cell* u_cell = new Search_Cell;
            update(x-1,y,u_cell);
        }
        //左相邻格
        if (isValidCell(x,y-1)) {
            Search_Cell* r_cell = new Search_Cell;
            update(x,y-1,r_cell);
        }
        
        //移出优先队列，从next_cell中选择能加入优先队列的
        open_list.pop();
        // 已经访问过的结点不能加入优先队列
        for (auto nc : next_cell) {
            Search_Cell* parent= cur_cell;
            bool is_exist = false;
            while (parent=parent->come_from) {
                if (parent->point == nc->point) {
                    is_exist = true;
                    break;
                }
            }
            if(is_exist){
                continue;
            }
            open_list.push(nc);
            nc->come_from = cur_cell;
        }
    }

    // ------------------------------------------------------------------
    // TODO: 填充step_nums与way
    if (cur_cell->point == end_point) {
        step_nums = cur_cell->g;
        getPath(cur_cell,cur_cell->come_from,way);
    } else {
        step_nums = -1;
        way = "";
    }

    // ------------------------------------------------------------------
    // 释放动态内存
    for (int i = 0; i < M; i++) {
        delete[] Map[i];
    }
    delete[] Map;
    while (!open_list.empty()) {
        auto temp = open_list.top();
        delete[] temp;
        open_list.pop();
    }
    return;
}

void output(const string output_file, int& step_nums, string& way) {
    ofstream file(output_file);
    if (file.is_open()) {
        file << step_nums << endl;
        if (step_nums >= 0) {
            file << way << endl;
        }

        file.close();
    } else {
        cerr << "Can not open file: " << output_file << endl;
    }
    return;
}

int main(int argc, char* argv[]) {
    string input_base = "../input/input_";
    string output_base = "../output/output_";
    // input_0为讲义样例，此处不做测试
    long start_time = GetTickCount();   //获取开始执行时间
    for (int i = 1; i < 11; i++) {
        int step_nums = 0;
        string way = "";
        Astar_search(input_base + to_string(i) + ".txt", step_nums, way);
        output(output_base + to_string(i) + ".txt", step_nums, way);
    }
    long end_time = GetTickCount();     //获取结束时间
    long Times = end_time-start_time;
    
    return 0;
}