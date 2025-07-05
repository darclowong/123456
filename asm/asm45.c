//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <limits.h>

// 计算最优矩阵乘法次数
int computeMinMultiplications(int* dims, int size) {
    if (size <= 1) return 0;

    int dp[size + 2][size + 2]; // 1-based 索引

    // 初始化 dp 数组
    for (int i = 1; i <= size; ++i) {
        for (int j = 1; j <= size; ++j) {
            if (i == j) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = INT_MAX;
            }
        }
    }

    // 按链长从小到大处理
    for (int l = 2; l <= size; ++l) {
        for (int i = 1; i <= size - l + 1; ++i) {
            int j = i + l - 1;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[1][size];
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int dims[n + 1]; // 存储每个矩阵的列数（dims[0] 为第一个矩阵的行数）

        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            if (i == 0) {
                dims[0] = x;
                dims[1] = y;
            } else {
                dims[i + 1] = y;
            }
        }

        int result = computeMinMultiplications(dims, n);
        printf("%d\n", result);
    }

    return 0;
}
