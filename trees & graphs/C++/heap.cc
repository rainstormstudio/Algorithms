/**
 * @file heap.cc
 * @author Hongyu Ding
 * @brief This file is an implementation of heap data structure
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>

using List = std::vector<int>;

class Heap {
    const int startIndex = 1;

    List btree;
    int heapLen;

    int parentIndex(int index) {
        return index / 2;
    }

    int leftChild(int index) {
        return index * 2;
    }

    int rightChild(int index) {
        return index * 2 + 1;
    }

public:
    Heap() : heapLen{0} {
        btree.push_back(0);
    }
    Heap(List &list) {
        btree.push_back(0);
        heapLen = 0;
        for (auto val : list) {
            btree.push_back(val);
            heapLen ++;
        }
    }

    void build() {
        if (heapLen < 2) return;

        int parent = parentIndex(heapLen);
        do {
            adjustHeap(parent, btree[parent]);
            parent --;
        } while (parent >= startIndex);
    }

    void sortHeap() {
        while (heapLen) {
            pop();
        }
    }

    List getList() const {
        List list;
        for (int i = 1; i < btree.size(); i ++) {
            list.push_back(btree[i]);
        }
        return list;
    }

    void clearList() {
        List heap;
        for (int i = 0; i <= heapLen; i ++) {
            heap.push_back(btree[i]);
        }
        btree = heap;
    }

    void printList(std::ostream &out) const {
        for (int i = 1; i < btree.size(); i ++) {
            out << btree[i] << " ";
        }
    }

    int getLen() const { return heapLen; }

    void printHeap(std::ostream &out) const {
        for (int i = 0; i < heapLen; i ++) {
            out << btree[i + startIndex] << " ";
        }
    }

    void insert(int val) {
        btree.insert(btree.begin() + heapLen + startIndex, val);
        heapLen ++;
        adjustUp(heapLen, btree[heapLen]);
    }

    void pop() {
        int temp = btree[heapLen];
        btree[heapLen] = btree[startIndex];
        heapLen --;
        adjustHeap(startIndex, temp);
    }

    void adjustHeap(int index, int value) {
        int left = leftChild(index);
        int right = rightChild(index);
        int tempIndex = right;
        while (right <= heapLen) {
            if (btree[right] < btree[left]) {
                tempIndex = left;
            }
            btree[index] = btree[tempIndex];
            index = tempIndex;
            left = leftChild(tempIndex);
            right = rightChild(tempIndex);
            tempIndex = right;
        }
        if (tempIndex == heapLen + 1) {
            btree[index] = btree[left];
            index = left;
        }
        btree[index] = value;
        adjustUp(index, value);
    }

    void adjustUp(int index, int value) {
        int parent = parentIndex(index);
        while (index > startIndex && btree[parent] < value) {
            btree[index] = btree[parent];
            index = parent;
            parent = parentIndex(parent);
        }
        btree[index] = value;
    }
};

int main() {
    List ary = {10, 20, 15, 30, 40};
    Heap heap = Heap(ary);

    heap.printHeap(std::cout);
    std::cout << std::endl;

    heap.build();
    heap.printHeap(std::cout);
    std::cout << std::endl;

    heap.pop();
    heap.insert(66);
    heap.pop();
    heap.sortHeap();
    heap.printHeap(std::cout);
    std::cout << std::endl;
    std::cout << "len = " << heap.getLen() << std::endl;
    List sorted = heap.getList();
    for (auto& item : sorted) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    heap.clearList();
    heap.insert(23);
    heap.insert(114);
    heap.insert(90);
    heap.insert(1);
    heap.insert(20);
    heap.printHeap(std::cout);
    std::cout << std::endl;
    heap.pop();
    heap.printHeap(std::cout);
    std::cout << std::endl;
    heap.sortHeap();
    heap.pop();
    heap.printHeap(std::cout);
    std::cout << std::endl;
    heap.printList(std::cout);
    std::cout << std::endl;
    std::cout << "done" << std::endl;

    return 0;
}