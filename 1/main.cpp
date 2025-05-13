#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include "DoublyLinkedList.h"

using namespace std;

// 生成随机数据
vector<int> generateRandomData(size_t size) {
    vector<int> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = rand() % 10000; // 生成0-9999的随机数
    }
    return data;
}

int main() {
    const size_t dataSize = 10000; // 测试数据量

    // 生成随机数据并打印
    vector<int> data = generateRandomData(dataSize);
    DoublyLinkedList<int> list;

    for (int value : data) {
        list.append(value);
    }

    // 打印排序前的链表
    // list.print();

    // 测试冒泡排序
    auto start = chrono::high_resolution_clock::now();
    list.bubbleSort();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Bubble Sort on Doubly Linked List took: " << duration.count() << " milliseconds." << endl;

    // 对比传统数组冒泡排序
    start = chrono::high_resolution_clock::now();
    vector<int> arrayData = data;
    for (size_t i = 0; i < arrayData.size() - 1; ++i) {
        for (size_t j = 0; j < arrayData.size() - 1 - i; ++j) {
            if (arrayData[j] > arrayData[j + 1]) {
                swap(arrayData[j], arrayData[j + 1]);
            }
        }
    }
    end = chrono::high_resolution_clock::now();
    auto arrayDuration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Bubble Sort on Array took: " << arrayDuration.count() << " milliseconds." << endl;

    return 0;
}
