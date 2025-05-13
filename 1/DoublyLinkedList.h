#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    // 插入到链表尾部
    void append(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    // 清空链表
    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    // 打印链表
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // 冒泡排序，按反复扫描顺序交换节点指针
    void bubbleSort() {
        if (size <= 1) return;

        bool swapped;
        for (size_t i = 0; i < size - 1; ++i) {
            swapped = false;
            Node* current = head;
            for (size_t j = 0; j < size - 1 - i; ++j) {
                if (current->data > current->next->data) {
                    // 交换节点指针
                    swapNodes(current, current->next);
                    swapped = true;
                }
                current = current->next;
            }
            if (!swapped) break;

            swapped = false;
            current = tail;
            for (size_t j = 0; j < size - 1 - i; ++j) {
                if (current->data < current->prev->data) {
                    // 交换节点指针
                    swapNodes(current->prev, current);
                    swapped = true;
                }
                current = current->prev;
            }
            if (!swapped) break;
        }
    }

private:
    // 交换两个节点
    void swapNodes(Node* first, Node* second) {
        if (!first || !second) return;

        Node* temp = first->prev;
        first->prev = second;
        second->prev = temp;

        if (first->prev) first->prev->next = first;
        if (second->prev) second->prev->next = second;

        temp = first->next;
        first->next = second;
        second->next = temp;

        if (first->next) first->next->prev = first;
        if (second->next) second->next->prev = second;

        if (first == head) head = second;
        else if (second == tail) tail = first;
    }
};

#endif // DOUBLYLINKEDLIST_H
