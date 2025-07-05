////
//// Created by 王智杰 on 2025/5/29.
////
//#include <stdio.h>
//#include <string.h>
//
//#define MAX_C 1005
//#define MAX_L 1005
//
//int dp[MAX_C][MAX_L];
//
//int max(int a, int b) {
//    return a > b ? a : b;
//}
//
//int main() {
//    int T;
//    scanf("%d", &T);
//
//    while (T--) {
//        int N, C, L;
//        scanf("%d %d %d", &N, &C, &L);
//
//        // 初始化 dp 数组
//        memset(dp, 0, sizeof(dp));
//
//        for (int i = 0; i < N; ++i) {
//            int v, w, p;
//            scanf("%d %d %d", &v, &w, &p);
//
//            // 逆序更新 dp 数组
//            for (int j = C; j >= v; --j) {
//                for (int k = L; k >= w; --k) {
//                    dp[j][k] = max(dp[j][k], dp[j - v][k - w] + p);
//                }
//            }
//        }
//
//        // 找出最大值
//        int result = 0;
//        for (int i = 0; i <= C; ++i) {
//            for (int j = 0; j <= L; ++j) {
//                result = max(result, dp[i][j]);
//            }
//        }
//
//        printf("%d\n", result);
//    }
//
//    return 0;
//}
//
//
//

#include <stdio.h>
#include <string.h>

// 定义最大容量常量
#define MAX_CAPACITY 1005
#define MAX_WEIGHT   1005

// 动态规划表，用于记录当前容量和重量下可获得的最大价值
int maxValueTable[MAX_CAPACITY][MAX_WEIGHT];


// 返回两个整数中的较大值

int maxOfTwo(int a, int b) {
    return a > b ? a : b;
}


// 初始化动态规划数组

void initializeDPTable() {
    memset(maxValueTable, 0, sizeof(maxValueTable));
}


void updateDPTable(int volume, int weight, int value, int capacity, int loadLimit) {
    // 使用倒序循环防止重复计算
    for (int j = capacity; j >= volume; --j) {
        for (int k = loadLimit; k >= weight; --k) {
            maxValueTable[j][k] = maxOfTwo(
                    maxValueTable[j][k],
                    maxValueTable[j - volume][k - weight] + value
            );
        }
    }
}


// 查找当前动态规划表中能获得的最大价值

int findMaxPossibleValue(int capacity, int loadLimit) {
    int maxValue = 0;

    for (int i = 0; i <= capacity; ++i) {
        for (int j = 0; j <= loadLimit; ++j) {
            maxValue = maxOfTwo(maxValue, maxValueTable[i][j]);
        }
    }

    return maxValue;
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        int itemCount, capacity, loadLimit;
        scanf("%d %d %d", &itemCount, &capacity, &loadLimit);

        // 初始化 DP 表
        initializeDPTable();

        // 处理每个物品
        for (int i = 0; i < itemCount; ++i) {
            int volume, weight, value;
            scanf("%d %d %d", &volume, &weight, &value);
            updateDPTable(volume, weight, value, capacity, loadLimit);
        }

        // 计算并输出最大价值
        int result = findMaxPossibleValue(capacity, loadLimit);
        printf("%d\n", result);
    }

    return 0;
}
