/**
 * @file merge_sort.cc
 * @author Hongyu Ding
 * @brief This is the code of merge sort
 * @version 1.0
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>

void merge(std::vector<int> &a, std::vector<int> &l, std::vector<int> &r) {
    int i = 0, j = 0, index = 0;
    while (i < l.size() || j < r.size()) {
        if (i < l.size() && j < r.size()) {
            if (l[i] < r[j]) {
                a[index] = l[i]; i ++;
            } else {
                a[index] = r[j]; j ++;
            }
        } else if (i == l.size()) {
            while (j < r.size()) {
                a[index] = r[j];
                j ++; index ++;
            }
            break;
        } else if (j == r.size()) {
            while (i < l.size()) {
                a[index] = l[i];
                i ++; index ++;
            }
            break;
        }
        index ++;
    }
}

/**
 * @brief merge_sort applies merge_sort on array a
 * O(n log n)
 * 
 * @param a array
 */
void merge_sort(std::vector<int> &a) {
    if (a.size() <= 1) return;

    std::vector<int> l, r;
    int mid = (static_cast<int>(a.size()) + 1) / 2;

    for (int i = 0; i < mid; i ++) l.emplace_back(a[i]);
    for (int i = mid; i < static_cast<int>(a.size()); i ++) r.emplace_back(a[i]);

    merge_sort(l);
    merge_sort(r);
    merge(a, l, r);
}

int main() {
    std::vector<int> array;
    int n;
    
    // input
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        array.emplace_back(val);
    }

    merge_sort(array);

    // output
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
