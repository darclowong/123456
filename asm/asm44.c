//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 计算最长公共子序列长度
 * @param X 第一个字符串
 * @param Y 第二个字符串
 * @return LCS长度
 */
int compute_lcs_length(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);

    // 动态分配一维DP数组
    int *dp = (int *)calloc(n + 1, sizeof(int));

    // 逐行更新DP数组
    for (int i = 1; i <= m; ++i) {
        int prev = dp[0];  // 保存左上角值

        for (int j = 1; j <= n; ++j) {
            int current = dp[j];

            // 状态转移方程
            if (X[i-1] == Y[j-1]) {
                dp[j] = prev + 1;  // 字符匹配时
            } else {
                // 取上边或左边的最大值
                dp[j] = (dp[j] > dp[j-1]) ? dp[j] : dp[j-1];
            }

            prev = current;  // 更新左上角值
        }
    }

    int result = dp[n];  // 最终结果
    free(dp);            // 释放内存
    return result;
}


void process_test_case(int case_num) {
    char X[1001], Y[1001];
    scanf("%s", X);
    scanf("%s", Y);

    int lcs_length = compute_lcs_length(X, Y);
    printf("%d\n",lcs_length);
}

int main() {
    int T;
    scanf("%d", &T);

    // 逐个处理测试用例
    for (int i = 1; i <= T; ++i) {
        process_test_case(i);
    }

    return 0;
}
