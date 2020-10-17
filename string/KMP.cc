/**
 * @file KMP.cc
 * @author Hongyu Ding
 * @brief This is the code of Knuth-Morris-Pratt algorithm.
 * It searches for occurrences of a pattern within a string.
 * @version 1.0
 * @date 2020-10-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <string>

/**
 * @brief calcLPS modifies the array lps and makes it 
 * an array of longest prefix suffix values for pattern
 * 
 * @param lps longest prefix suffix array
 * @param m the length of the lps
 * @param pattern the string
 */
void calcLPS(int* lps, int m, std::string pattern) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len ++;
            lps[i] = len;
            i ++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i ++;
            }
        }
    }
}

/**
 * @brief KMP runs Knuth-Morris-Pratt algorithm and it
 * outputs the positions of pattern in str
 * O(m + n)
 * 
 * @param str the main text string
 * @param pattern the substring we want to find in str
 */
void KMP(std::string str, std::string pattern) {
    int n = str.length();
    int m = pattern.length();

    int lps[m]; // longest prefix suffix length for pattern
    calcLPS(lps, m, pattern);   // preprocess the pattern

    int i = 0, j = 0; // i is the index for str, j is the index for pattern
    while (i < n) {
        if (pattern[j] == str[i]) {
            i ++; j ++;
        }
        if (j == m) {
            std::cout << "Found pattern at " << i - j << std::endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != str[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
}

int main() {
    std::string str, pattern;
    std::getline(std::cin, str);
    std::getline(std::cin, pattern);

    KMP(str, pattern);

    return 0;
}