/**
 * @file quick_sort.cc
 * @author Hongyu Ding
 * @brief This is the code of the quick sort
 * @version 1.0
 * @date 2020-10-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <vector>

void qsort(std::vector<int> &a, int l, int r) {
    int i = l, j = r, mid = (l + r) / 2;
    while (i <= j) {
        while (a[i] < a[mid]) i ++;
        while (a[j] > a[mid]) j --;
        if (i <= j) {
            std::swap(a[i], a[j]);
            i ++; j --;
        }
    }
    if (l < j) qsort(a, l, j);
    if (r > j) qsort(a, i, r);
}

/**
 * @brief quick_sort sorts the array a
 * O(n log n)
 * 
 * @param a the array we want to perform quick sort with
 */
void quick_sort(std::vector<int> &a) {
    qsort(a, 0, a.size() - 1);
}

int main() {
    std::vector<int> array;
    int n;
    
    // input
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        array.push_back(val);
    }

    quick_sort(array);

    // output
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}