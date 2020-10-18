/**
 * @file quick_power.cc
 * @author Hongyu Ding
 * @brief This is the code of quick power
 * A.K.A exponential by squaring
 * @version 1.0
 * @date 2020-10-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>

/**
 * @brief qpower_recursion returns x^n
 * O(log n)
 * 
 * @param x base
 * @param n exponent
 * @param mod 
 * @return long long 
 */
long long qpower_recursion(long long x, long long n, long long mod) {
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n & 1) return qpower_recursion(x, n - 1, mod) * x % mod;
    long long temp = qpower_recursion(x, n >> 1, mod) % mod;
    return temp * temp % mod;
}

/**
 * @brief qpower returns x^n
 * O(log n)
 * 
 * @param x base
 * @param n exponent
 * @return long long 
 */
double qpower(double x, long long n) {
    if (n < 0) {
        x = 1 /x;
        n = -n;
    }
    if (n == 0) return 1;
    int temp = 1;
    while (n > 1) {
        if (n & 1) {
            temp *= x;
            x *= x;
            n = (n - 1) >> 1;
        } else {
            x *= x;
            n = n >> 1;
        }
    }
    return x * temp;
}

int main() {
    double x;
    long long n;
    std::cin >> x >> n;

    std::cout << qpower(x, n) << std::endl;

    return 0;
}