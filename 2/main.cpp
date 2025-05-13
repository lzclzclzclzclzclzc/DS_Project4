#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <chrono>
#include <cstdlib>

using namespace std;

// 三数取中法获取枢轴索引
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    return mid;
}

// 区间内小于等于3个元素直接插入排序
void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 非递归快速排序
void quickSortIterative(vector<int>& arr) {
    stack<pair<int, int>> bounds;
    bounds.push({0, static_cast<int>(arr.size() - 1)});

    while (!bounds.empty()) {
        auto [low, high] = bounds.top();
        bounds.pop();

        if (high - low + 1 <= 3) {
            insertionSort(arr, low, high);
            continue;
        }

        int pivotIndex = medianOfThree(arr, low, high);
        swap(arr[pivotIndex], arr[high]); // 把枢轴移到末尾
        int pivot = arr[high];

        int i = low - 1;
        bool swapped = false;
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                if (i != j) {
                    swap(arr[i], arr[j]);
                    swapped = true;
                }
            }
        }
        swap(arr[i + 1], arr[high]);
        if (arr[i + 1] != arr[high]) swapped = true;

        int pivotFinal = i + 1;

        if (!swapped) continue;

        int leftSize = pivotFinal - 1 - low;
        int rightSize = high - (pivotFinal + 1);

        if (leftSize < rightSize) {
            if (pivotFinal + 1 < high)
                bounds.push({pivotFinal + 1, high});
            if (low < pivotFinal - 1)
                bounds.push({low, pivotFinal - 1});
        } else {
            if (low < pivotFinal - 1)
                bounds.push({low, pivotFinal - 1});
            if (pivotFinal + 1 < high)
                bounds.push({pivotFinal + 1, high});
        }
    }
}

// 递归快速排序（基准）
void quickSortRecursive(vector<int>& arr, int low, int high) {
    if (high - low + 1 <= 3) {
        insertionSort(arr, low, high);
        return;
    }

    int pivotIndex = medianOfThree(arr, low, high);
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);

    quickSortRecursive(arr, low, i);
    quickSortRecursive(arr, i + 2, high);
}

vector<int> generateRandomData(size_t size) {
    vector<int> data(size);
    for (size_t i = 0; i < size; ++i)
        data[i] = rand() % 100000;
    return data;
}

int main() {
    const size_t dataSize = 1000000; // 一百万数据测试

    vector<int> data1 = generateRandomData(dataSize);
    vector<int> data2 = data1;

    auto start = chrono::high_resolution_clock::now();
    quickSortIterative(data1);
    auto end = chrono::high_resolution_clock::now();
    auto iterDuration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Non-recursive quick sort time: " << iterDuration.count() << " ms" << endl;

    start = chrono::high_resolution_clock::now();
    quickSortRecursive(data2, 0, data2.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto recurDuration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Recursive quick sort time: " << recurDuration.count() << " ms" << endl;

    return 0;
}
