/**
 * @file selection_sort.cc
 * @author Hongyu Ding
 * @brief This is the code of the selection sort
 * @version 1.0
 * @date 2020-10-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <vector>

/**
 * @brief selection_sort sorts the array a
 * O(n^2)
 * 
 * @param a the array we want to perform selection sort with
 */
void selection_sort(std::vector<int> &a) {
    int len = a.size();
    for (int i = 0; i < len - 1; i ++) {
        int min = i;
        for (int j = i + 1; j < len; j ++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        std::swap(a[i], a[min]);
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

    selection_sort(array);

    // output
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}