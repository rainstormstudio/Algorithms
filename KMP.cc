#include <iostream>
#include <string>

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

void KMP(std::string str, std::string pattern) {
    int n = str.length();
    int m = pattern.length();

    int lps[m]; // longest prefix suffix length for pattern
    calcLPS(lps, m, pattern);

    int i = 0, j = 0;
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