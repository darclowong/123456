//
// Created by 王智杰 on 2025/5/30.
//
#include <stdio.h>
#include <string.h>

#define MAX_CAPACITY 1005

// 最大背包容量
int maxValue[MAX_CAPACITY];

//返回两个整数中的较大值
int maxOfTwo(int a, int b) {
    return a > b ? a : b;
}

//初始化动态规划数组
void initializeDP(int capacity) {
    memset(maxValue, 0, sizeof(int) * (capacity + 1));
}

//处理一组物品，更新动态规划表

void processGroup(int capacity, int itemCount) {
    // 临时保存当前组的数据
    int volumes[100], values[100];
    for (int i = 0; i < itemCount; ++i) {
        scanf("%d %d", &volumes[i], &values[i]);
    }

    // 倒序更新 DP 数组
    for (int j = capacity; j >= 0; --j) {
        for (int k = 0; k < itemCount; ++k) {
            if (volumes[k] <= j) {
                maxValue[j] = maxOfTwo(
                        maxValue[j],
                        maxValue[j - volumes[k]] + values[k]
                );
            }
        }
    }
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        int groupCount, capacity;
        scanf("%d %d", &groupCount, &capacity);

        // 初始化动态规划数组
        initializeDP(capacity);

        // 依次处理每组物品
        for (int i = 0; i < groupCount; ++i) {
            int itemCount;
            scanf("%d", &itemCount);
            processGroup(capacity, itemCount);
        }

        // 输出最大价值
        printf("%d\n", maxValue[capacity]);
    }

    return 0;
}
