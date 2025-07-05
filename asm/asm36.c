//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, C;
        scanf("%d %d", &n, &C);

        int *weights = (int *)malloc(n * sizeof(int));
        int *values = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &weights[i], &values[i]);
        }

        int *dp = (int *)calloc(C + 1, sizeof(int));

        for (int i = 0; i < n; i++) {
            int w = weights[i];
            int v = values[i];

            // 从后往前更新dp数组
            for (int j = C; j >= w; j--) {
                dp[j] = max(dp[j], dp[j - w] + v);
            }
        }

        printf("%d\n", dp[C]);

        // 释放内存
        free(dp);
        free(weights);
        free(values);
    }

    return 0;
}
