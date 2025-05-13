#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// 改进计数排序：适用于整数区间 [u, w]
void countingSort(vector<int>& arr, int u, int w) {
    int range = w - u + 1;
    vector<int> number(range, 0);

    // 统计每个关键字的个数
    for (int val : arr) {
        number[val - u]++;
    }

    // 重构原数组为有序
    int index = 0;
    for (int i = 0; i < range; ++i) {
        while (number[i]-- > 0) {
            arr[index++] = i + u;
        }
    }
}

// 生成测试数据
vector<int> generateTestData(int n, int u, int w) {
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = u + rand() % (w - u + 1);
    }
    return data;
}

// 验证是否有序
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int n = 1000000; // 一百万数据量
    int u = 100;
    int w = 200;     // 关键字落在 [100, 200] 之间

    vector<int> data = generateTestData(n, u, w);

    auto start = chrono::high_resolution_clock::now();
    countingSort(data, u, w);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Soring Duration: " << duration.count() << " ms" << endl;
    cout << "Correction: " << (isSorted(data) ? "Yes" : "No") << endl;

    return 0;
}
