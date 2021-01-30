/**
 * @file k_way_merge_sort.cc
 * @author Daniel Hongyu Ding
 * @brief k way merge sort splits an array into k subarrays 
 * and merges them after sorting each of them.
 * @version 0.1
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <vector>

/**
 * @brief prints an array of integers to standard output
 * 
 * @param ary 
 */
void print(const std::vector<int> &ary) {
    for (size_t i = 0; i < ary.size(); i ++) {
        std::cout << ary[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief split an array into k subarrays
 * 
 * @param ary 
 * @param k 
 * @return std::vector<std::vector<int>> 
 */
std::vector<std::vector<int>> split(const std::vector<int> &ary, int k) {
    int len = ary.size();
    int groupSize = len / k;
    if (len % k) groupSize ++;
    std::vector<std::vector<int>> subs;

    for (int i = 0; i < k && i < len; i ++) {
        std::vector<int> sub;
        for (int j = 0; j < groupSize; j ++) {
            int index = i * groupSize + j;
            if (index >= len) break;
            sub.push_back(ary[index]);
        }
        subs.push_back(sub);
    }

    return subs;
}

/**
 * @brief merges k subarrays into one
 * 
 * @param ary 
 * @return std::vector<int> 
 */
std::vector<int> kWayMerge(const std::vector<std::vector<int>> &arys) {
    int k = arys.size();
    std::vector<int> table = std::vector<int>(k, 0);
    std::vector<int> ans;

    while (true) {
        int l = -1;
        int min = 0;
        for (int i = 0; i < k; i ++) {
            if (table[i] < arys[i].size()) {
                if (l == -1 || min > arys[i][table[i]]) {
                    min = arys[i][table[i]];
                    l = i;
                }
            }
        }
        if (l == -1) break;
        ans.push_back(arys[l][table[l]]);
        table[l] ++;
    }
    return ans;
}

/**
 * @brief k way merge sort
 * 
 * @param ary 
 * @param k 
 */
void kWayMergeSort(std::vector<int> &ary, int k) {
    if (ary.empty() || ary.size() == 1) return;
    std::vector<std::vector<int>> subs = split(ary, k);
    for (auto& sub : subs) {
        kWayMergeSort(sub, k);
    }
    std::vector<int> ans = kWayMerge(subs);
    ary.swap(ans);
}

int main() {
    int n, k;
    std::vector<int> ary;

    std::cout << "input n, k:" << std::endl;
    std::cin >> n >> k;
    std::cout << "input array:" << std::endl;
    for (int i = 0; i < n; i ++) {
        int value;
        std::cin >> value;
        ary.push_back(value);
    }

    std::cout << "original array: " << std::endl;
    print(ary);

    kWayMergeSort(ary, k);

    std::cout << "sorted array: " << std::endl;
    print(ary);

    return 0;
}