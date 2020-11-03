/**
 * @file fast_fourier_transform.cc
 * @author Hongyu Ding
 * @brief This is the implementation of Fast Fourier Transform
 * @version 0.1
 * @date 2020-11-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>
#include <complex>
#include <math.h>

using List = std::vector<std::complex<double>>;
const std::complex<double> i(0, 1);

std::complex<double> M(int N, int exp) {
    return std::exp(2 * M_PI / N * exp * i);
}

void print_complex(std::complex<double> c) {
    double x = c.real();
    double y = c.imag();
    if (x == 0 && y == 0) {
        std::cout << "0" << std::endl;
    } else if (x == 0) {
        if (y == 1) {
            std::cout << "i" << std::endl;
        } else if (y == -1) {
            std::cout << "-i" << std::endl;
        } else {
            std::cout << std::showpos << y << "i" << std::endl;
        }
    } else if (y == 0) {
        std::cout << x << std::endl;
    } else {
        std::cout << std::noshowpos << x;
        if (y == 1) {
            std::cout << "+i" << std::endl;
        } else if (y == -1) {
            std::cout << "-i" << std::endl;
        } else {
            std::cout << std::showpos << y << "i" << std::endl;
        }
    }
}

/**
 * @brief fft (Fast Fourier Transform)
 * O(n log n)
 * 
 * @param f data set
 * @return List 
 */
List fft(List &f) {
    List ans;
    if (f.size() == 1) {
        ans.push_back(f[0]);
        return ans;
    } else {
        List g, h;
        int N = static_cast<int>(f.size());
        for (int n = 0; n < f.size() / 2; n ++) {
            g.push_back(1.0/2.0 * (f[n] + f[n + N / 2]));
            h.push_back(1.0/2.0 * (f[n] - f[n + N / 2]) * M(N, -n));
        }
        ans = List(N);
        List temp = fft(g);
        for (int i = 0; i < N; i += 2) {
            ans[i] = temp[i / 2];
        }
        temp = fft(h);
        for (int i = 1; i < N; i += 2) {
            ans[i] = temp[i / 2];
        }
        return ans;
    }
}

int main() {
    List f = {{2, 0}, {0, 2}, {0, -2}, {6, 0}, {2, 0}, {0, 2}, {0, -2}, {6, 0}};

    List F = fft(f);

    for (std::complex<double> &x : F) {
        print_complex(x);
    }

    return 0;
}