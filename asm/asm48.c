//
// Created by 王智杰 on 2025/6/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义动态规划数组类型
typedef unsigned char bool;

int main() {
    int T;
    scanf("%d", &T);

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int n;
        int c1, c2;
        scanf("%d", &n);
        scanf("%d %d", &c1, &c2);

        int* weights = (int*)malloc(n * sizeof(int));
        int sum_total = 0;

        for (int i = 0; i < n; ++i) {
            scanf("%d", &weights[i]);
            sum_total += weights[i];
        }

        printf("Case %d:\n", caseNum);

        // 总重量超过两船总载重，直接不可行
        if (sum_total > c1 + c2) {
            printf("No\n");
            free(weights);
            continue;
        }

        // 确定搜索区间 [low, high]
        int low = (sum_total - c2 > 0) ? (sum_total - c2) : 0;
        int high = (c1 < sum_total) ? c1 : sum_total;

        if (high < low) {
            printf("No\n");
            free(weights);
            continue;
        }

        // 动态规划数组
        bool* dp = (bool*)calloc(high + 1, sizeof(bool));
        dp[0] = 1; // 初始：可以构造空集

        for (int i = 0; i < n; ++i) {
            int w = weights[i];
            for (int j = high; j >= w; --j) {
                if (dp[j - w]) {
                    dp[j] = 1;
                }
            }
        }

        // 查找最大可行解
        int result = -1;
        for (int s = high; s >= low; --s) {
            if (dp[s]) {
                result = s;
                break;
            }
        }

        free(dp);
        free(weights);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("No\n");
        }
    }

    return 0;
}
