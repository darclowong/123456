//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/**
 * 计算 (base^exponent) % modulus 使用迭代快速幂算法
 * @param base 底数
 * @param exponent 指数
 * @param modulus 模数
 * @return 计算结果
 */
long long modularExponentiation(long long base, long long exponent, long long modulus) {
    // 优化点：使用迭代替代递归实现
    long long result = 1;
    base = base % modulus;

    // 优化点：使用while循环替代for循环
    while (exponent > 0) {
        // 优化点：使用位运算代替取模
        if (exponent & 1) {
            result = (result * base) % modulus;
        }

        // 优化点：使用位移替代除法
        exponent >>= 1;
        base = (base * base) % modulus;
    }

    return result;
}

/**
 * 使用费马小定理测试素数
 * @param n 待测试的整数
 * @param iterations 测试次数
 * @return 是否可能为素数
 */
int isFermatPrime(long long n, int iterations) {
    // 特殊情况处理
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0) return 0;

    // 优化点：使用do-while实现随机测试
    do {
        // 选择随机基数a
        long long a = 2 + rand() % (n - 3);

        // 如果a^(n-1) % n ≠ 1，则n不是素数
        if (modularExponentiation(a, n - 1, n) != 1) {
            return 0;  // 合数
        }

        iterations--;
    } while (iterations > 0);

    return 1;  // 可能为素数
}

/**
 * 处理单个测试用例
 * @param n 待测试的整数
 */
void processTestCase(long long n) {
    // 优化点：使用三元运算符简化逻辑
    const char* result = isFermatPrime(n, 5) ? "yes" : "no";
    printf("%s\n", result);
}

int main() {
    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 优化点：使用while循环替代for循环
    long long inputNumber;
    while (scanf("%lld", &inputNumber) != EOF) {
        processTestCase(inputNumber);
    }

    return 0;
}
