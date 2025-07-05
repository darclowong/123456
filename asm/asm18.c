//
// Created by 王智杰 on 2025/5/29.
//
//
// Created by 王智杰 on 2025/5/30.
// 混合背包问题实现：支持 0-1、完全、多重背包
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 200000

int dp[MAX_CAPACITY + 1]; // dp[j]: 容量 j 下的最大价值

// 更新函数：用于 0-1 背包和多重背包（逆序）
void processBoundedItem(int vol, int val, int cap) {
    for (int j = cap; j >= vol; --j) {
        if (dp[j - vol] + val > dp[j]) {
            dp[j] = dp[j - vol] + val;
        }
    }
}

// 更新函数：用于完全背包（顺序）
void processUnboundedItem(int vol, int val, int cap) {
    for (int j = vol; j <= cap; ++j) {
        if (dp[j - vol] + val > dp[j]) {
            dp[j] = dp[j - vol] + val;
        }
    }
}

// 处理多重背包（二进制拆分）
void processMultipleItem(int volume, int value, int count, int capacity) {
    int remaining = count;
    int power = 1;

    while (remaining > 0) {
        int take = (remaining < power) ? remaining : power;
        int v = volume * take;
        int w = value * take;

        processBoundedItem(v, w, capacity);

        remaining -= take;
        power *= 2;
    }
}

int main() {
    int N, C;

    while (scanf("%d %d", &N, &C) != EOF) {
        // 初始化 dp 数组
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < N; ++i) {
            int vi, wi, mi;
            scanf("%d %d %d", &vi, &wi, &mi);

            if (mi == 1) {
                // 0-1 背包：视为只取一件
                processBoundedItem(vi, wi, C);
            } else if (mi > 1) {
                // 多重背包：二进制优化处理
                processMultipleItem(vi, wi, mi, C);
            } else if (mi == -1) {
                // 完全背包：可无限选取
                processUnboundedItem(vi, wi, C);
            }
        }

        printf("%d\n", dp[C]);
    }

    return 0;
}
