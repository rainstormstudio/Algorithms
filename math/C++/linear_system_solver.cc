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
using Matrix = std::vector<Vector>;

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

    static Matrix inputMatrix(int n, int m) {
        Matrix mat = Matrix(n);
        for (int i = 0; i < n; i ++) {
            mat[i] = Vector(m, 0);
            for (int j = 0; j < m; j ++) {
                std::cin >> mat[i][j];
            }
        }
        return mat;
    }

    static void outputMatrix(Matrix &mat) {
        int n = mat.size(), m = mat[0].size();
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                std::cout << std::setw(10);
                std::cout << mat[i][j];
            }
            std::cout << std::endl;
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
    Matrix A;
    Vector b;
    int n, m;
    std::cout << "solve linear system Ax = b:\n";
    std::cout << "input A:\n";
    std::cout << "n = ";
    std::cin >> n;
    std::cout << "m = ";
    std::cin >> m;
    std::cout << "matrix = \n";
    A = LSsolver::inputMatrix(n, m);
    std::cout << "input b:\n";
    b = LSsolver::inputVector(n);

    Vector x = LSsolver::solve(A, b);

    std::cout << "L & U:\n";
    LSsolver::outputMatrix(A);
    std::cout << "new b:\n";
    LSsolver::outputVector(b);
    std::cout << "ans x = \n";
    LSsolver::outputVector(x);
    return 0;
}