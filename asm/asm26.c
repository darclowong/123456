//
// Created by 王智杰 on 2025/5/28.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 比较函数：用于降序排序
 * @param a 第一个元素指针
 * @param b 第二个元素指针
 * @return 排序比较结果
 */
static int compareDescending(const void* a, const void* b) {
    return (*(const int*)b - *(const int*)a);
}

/**
 * 找到当前负载最小的机器索引
 * @param loads 机器负载数组
 * @param machineCount 机器数量
 * @return 最小负载的机器索引
 */
int findMinLoadIndex(int* loads, int machineCount) {
    int minIndex = 0;
    int currentIndex = 1;

    // 使用while循环替代for循环
    while (currentIndex < machineCount) {
        if (loads[currentIndex] < loads[minIndex]) {
            minIndex = currentIndex;
        }
        currentIndex++;
    }

    return minIndex;
}

/**
 * 计算最短加工时间
 * @param times 作业时间数组
 * @param jobCount 作业数量
 * @param machineCount 机器数量
 * @return 最短加工时间
 */
int calculateMinProcessingTime(int* times, int jobCount, int machineCount) {
    // 如果机器足够多，直接返回最长作业时间
    if (jobCount <= machineCount) {
        return times[0];
    }

    // 动态分配并初始化机器负载数组
    int* machineLoads = (int*)calloc(machineCount, sizeof(int));

    // 前machineCount个最长作业分配给各机器
    int i = 0;
    while (i < machineCount) {
        machineLoads[i] = times[i];
        i++;
    }

    // 剩余作业分配给当前负载最小的机器
    int currentJob = machineCount;
    while (currentJob < jobCount) {
        int minIndex = findMinLoadIndex(machineLoads, machineCount);
        machineLoads[minIndex] += times[currentJob];
        currentJob++;
    }

    // 找出最大负载作为结果
    int maxLoad = machineLoads[0];
    i = 1;
    while (i < machineCount) {
        if (machineLoads[i] > maxLoad) {
            maxLoad = machineLoads[i];
        }
        i++;
    }

    free(machineLoads);
    return maxLoad;
}

/**
 * 处理单个测试用例
 * @param caseNumber 测试用例编号
 */
void processTestCase(int caseNumber) {
    int jobCount, machineCount;
    scanf("%d %d", &jobCount, &machineCount);

    // 动态分配并读取作业时间数组
    int* jobTimes = (int*)malloc(jobCount * sizeof(int));
    for (int i = 0; i < jobCount; i++) {
        scanf("%d", &jobTimes[i]);
    }

    // 降序排序作业时间
    qsort(jobTimes, jobCount, sizeof(int), compareDescending);

    // 计算并输出结果
    int result = calculateMinProcessingTime(jobTimes, jobCount, machineCount);
    printf("Case %d: %d\n", caseNumber, result);

    // 释放内存
    free(jobTimes);
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    // 处理所有测试用例
    int currentCase = 1;
    while (currentCase <= testCases) {
        processTestCase(currentCase);
        currentCase++;
    }

    return 0;
}
