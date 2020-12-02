/**
 * @file matrix.cc
 * @author Hongyu Ding
 * @brief This defines a matrix class
 * @version 0.1
 * @date 2020-12-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <iomanip>
#include <vector>

class Matrix {
    std::vector<std::vector<double>> mat;
    unsigned int rows;
    unsigned int cols;
public:
    Matrix(std::vector<std::vector<double>> ary) {
        rows = ary.size();
        cols = ary[0].size();
        mat = std::vector<std::vector<double>>(rows);
        for (int i = 0; i < rows; i ++) {
            mat[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j ++) {
                mat[i][j] = ary[i][j];
            }
        }
    }

    Matrix(unsigned int rows, unsigned int cols) 
        : rows{rows}, cols{cols} {
        mat = std::vector<std::vector<double>>(rows);
        for (int i = 0; i < rows; i ++) {
            mat[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j ++) {
                mat[i][j] = 0.0;
            }
        }
    }

    Matrix(unsigned int rows, unsigned int cols, double val) 
        : rows{rows}, cols{cols} {
        mat = std::vector<std::vector<double>>(rows);
        for (int i = 0; i < rows; i ++) {
            mat[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j ++) {
                mat[i][j] = val;
            }
        }
    }

    Matrix(std::istream &in) {
        in >> rows;
        in >> cols;
        mat = std::vector<std::vector<double>>(rows);
        for (int i = 0; i < rows; i ++) {
            mat[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j ++) {
                in >> mat[i][j];
            }
        }
    }

    Matrix(const Matrix &mat2) {
        rows = mat2.getRows();
        cols = mat2.getCols();
        mat = std::vector<std::vector<double>>(rows);
        for (int i = 0; i < rows; i ++) {
            mat[i] = std::vector<double>(cols);
            for (int j = 0; j < cols; j ++) {
                mat[i][j] = mat2[i][j];
            }
        }
    }

    int getRows() const { return rows; }

    int size() const { return rows; }

    int getCols() const { return cols; }

    std::vector<std::vector<double>> getMat() {
        return mat;
    }

    std::vector<double>& operator[](std::size_t index) {
        return mat[index];
    }

    const std::vector<double>& operator[](std::size_t index) const {
        return mat[index];
    }

    Matrix& operator=(const Matrix& mat2) {
        if (this != &mat2) {
            rows = mat2.getRows();
            cols = mat2.getCols();
            mat.resize(rows);
            for (int i = 0; i < rows; i ++) {
                mat[i].resize(cols);
            }
            for (int i = 0; i < rows; i ++) {
                for (int j = 0; j < cols; j ++) {
                    mat[i][j] = mat2[i][j];
                }
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& mat2) {
        Matrix ans(rows, cols);
        if (rows == mat2.getRows() && cols == mat2.getCols()) {
            for (int i = 0; i < rows; i ++) {
                for (int j = 0; j < cols; j ++) {
                    ans[i][j] = mat[i][j] + mat2[i][j];
                }
            }
        }
        return ans;
    }

    Matrix& operator+=(const Matrix& mat2) {
        if (rows == mat2.getRows() && cols == mat2.getCols()) {
            for (int i = 0; i < rows; i ++) {
                for (int j = 0; j < cols; j ++) {
                    mat[i][j] += mat2[i][j];
                }
            }
        }
        return *this;
    }

    Matrix operator-(const Matrix& mat2) {
        Matrix ans(rows, cols);
        if (rows == mat2.getRows() && cols == mat2.getCols()) {
            for (int i = 0; i < rows; i ++) {
                for (int j = 0; j < cols; j ++) {
                    ans[i][j] = mat[i][j] - mat2[i][j];
                }
            }
        }
        return ans;
    }

    Matrix& operator-=(const Matrix& mat2) {
        if (rows == mat2.getRows() && cols == mat2.getCols()) {
            for (int i = 0; i < rows; i ++) {
                for (int j = 0; j < cols; j ++) {
                    mat[i][j] -= mat2[i][j];
                }
            }
        }
        return *this;
    }

    Matrix operator*(const Matrix& mat2) {
        Matrix ans(rows, mat2.getCols());
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < mat2.getCols(); j ++) {
                for (int k = 0; k < cols; k ++) {
                    ans[i][j] += mat[i][k] * mat2[k][j];
                }
            }
        }
        return ans;
    }

    Matrix& operator*=(const Matrix& mat2) {
        Matrix ans = (*this) * mat2;
        (*this) = ans;
        return *this;
    }

    Matrix operator+(const double val) {
        Matrix ans(rows, cols);
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                ans[i][j] = mat[i][j] + val;
            }
        }
        return ans;
    }

    Matrix operator-(const double val) {
        Matrix ans(rows, cols);
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                ans[i][j] = mat[i][j] - val;
            }
        }
        return ans;
    }

    Matrix operator*(const double val) {
        Matrix ans(rows, cols);
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                ans[i][j] = mat[i][j] * val;
            }
        }
        return ans;
    }

    Matrix operator/(const double val) {
        Matrix ans(rows, cols);
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                ans[i][j] = mat[i][j] / val;
            }
        }
        return ans;
    }

    std::vector<int> operator*(const std::vector<double> &vec) {
        std::vector<int> ans(vec.size(), 0.0);
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                ans[i] = mat[i][j] * vec[j];
            }
        }
        return ans;
    }

    Matrix transpose() {
        Matrix ans(cols, rows);
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                ans[j][i] = mat[i][j];
            }
        }
        return ans;
    }

    static Matrix identity(int n) {
        Matrix ans(n, n);
        for (int i = 0; i < n; i ++) {
            ans[i][i] = 1;
        }
        return ans;
    }

    std::vector<double> getDiagonal() {
        int n = std::min(rows, cols);
        std::vector<double> ans(n, 0.0);
        for (int i = 0; i < n; i ++) {
            ans[i] = mat[i][i];
        }
        return ans;
    }

    void output(std::ostream &out, int width, int precision) {
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                out << std::setw(width) << std::setprecision(precision) << mat[i][j];
            }
            out << std::endl;
        }
    }

    Matrix getLU() {
        Matrix ans(mat);
        if (rows != cols) return ans;
        int N = rows;
        for (int i = 0; i < N; i ++) {
            for (int k = i + 1; k < N; k ++) {
                double mult = ans[k][i] / ans[i][i];
                ans[k][i] = mult;
                for (int j = i + 1; j < N; j ++) {
                    ans[k][j] = ans[k][j] - mult * ans[i][j];
                }
            }
        }
        return ans;
    }
};

int main() {
    Matrix A(std::cin);
    Matrix U = A.getLU();
    U.output(std::cout, 10, 5);
    return 0;
}