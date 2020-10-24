/**
 * @file static_partial_sum.cc
 * @author Hongyu Ding
 * @brief This file is an example of static partial sum
 * @version 1.0
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

class PartialSum {
    Matrix pSum; // partial sum matrix
public:
    PartialSum(Matrix &mat) {
        pSum = std::vector<std::vector<int>>(mat.size());
        for (int i = 0; i < mat.size(); i ++) {
            pSum[i] = std::vector<int>(mat[i].size());
            for (int j = 0; j < mat[i].size(); j ++) {
                pSum[i][j] = mat[i][j];
                if (i != 0 && j != 0) {
                    pSum[i][j] = pSum[i][j] + pSum[i-1][j] + pSum[i][j-1] - pSum[i-1][j-1];
                } else if (i != 0) {
                    pSum[i][j] = pSum[i][j] + pSum[i-1][j];
                } else if (j != 0) {
                    pSum[i][j] = pSum[i][j] + pSum[i][j-1];
                }
            }
        }
    }

    /**
     * @brief Get the Region Sum object
     * want row1 <= row2 and col1 <= col2
     * 
     * @param row1 point1.x
     * @param col1 point1.y
     * @param row2 point2.x
     * @param col2 point2.y
     * @return int 
     */
    int getRegionSum(int row1, int col1, int row2, int col2) {
        int ans = pSum[row2][col2];
        if (row1 != 0 && col1 != 0) {
            ans = ans - pSum[row2][col1-1] - pSum[row1-1][col2] + pSum[row1-1][col1-1];
        } else if (row1 != 0) {
            ans = ans - pSum[row1-1][col2];
        } else if (col1 != 0) {
            ans = ans - pSum[row2][col1-1];
        }
        return ans;
    }
};

int main() {
    Matrix mat;

    // input
    int m, n;
    std::cin >> m >> n;
    mat = std::vector<std::vector<int>>(m);
    for (int i = 0; i < m; i ++) {
        mat[i] = std::vector<int>(n);
        for (int j = 0; j < n; j ++) {
            int val;
            std::cin >> val;
            mat[i][j] = val;
        }
    }

    PartialSum ps(mat);

    int k = 0;
    std::cin >> k;
    for (int i = 0; i < k; i ++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << ps.getRegionSum(x1, y1, x2, y2) << std::endl;
    }

    return 0;
}