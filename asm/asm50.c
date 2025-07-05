//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 结构体表示一个作业，包含 M1 和 M2 的加工时间
 */
typedef struct {
    int m1Time;  // 在 M1 上的加工时间
    int m2Time;  // 在 M2 上的加工时间
} Job;

/**
 * 比较函数，用于 qsort 排序，应用 Johnson 规则
 * 如果 min(a_i, b_j) < min(b_i, a_j)，则 i 应排在 j 前面
 */
int compareJobs(const void *x, const void *y) {
    const Job *jobA = (const Job *)x;
    const Job *jobB = (const Job *)y;
    int minAB = (jobA->m1Time < jobB->m2Time) ? jobA->m1Time : jobB->m2Time;
    int minBA = (jobB->m1Time < jobA->m2Time) ? jobB->m1Time : jobA->m2Time;

    if (minAB < minBA) return -1;
    else if (minAB > minBA) return 1;
    else return 0;
}

/**
 * 计算给定作业顺序下的最短完成时间
 */
int calculateMinTime(Job jobs[], int n) {
    int m1EndTime = 0;
    int m2EndTime = 0;

    for (int i = 0; i < n; ++i) {
        m1EndTime += jobs[i].m1Time;
        int currentM2Start = (m2EndTime > m1EndTime) ? m2EndTime : m1EndTime;
        int currentM2End = currentM2Start + jobs[i].m2Time;
        m2EndTime = currentM2End;
    }

    return m2EndTime;
}

/**
 * 主函数：处理输入输出并调用处理函数
 */
int main() {
    int testCases;
    scanf("%d", &testCases);

    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        int jobCount;
        scanf("%d", &jobCount);

        Job *jobs = (Job *)malloc(jobCount * sizeof(Job));
        for (int i = 0; i < jobCount; ++i) {
            scanf("%d %d", &jobs[i].m1Time, &jobs[i].m2Time);
        }

        // 应用 Johnson 规则排序作业顺序
        qsort(jobs, jobCount, sizeof(Job), compareJobs);

        // 计算最短完成时间
        int result = calculateMinTime(jobs, jobCount);

        // 输出结果
        printf("%d\n", result);

        free(jobs);
    }

    return 0;
}
