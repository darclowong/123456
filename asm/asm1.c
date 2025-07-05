//
// Created by 王智杰 on 2025/3/27.
//
//Description
//        给定n个矩阵{ A1，A2，…，An }，保证Ai与Ai+1是可乘的，i = 1，2，…，n-1。考察这n个矩阵的连乘积A1A2…An。由于矩阵乘法满足结合律，故计算矩阵的连乘积可以有许多不同的计算次序。这种计算次序可以用加括号的方式来确定。现要求设计一个高效的算法，对给定的n个矩阵确定一个计算次序使得总的乘法次数最少，并输出该最优值。‪‬‪‬‪‬‪‬‪‬‮‬‪‬‫‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‫‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‭‬‪‬‪‬‪‬‪‬‪‬‮‬‫‬‭‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‭‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‫‬‪‬‪‬‪‬‪‬‪‬‮‬‫‬‪‬
//
//Input
//第一行是单独一个n ( 1 ≤ n ≤ 600 )，表示矩阵的个数。接下来第n行，依序分别对应第i个矩阵，每行包括两个整数xi，yi (1 ≤ i ≤ n，1 ≤ xi , yi ≤ 100 )，表示该矩阵的行数和列数。保证n个矩阵依序是可乘的。‪‬‪‬‪‬‪‬‪‬‮‬‪‬‫‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‫‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‭‬‪‬‪‬‪‬‪‬‪‬‮‬‫‬‭‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‭‬‪‬‪‬‪‬‪‬‪‬‮‬‪‬‫‬‪‬‪‬‪‬‪‬‪‬‮‬‫‬‪‬
//
//Output
//        输出一个整数，表示最少需要的乘法次数。 运算过程及结果不会超出int范围
//Sample Input
//4
//50 10
//10 40
//40 30
//30 5
//Sample Output
//10500
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int* p = (int*)malloc((n + 1) * sizeof(int));
    scanf("%d %d", &p[0], &p[1]);
    int i;
    for (i = 2; i <= n; i++) {
        int x;
        scanf("%d %d", &x, &p[i]);
    }

    int** m = (int**)malloc((n + 1) * sizeof(int*));
//    int i;
    for (i = 0; i <= n; i++) {
        m[i] = (int*)malloc((n + 1) * sizeof(int));
    }
//    int i;
    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    int L, j, k, temp;
    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++) {
                temp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (temp < m[i][j]) {
                    m[i][j] = temp;
                }
            }
        }
    }

    printf("%d\n", m[1][n]);

    return 0;
}
