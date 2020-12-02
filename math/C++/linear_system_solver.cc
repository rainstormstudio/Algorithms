/**
 * @file linear_system_solver.cc
 * @author Hongyu Ding
 * @brief This is the code for a linear system solver
 * @version 0.1
 * @date 2020-11-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <vector>
#include <iostream>
#include <iomanip>

using Vector = std::vector<double>;

class Matrix {
    std::vector<std::vector<double>> mat;
    unsigned int rows;
    unsigned int cols;
public:
    Matrix(std::vector<std::vector<int>> ary) {
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
};


class LSsolver {

public:
    static Vector inputVector(int n) {
        Vector vec = Vector(n, 0);
        for (int i = 0; i < n; i ++) {
            std::cin >> vec[i];
        }
        return vec;
    }

    static void outputVector(Vector &vec) {
        int len = vec.size();
        for (int i = 0; i < len; i ++) {
            std::cout << std::setw(10);
            std::cout << vec[i] << std::endl;
        }
    }

    /**
     * @brief Gaussian Elimination changes A to a matrix
     * which upper triangle is U and lower triangle is L, 
     * and changes b to the corresponding new b';
     * system: Ax = b
     * requires A.size() == b.size()
     * O(n^3)
     * 
     * @param A coefficient matrix
     * @param b right-hand side
     */
    static void GE(Matrix &A, Vector &b) {
        int N = A.size();
        for (int i = 0; i < N; i ++) {
            for (int k = i + 1; k < N; k ++) {
                double mult = A[k][i] / A[i][i];
                A[k][i] = mult;
                for (int j = i + 1; j < N; j ++) {
                    A[k][j] = A[k][j] - mult * A[i][j];
                }
                b[k] = b[k] - mult * b[i];
            }
        }
    }

    /**
     * @brief Forward Solve: 
     * solves system Ly = b for y
     * requires L.size() == b.size()
     * O(n^2)
     * 
     * @param L lower triangle
     * @param b RHS
     * @return Vector 
     */
    static Vector forwardSolve(Matrix &L, Vector &b) {
        int N = L.size();
        Vector y = Vector(N);
        for (int i = 0; i < N; i ++) {
            y[i] = b[i];
            for (int j = 0; j < i; j ++) {
                y[i] = y[i] - L[i][j] * y[j];
            }
        }
        return y;
    }

    /**
     * @brief Back Solve:
     * solves system Ux = y for x
     * requires U.size() == y.size()
     * O(n^2)
     * 
     * @param U upper triangle
     * @param y RHS
     * @return Vector 
     */
    static Vector backSolve(Matrix &U, Vector &y) {
        int N = U.size();
        Vector x = Vector(N);
        for (int i = N - 1; i >= 0; i --) {
            x[i] = y[i];
            for (int j = i + 1; j < N; j ++) {
                x[i] = x[i] - U[i][j] * x[j];
            }
            x[i] /= U[i][i];
        }
        return x;
    }

    static Vector solve(Matrix &A, Vector &b) {
        GE(A, b);
        Vector x = backSolve(A, b);
        return x;
    }
};

int main() {
    std::cout << "solve linear system Ax = b:\n";
    std::cout << "input A:\n";
    Matrix A(std::cin);
    std::cout << "input b:\n";
    Vector b = LSsolver::inputVector(A.size());

    Vector x = LSsolver::solve(A, b);

    std::cout << "L & U:\n";
    A.output(std::cout, 10, 5);
    std::cout << "new b:\n";
    LSsolver::outputVector(b);
    std::cout << "ans x = \n";
    LSsolver::outputVector(x);
    return 0;
}