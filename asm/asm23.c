////
//// Created by 王智杰 on 2025/5/31.
////
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
///**
// * 0-1背包问题求解器
// * 计算在有限容量下能够获得的最大价值
// */
//
///**
// * 物品结构体定义
// */
//typedef struct {
//    int weight;     // 物品重量
//    int value;      // 物品价值
//    float ratio;    // 价值/重量比率（用于预处理）
//} Item;
//
///**
// * 背包问题状态结构体
// */
//typedef struct {
//    int capacity;       // 背包容量
//    int itemCount;      // 物品数量
//    Item* items;        // 物品数组
//    int* valueTable;    // 动态规划值表
//} Knapsack;
//
///**
// * 初始化背包问题状态
// *
// * @param knapsack 背包状态指针
// * @param capacity 背包容量
// * @param itemCount 物品数量
// * @return 初始化是否成功
// */
//bool initializeKnapsack(Knapsack* knapsack, int capacity, int itemCount) {
//    knapsack->capacity = capacity;
//    knapsack->itemCount = itemCount;
//
//    // 分配物品数组内存
//    knapsack->items = (Item*)malloc(itemCount * sizeof(Item));
//    if (!knapsack->items) return false;
//
//    // 分配DP表内存（使用一维数组优化空间）
//    // 容量+1是因为需要考虑容量为0的情况
//    knapsack->valueTable = (int*)calloc(capacity + 1, sizeof(int));
//    if (!knapsack->valueTable) {
//        free(knapsack->items);
//        return false;
//    }
//
//    return true;
//}
//
///**
// * 释放背包问题资源
// *
// * @param knapsack 背包状态指针
// */
//void destroyKnapsack(Knapsack* knapsack) {
//    if (knapsack->items) {
//        free(knapsack->items);
//        knapsack->items = NULL;
//    }
//
//    if (knapsack->valueTable) {
//        free(knapsack->valueTable);
//        knapsack->valueTable = NULL;
//    }
//}
//
///**
// * 读取物品数据
// *
// * @param knapsack 背包状态指针
// * @return 读取是否成功
// */
//bool readItems(Knapsack* knapsack) {
//    for (int i = 0; i < knapsack->itemCount; i++) {
//        if (scanf("%d %d", &knapsack->items[i].weight, &knapsack->items[i].value) != 2) {
//            return false;
//        }
//
//        // 计算价值/重量比率（可用于某些优化策略）
//        if (knapsack->items[i].weight > 0) {
//            knapsack->items[i].ratio = (float)knapsack->items[i].value / knapsack->items[i].weight;
//        } else {
//            knapsack->items[i].ratio = 0;
//        }
//    }
//    return true;
//}
//
///**
// * 使用动态规划算法求解背包问题
// * 采用自底向上的一维DP数组实现，优化空间复杂度
// *
// * @param knapsack 背包状态指针
// * @return 最大价值
// */
//int solveKnapsack(Knapsack* knapsack) {
//    // 初始状态：背包为空时，价值为0（已通过calloc初始化）
//
//    // 逐个考虑每件物品
//    for (int i = 0; i < knapsack->itemCount; i++) {
//        int itemWeight = knapsack->items[i].weight;
//        int itemValue = knapsack->items[i].value;
//
//        // 从最大容量开始逆向遍历，避免重复计算
//        for (int w = knapsack->capacity; w >= itemWeight; w--) {
//            // 状态转移方程：max(不选当前物品, 选当前物品 + 剩余空间的最大价值)
//            int valueWithoutItem = knapsack->valueTable[w];
//            int valueWithItem = knapsack->valueTable[w - itemWeight] + itemValue;
//
//            if (valueWithItem > valueWithoutItem) {
//                knapsack->valueTable[w] = valueWithItem;
//            }
//        }
//    }
//
//    // 返回最大容量对应的最大价值
//    return knapsack->valueTable[knapsack->capacity];
//}
//
///**
// * 处理单个测试用例
// */
//void solveTestCase() {
//    int itemCount, capacity;
//
//    // 读取物品数量和背包容量
//    scanf("%d %d", &itemCount, &capacity);
//
//    // 初始化背包状态
//    Knapsack knapsack;
//    if (!initializeKnapsack(&knapsack, capacity, itemCount)) {
//        fprintf(stderr, "内存分配失败\n");
//        return;
//    }
//
//    // 读取物品数据
//    if (!readItems(&knapsack)) {
//        fprintf(stderr, "输入数据格式错误\n");
//        destroyKnapsack(&knapsack);
//        return;
//    }
//
//    // 求解背包问题
//    int maxValue = solveKnapsack(&knapsack);
//
//    // 输出结果
//    printf("%d\n", maxValue);
//
//    // 释放资源
//    destroyKnapsack(&knapsack);
//}
//
///**
// * 主函数 - 程序入口
// */
//int main() {
//    int testCaseCount;
//    scanf("%d", &testCaseCount);
//
//    // 处理每个测试用例
//    for (int i = 0; i < testCaseCount; i++) {
//        solveTestCase();
//    }
//
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, C;
        scanf("%d%d", &n, &C);

        int *w = (int*)malloc(n * sizeof(int)); //动态分配内容空间
        int *v = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &w[i], &v[i]);
        }

        // 创建滚动数组：2行 x (C+1)列
        int **dp = (int**)malloc(2 * sizeof(int*));
        for (int i = 0; i < 2; i++) {
            dp[i] = (int*)malloc((C + 1) * sizeof(int));
            memset(dp[i], 0, (C + 1) * sizeof(int)); // 初始化为0
        }

        // 动态规划处理每个物品
        for (int i = 0; i < n; i++) {
            int cur = (i + 1) % 2;  // 当前行索引
            int pre = i % 2;         // 上一行索引

            // 处理容量小于当前物品重量的情况
            for (int j = 0; j < w[i]; j++) {
                dp[cur][j] = dp[pre][j];
            }

            // 处理容量大于等于当前物品重量的情况
            for (int j = w[i]; j <= C; j++) {
                dp[cur][j] = max(dp[pre][j], dp[pre][j - w[i]] + v[i]);
            }
        }

        // 输出结果（最后结果在dp[n%2][C]）
        printf("%d\n", dp[n % 2][C]);

        // 释放内存
        free(w);
        free(v);
        for (int i = 0; i < 2; i++) {
            free(dp[i]);
        }
        free(dp);
    }
    return 0;
}