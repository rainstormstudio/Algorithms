/**
 * @file heap_sort.cc
 * @author Hongyu Ding
 * @brief This is the code of heap sort
 * @version 1.0
 * @date 2020-10-18
 * @ref https://www.geeksforgeeks.org/heap-sort/
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <vector>

/**
 * @brief heapify heapifies a subree that is indexed at
 * i as its root with n as the size of the heap
 * 
 * @param a heap array/array
 * @param n size of the heap
 * @param i root index
 */
void heapify(std::vector<int> &a, int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[max]) max = l;
    if (r < n && a[r] > a[max]) max = r;
    if (max != i) {
        std::swap(a[i], a[max]);
        heapify(a, n, max);
    }
}

/**
 * @brief heap_sort sorts the array a
 * O(n log n)
 * 
 * @param a array we want to sort
 */
void heap_sort(std::vector<int> &a) {
    // build heap
    for (int i = a.size() / 2 - 1; i >= 0; i--) {
        heapify(a, a.size(), i);
    }
    // extract elements from heap
    for (int i = a.size() - 1; i > 0; i--) {
        std::swap(a[0], a[i]);  // move current root to the end
        heapify(a, i, 0);
    }
}

int main() {
    int n;
    std::vector<int> array;
    // input:
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        array.push_back(val);
    }

    heap_sort(array);

    // output
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}