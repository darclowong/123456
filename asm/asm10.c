
#include <stdio.h>
#include <stdlib.h>


#define INTEGER_LIMIT 51

/**
 * 整数划分计数器结构体
 * 用于存储和计算整数划分方案数
 */
typedef struct {
    long long** memoTable;  // 存储中间结果的记忆化表
    int capacity;           // 表的容量
} PartitionCounter;


int initializeCounter(PartitionCounter* counter, int size) {
    // 分配记忆化表内存
    counter->capacity = size;
    counter->memoTable = (long long**)malloc(size * sizeof(long long*));
    if (!counter->memoTable) return 0;

    for (int i = 0; i < size; i++) {
        counter->memoTable[i] = (long long*)malloc(size * sizeof(long long));
        if (!counter->memoTable[i]) {
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(counter->memoTable[j]);
            }
            free(counter->memoTable);
            return 0;
        }

        // 初始化基础情况
        for (int j = 0; j < size; j++) {
            // 当整数为0时，只有一种划分方案（空划分）
            if (i == 0) {
                counter->memoTable[i][j] = 1;
            }
                // 当最大部分为0时，无法划分（除了整数0）
            else if (j == 0) {
                counter->memoTable[i][j] = 0;
            }
            else {
                counter->memoTable[i][j] = 0;  // 其他情况初始化为0
            }
        }
    }

    return 1;
}


void destroyCounter(PartitionCounter* counter) {
    if (!counter || !counter->memoTable) return;

    for (int i = 0; i < counter->capacity; i++) {
        free(counter->memoTable[i]);
    }
    free(counter->memoTable);
    counter->memoTable = NULL;
}


void computePartitions(PartitionCounter* counter) {
    int size = counter->capacity;

    // 自底向上填充记忆化表
    for (int number = 1; number < size; number++) {
        for (int maxPart = 1; maxPart < size; maxPart++) {
            if (maxPart > number) {
                // 最大部分大于整数本身，等同于使用整数作为最大部分
                counter->memoTable[number][maxPart] = counter->memoTable[number][number];
            } else {

                counter->memoTable[number][maxPart] =
                        counter->memoTable[number - maxPart][maxPart] +
                        counter->memoTable[number][maxPart - 1];
            }
        }
    }
}


long long getPartitionCount(PartitionCounter* counter, int n) {
    if (n < 0 || n >= counter->capacity) return 0;
    return counter->memoTable[n][n];
}

int main() {
    // 创建并初始化划分计数器
    PartitionCounter counter;
    if (!initializeCounter(&counter, INTEGER_LIMIT)) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }

    // 预计算所有可能的划分方案数
    computePartitions(&counter);

    // 处理输入并输出结果
    int number;
    while (scanf("%d", &number) != EOF) {
        if (number >= 0 && number < INTEGER_LIMIT) {
            printf("%lld\n", getPartitionCount(&counter, number));
        } else {
            printf("输入超出范围(0-%d)", INTEGER_LIMIT - 1);
        }
    }

    destroyCounter(&counter);

    return 0;
}
