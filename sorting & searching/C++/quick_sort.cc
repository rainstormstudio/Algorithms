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

int partition(std::vector<int> &nums, int l, int r) {
    int pivot = nums[r];
    int i = l, j = l, temp;
    while (j < r) {
        if (nums[j] < pivot) {
            std::swap(nums[i], nums[j]);
            i ++;
        }
        j ++;
    }
    nums[r] = nums[i];
    nums[i] = pivot;
    return i;
}

void qsort(std::vector<int> &nums, int l, int r) {
    if (l < r) {
        int mid = partition(nums, l, r);
        qsort(nums, l, mid - 1);
        qsort(nums, mid + 1, r);
    }
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