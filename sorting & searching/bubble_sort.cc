/**
 * @file bubble_sort.cc
 * @author Hongyu Ding
 * @brief This is the code of the bubble sort
 * @version 1.0
 * @date 2020-10-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <vector>

/**
 * @brief bubble_sort sorts the array a
 * O(n^2)
 * 
 * @param a the array we want to perform bubble sort with
 */
void bubble_sort(std::vector<int> &a) {
    int len = a.size();
    for (int i = 0; i < len - 1; i ++) {
        for (int j = 0; j < len - i - 1; j ++) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
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

    bubble_sort(array);

    // output
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}