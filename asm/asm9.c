//
// Created by 王智杰 on 2025/5/31.
//
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1005

// LCS 表，记录不同子问题的结果
int lcsTable[MAX_LEN][MAX_LEN];


// 返回两个整数中的较大值
int maxOfTwo(int a, int b) {
    return a > b ? a : b;
}


// 计算两个字符串的最长公共子序列长度

int computeLCSLength(char* strX, char* strY) {
    int lenX = strlen(strX);
    int lenY = strlen(strY);

    // 初始化表
    for (int i = 0; i <= lenX; ++i)
        for (int j = 0; j <= lenY; ++j)
            lcsTable[i][j] = 0;

    // 填充 DP 表
    for (int i = 1; i <= lenX; ++i) {
        for (int j = 1; j <= lenY; ++j) {
            if (strX[i - 1] == strY[j - 1]) {
                lcsTable[i][j] = lcsTable[i - 1][j - 1] + 1;
            } else {
                lcsTable[i][j] = maxOfTwo(lcsTable[i - 1][j], lcsTable[i][j - 1]);
            }
        }
    }

    // 返回最终结果
    return lcsTable[lenX][lenY];
}


int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        char strX[1005], strY[1005];
        scanf("%s %s", strX, strY);

        int result = computeLCSLength(strX, strY);
        printf("%d\n", result);
    }

    return 0;
}
