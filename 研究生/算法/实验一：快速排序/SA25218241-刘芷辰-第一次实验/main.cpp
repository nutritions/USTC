#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <random> 

const int k = 50; // 长度阈值

// 插入排序
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 三数取中
int medianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2; 

    // 调整三个数的顺序
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);

    std::swap(arr[mid], arr[high - 1]); // 将基准值移到high-1位置，分区函数最后的处理是将最后的基准值移到正确位置
    return arr[high - 1]; 
}

// 分区函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high); // 选基准
    int i = low;
    int j = high - 1;

    while (true) {
        while (arr[++i] < pivot); // 找到大于等于基准的元素
        while (arr[--j] > pivot); // 找到小于等于基准的元素
        if (i >= j) break;
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[i], arr[high - 1]); // 将基准值放到正确位置
    return i;
}

// 快速排序
void quickSortOptimized(std::vector<int>& arr, int low, int high) {
    if (high - low + 1 > k) {//子数组长度≤k时停止递归
        int pi = partition(arr, low, high);
        quickSortOptimized(arr, low, pi - 1);
        quickSortOptimized(arr, pi + 1, high);
    }
}

int main() {
    // 读取数据
    std::ifstream inFile("data.txt");
    if (!inFile.is_open()) {
        std::cerr << "错误：无法打开data.txt文件！" << std::endl;
        return 1;
    }
    int n;
    inFile >> n;
    std::vector<int> data(n);
    for (int i = 0; i < n; i++) {
        if (!(inFile >> data[i])) {
            return 1;
        }
    }
    inFile.close();

    // 计时
    auto start = std::chrono::high_resolution_clock::now();

    //快排
    quickSortOptimized(data, 0, n - 1);

    //插入排序对递归后大致有序数组进行最后的排序
    insertionSort(data);

    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    
    std::ofstream outFile("sorted.txt");
    if (!outFile.is_open()) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        outFile << data[i];
        if (i != n - 1) outFile << " ";
    }
    outFile.close();

    std::cout << "排序完成，结果保存在sorted.txt" << std::endl;
    std::cout << "运行时间：" << duration.count() << " ms " << std::endl;

    return 0;
}