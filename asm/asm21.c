//
// Created by 王智杰 on 2025/6/4.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 计算最大子段和
 * @param nums 输入数组
 * @param n 数组长度
 * @return 最大子段和（当所有数为负数时返回0）
 */
int findMaxSubarraySum(const int* nums, int n) {
    int maxSum = 0;      // 存储全局最大值
    int currentSum = 0;  // 存储当前子数组和

    for (int i = 0; i < n; i++) {
        currentSum += nums[i];

        // 如果当前和为负数则重置为0
        if (currentSum < 0) {
            currentSum = 0;
        }

        // 更新全局最大值
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    return maxSum;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        // 动态分配数组空间
        int* numbers = (int*)malloc(n * sizeof(int));
        if (!numbers) {
            fprintf(stderr, "Memory allocation failed");
            return 1;
        }

        // 读取数组元素
        for (int i = 0; i < n; i++) {
            scanf("%d", &numbers[i]);
        }

        // 计算并输出结果
        int result = findMaxSubarraySum(numbers, n);
        printf("%d\n", result);

        // 释放内存
        free(numbers);
    }

    return 0;
}
