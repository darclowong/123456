//
// Created by 王智杰 on 2025/5/29.
// 修改版多重背包实现：风格重构 + 独立实现
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define MAX_CAPACITY 100000
//
//int dp[MAX_CAPACITY];
//
//// 物品类结构体
//typedef struct {
//    int weight;
//    int value;
//} Item;
//
//// 更新 dp 数组（0-1 背包逻辑）
//void updateKnapsack(int capacity, int weight, int value) {
//    for (int j = capacity; j >= weight; --j) {
//        if (dp[j - weight] + value > dp[j]) {
//            dp[j] = dp[j - weight] + value;
//        }
//    }
//}
//
//int main() {
//    int testCases;
//    scanf("%d", &testCases);
//
//    for (int caseNumber = 1; caseNumber <= testCases; ++caseNumber) {
//        int itemTypes, capacity;
//        scanf("%d %d", &itemTypes, &capacity);
//
//        // 初始化 dp 数组
//        memset(dp, 0, sizeof(dp));
//
//        // 处理每种物品
//        for (int i = 0; i < itemTypes; ++i) {
//            int weight, value, count;
//            scanf("%d %d %d", &weight, &value, &count);
//
//            // 二进制拆分处理
//            int remaining = count;
//            int multiplier = 1;
//
//            while (remaining > 0) {
//                int take = (remaining < multiplier) ? remaining : multiplier;
//                Item newItem;
//                newItem.weight = weight * take;
//                newItem.value = value * take;
//
//                updateKnapsack(capacity, newItem.weight, newItem.value);
//
//                remaining -= take;
//                multiplier *= 2;
//            }
//        }
//
//        printf("%d\n", dp[capacity]);
//    }
//
//    return 0;
//}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 100000

int dp[MAX_CAPACITY]; // 动态规划数组：dp[j] 表示容量 j 下的最大价值

// 单个物品结构体
typedef struct {
    int weight;
    int value;
} Item;

// 处理单个虚拟物品（0-1 背包逻辑）
void processItem(int capacity, int itemWeight, int itemValue) {
    int current = capacity;
    while (current >= itemWeight) {
        if (dp[current - itemWeight] + itemValue > dp[current]) {
            dp[current] = dp[current - itemWeight] + itemValue;
        }
        current--;
    }
}

// 拆分并处理原始物品
void splitAndProcess(int capacity, int baseWeight, int baseValue, int count) {
    int remaining = count;
    int power = 1;

    while (remaining > 0) {
        int take = (remaining < power) ? remaining : power;
        Item virtualItem;
        virtualItem.weight = baseWeight * take;
        virtualItem.value = baseValue * take;

        processItem(capacity, virtualItem.weight, virtualItem.value);

        remaining -= take;
        power *= 2;
    }
}

// 初始化 DP 数组
void resetDPArray(int capacity) {
    for (int i = 0; i <= capacity; ++i) {
        dp[i] = 0;
    }
}

int main() {
    int totalCases;
    scanf("%d", &totalCases);

    for (int caseId = 1; caseId <= totalCases; ++caseId) {
        int itemTypeCount, backpackCapacity;
        scanf("%d %d", &itemTypeCount, &backpackCapacity);

        resetDPArray(backpackCapacity);

        for (int i = 0; i < itemTypeCount; ++i) {
            int itemWeight, itemValue, itemCount;
            scanf("%d %d %d", &itemWeight, &itemValue, &itemCount);

            splitAndProcess(backpackCapacity, itemWeight, itemValue, itemCount);
        }

        printf("%d\n", dp[backpackCapacity]);
    }

    return 0;
}