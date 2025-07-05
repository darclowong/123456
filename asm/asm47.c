//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 计算背包最大价值
 * @param itemCount 物品数量
 * @param capacity 背包容量
 * @param weights 重量数组
 * @param values 价值数组
 * @return 最大价值
 */
int calculateMaxValue(int itemCount, int capacity, int* weights, int* values) {
    // 创建动态规划数组并初始化
    int* currentValue = (int*)calloc(capacity + 1, sizeof(int));
    if (!currentValue) return 0;

    // 遍历每个物品
    for (int i = 0; i < itemCount; i++) {
        int weight = weights[i];
        int value = values[i];

        // 从后向前更新dp数组
        for (int j = capacity; j >= weight; j--) {
            // 选择放入当前物品时的价值更大则更新
            if (currentValue[j - weight] + value > currentValue[j]) {
                currentValue[j] = currentValue[j - weight] + value;
            }
        }
    }

    int result = currentValue[capacity];
    free(currentValue);
    return result;
}

int main() {
    int T; // 测试用例数量
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int itemCount, capacity;
        scanf("%d %d", &itemCount, &capacity);

        // 动态分配物品数组
        int* weights = (int*)malloc(itemCount * sizeof(int));
        int* values = (int*)malloc(itemCount * sizeof(int));

        // 读取物品数据
        for (int i = 0; i < itemCount; i++) {
            scanf("%d %d", &weights[i], &values[i]);
        }

        // 计算并输出结果
        int maxValue = calculateMaxValue(itemCount, capacity, weights, values);
        printf("%d\n", maxValue);

        // 释放内存
        free(weights);
        free(values);
    }

    return 0;
}
