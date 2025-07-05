//
// Created by 王智杰 on 2025/6/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 20

int main() {
    int n;
    char op[MAXN];
    int val[MAXN];

    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %c %d", &op[i], &val[i]);
    }

    int max_score = INT_MIN;

    // 枚举删除的边位置 k
    for (int k = 0; k < n; ++k) {
        int new_val[MAXN];
        char new_op[MAXN];

        // 构造新的顶点数组
        for (int i = 0; i < n; ++i) {
            new_val[i] = val[(k + i) % n];
        }

        // 构造新的边数组
        for (int i = 0; i < n - 1; ++i) {
            new_op[i] = op[(k + i + 1) % n];
        }

        // 初始化 DP 数组
        int max_dp[MAXN][MAXN];
        int min_dp[MAXN][MAXN];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                max_dp[i][j] = min_dp[i][j] = 0;

        // 初始条件
        for (int i = 0; i < n; ++i)
            max_dp[i][i] = min_dp[i][i] = new_val[i];

        // 区间 DP
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                max_dp[i][j] = INT_MIN;
                min_dp[i][j] = INT_MAX;

                for (int k_split = i; k_split < j; ++k_split) {
                    char op = new_op[k_split];  // 分割点对应的边
                    int a_max = max_dp[i][k_split];
                    int a_min = min_dp[i][k_split];
                    int b_max = max_dp[k_split + 1][j];
                    int b_min = min_dp[k_split + 1][j];

                    if (op == '+') {
                        int current_max = a_max + b_max;
                        int current_min = a_min + b_min;

                        if (current_max > max_dp[i][j])
                            max_dp[i][j] = current_max;
                        if (current_min < min_dp[i][j])
                            min_dp[i][j] = current_min;
                    } else {  // '*'
                        int candidates[4];
                        candidates[0] = a_max * b_max;
                        candidates[1] = a_max * b_min;
                        candidates[2] = a_min * b_max;
                        candidates[3] = a_min * b_min;

                        int current_max = candidates[0];
                        int current_min = candidates[0];

                        for (int c = 1; c < 4; ++c) {
                            if (candidates[c] > current_max)
                                current_max = candidates[c];
                            if (candidates[c] < current_min)
                                current_min = candidates[c];
                        }

                        if (current_max > max_dp[i][j])
                            max_dp[i][j] = current_max;
                        if (current_min < min_dp[i][j])
                            min_dp[i][j] = current_min;
                    }
                }
            }
        }

        if (max_dp[0][n - 1] > max_score)
            max_score = max_dp[0][n - 1];
    }

    printf("%d\n", max_score);

    return 0;
}
