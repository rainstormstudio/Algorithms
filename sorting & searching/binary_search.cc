/**
 * @file binary_search.cc
 * @author Hongyu Ding
 * @brief This is the code of binary search
 * @version 1.0
 * @date 2020-10-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <vector>

/**
 * @brief bin_search returns the index of target in the array a
 * if not found, returns -1
 * O(log n)
 * 
 * @param a a sorted array
 * @param target the value we want to find
 * @return int 
 */
int bin_search(std::vector<int> &a, int target) {
    int ans = -1;
    int l = 0, r = a.size(), mid;
    while (l < r) {
        mid = (l + r) / 2;
        if (a[mid] < target) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (l != a.size() && a[l] == target) ans = l;
    return ans;
}

int main() {
    int n, k;
    std::vector<int> array;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int val = 0;
        std::cin >> val;
        array.push_back(val);
    }
    std::cin >> k;

    std::cout << bin_search(array, k) << std::endl;    

    return 0;
}