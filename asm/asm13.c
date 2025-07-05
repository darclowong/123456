////
//// Created by 王智杰 on 2025/5/31.
////
//#include <stdio.h>
//#include <stdlib.h>
//
///**
// * 比较函数：用于升序排序
// * @param a 第一个元素
// * @param b 第二个元素
// * @return 排序结果
// */
//static int compareIntegers(const void *a, const void *b) {
//    int valueA = *(const int *)a;
//    int valueB = *(const int *)b;
//    return (valueA > valueB) - (valueA < valueB);
//}
//
///**
// * 处理单个测试用例
// * @param caseNumber 测试用例编号
// */
//void processTestCase(int caseNumber) {
//    int containerCount, capacity;
//    scanf("%d %d", &containerCount, &capacity);
//
//    // 特殊情况处理
//    if (containerCount == 0) {
//        printf("Case %d: 0 0\n", caseNumber);
//        return;
//    }
//
//    // 动态分配内存存储集装箱重量
//    int *containerWeights = (int *)malloc(containerCount * sizeof(int));
//    for (int i = 0; i < containerCount; i++) {
//        scanf("%d", &containerWeights[i]);
//    }
//
//    // 升序排序集装箱重量
//    qsort(containerWeights, containerCount, sizeof(int), compareIntegers);
//
//    int loadedCount = 0;  // 已装载数量
//    int totalWeight = 0;  // 实际载重量
//
//    // 贪心算法实现：优先装载轻量级集装箱
//    for (int i = 0; i < containerCount; i++) {
//        if (totalWeight + containerWeights[i] <= capacity) {
//            totalWeight += containerWeights[i];
//            loadedCount++;
//        } else {
//            break;
//        }
//    }
//
//    // 输出结果
//    printf("Case %d: %d %d\n", caseNumber, loadedCount, totalWeight);
//
//    // 释放动态分配的内存
//    free(containerWeights);
//}
//
//int main() {
//    int testCases;
//    scanf("%d", &testCases);
//
//    // 处理所有测试用例
//    for (int i = 1; i <= testCases; i++) {
//        processTestCase(i);
//    }
//
//    return 0;
//}



#include <stdio.h>
#include <stdlib.h>

static int ascendingCompare(const void* a, const void* b) {
    int valA = *(const int*)a;
    int valB = *(const int*)b;
    return (valA > valB) - (valA < valB);
}

int* readAndSortContainers(int count) {
    int* weights = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        scanf("%d", &weights[i]);
    }

    qsort(weights, count, sizeof(int), ascendingCompare);
    return weights;
}


int calculateMaxLoad(int* weights, int count, int capacity, int* totalWeight) {
    int loaded = 0;
    *totalWeight = 0;

    int i = 0;
    while (i < count && *totalWeight + weights[i] <= capacity) {
        *totalWeight += weights[i];
        loaded++;
        i++;
    }

    return loaded;
}


void outputResult(int caseNum, int count, int weight) {
    printf("Case %d: %d %d\n", caseNum, count, weight);
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    int currentCase = 1;
    while (currentCase <= testCases) {
        int containerCount, capacity;
        scanf("%d %d", &containerCount, &capacity);

        if (containerCount == 0) {
            outputResult(currentCase, 0, 0);
            currentCase++;
            continue;
        }

        int* sortedWeights = readAndSortContainers(containerCount);
        int totalWeight;
        int maxLoad = calculateMaxLoad(sortedWeights, containerCount, capacity, &totalWeight);

        outputResult(currentCase, maxLoad, totalWeight);


        if (sortedWeights) {
            free(sortedWeights);
            sortedWeights = NULL;
        }

        currentCase++;
    }

    return 0;
}
