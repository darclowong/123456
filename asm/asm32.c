//
// Created by 王智杰 on 2025/6/8.
//
#include <stdio.h>

/**
 * 矩阵相乘函数：a * b = result
 * @param a 第一个矩阵 (2x2)
 * @param b 第二个矩阵 (2x2)
 * @param result 结果矩阵 (2x2)
 */
void multiply(int a[2][2], int b[2][2], int result[2][2]) {
    int a11 = a[0][0], a12 = a[0][1];
    int a21 = a[1][0], a22 = a[1][1];
    int b11 = b[0][0], b12 = b[0][1];
    int b21 = b[1][0], b22 = b[1][1];

    result[0][0] = a11 * b11 + a12 * b21;
    result[0][1] = a11 * b12 + a12 * b22;
    result[1][0] = a21 * b11 + a22 * b21;
    result[1][1] = a21 * b12 + a22 * b22;
}

/**
 * 矩阵快速幂函数：base^power = result
 * @param base 基础矩阵 (2x2)
 * @param power 幂次
 * @param result 结果矩阵 (2x2)
 */
void matrixPower(int base[2][2], int power, int result[2][2]) {
    // 初始化为单位矩阵
    result[0][0] = 1; result[0][1] = 0;
    result[1][0] = 0; result[1][1] = 1;

    while (power > 0) {
        if (power % 2 == 1) {
            int temp[2][2];
            multiply(result, base, temp);
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    result[i][j] = temp[i][j];
        }
        int temp[2][2];
        multiply(base, base, temp);
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                base[i][j] = temp[i][j];
        power /= 2;
    }
}

/**
 * 计算斐波那契数列第 n 项
 * @param n 第 n 项
 * @return F(n)
 */
int fibonacci(int n) {
    if (n == 0) return 0;
    int base[2][2] = {{1, 1}, {1, 0}};
    int powered[2][2];
    matrixPower(base, n - 1, powered);
    return powered[0][0]; // 返回矩阵左上角元素即为 F(n)
}

/**
 * 主函数：读取输入并输出结果
 */
int main() {
    int i;
    while (scanf("%d", &i) != EOF) {
        printf("%d\n", fibonacci(i));
    }
    return 0;
}
