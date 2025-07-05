//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * 流水线作业调度系统
 * 实现Johnson算法求解两机器流水作业调度问题
 */

/**
 * 作业信息结构体
 */
typedef struct {
    int processingTimeM1;  // 在机器1上的加工时间
    int processingTimeM2;  // 在机器2上的加工时间
    int jobID;             // 作业编号
} JobInfo;

/**
 * 流水线调度上下文
 */
typedef struct {
    int jobCount;          // 作业总数
    JobInfo* jobs;         // 作业信息数组
    int* optimalOrder;     // 最优调度顺序
    bool isInitialized;    // 初始化标志
} SchedulingContext;

/**
 * 初始化调度上下文
 * 
 * @param context 调度上下文指针
 * @param numJobs 作业数量
 * @return 初始化是否成功
 */
bool initSchedulingContext(SchedulingContext* context, int numJobs) {
    if (numJobs <= 0) {
        return false;
    }
    
    // 初始化基本属性
    context->jobCount = numJobs;
    context->isInitialized = false;
    
    // 分配作业数组内存
    context->jobs = (JobInfo*)malloc(numJobs * sizeof(JobInfo));
    if (!context->jobs) {
        return false;
    }
    
    // 分配最优顺序数组内存
    context->optimalOrder = (int*)malloc(numJobs * sizeof(int));
    if (!context->optimalOrder) {
        free(context->jobs);
        context->jobs = NULL;
        return false;
    }
    
    // 初始化作业ID
    for (int i = 0; i < numJobs; i++) {
        context->jobs[i].jobID = i;
    }
    
    context->isInitialized = true;
    return true;
}

/**
 * 释放调度上下文资源
 * 
 * @param context 调度上下文指针
 */
void cleanupSchedulingContext(SchedulingContext* context) {
    if (context->jobs) {
        free(context->jobs);
        context->jobs = NULL;
    }
    
    if (context->optimalOrder) {
        free(context->optimalOrder);
        context->optimalOrder = NULL;
    }
    
    context->isInitialized = false;
}

/**
 * 读取作业处理时间数据
 * 
 * @param context 调度上下文指针
 * @return 读取是否成功
 */
bool readJobData(SchedulingContext* context) {
    if (!context->isInitialized) {
        return false;
    }
    
    for (int i = 0; i < context->jobCount; i++) {
        if (scanf("%d %d", &context->jobs[i].processingTimeM1, 
                          &context->jobs[i].processingTimeM2) != 2) {
            return false;
        }
    }
    
    return true;
}

/**
 * 应用改进的Johnson算法计算最优调度顺序
 * 
 * @param context 调度上下文指针
 */
void calculateOptimalSchedule(SchedulingContext* context) {
    // 创建两个队列（实际上是数组的两端）
    int frontPos = 0;
    int backPos = context->jobCount - 1;
    
    // 标记数组，记录已处理的作业
    bool* processed = (bool*)calloc(context->jobCount, sizeof(bool));
    if (!processed) {
        return;
    }
    
    // Johnson算法的核心实现
    // 1. 先处理所有M1时间小于M2时间的作业
    for (int i = 0; i < context->jobCount; i++) {
        if (context->jobs[i].processingTimeM1 <= context->jobs[i].processingTimeM2) {
            context->optimalOrder[frontPos++] = context->jobs[i].jobID;
            processed[i] = true;
        }
    }
    
    // 2. 再处理所有M1时间大于M2时间的作业（从后往前）
    for (int i = context->jobCount - 1; i >= 0; i--) {
        if (!processed[i]) {
            context->optimalOrder[backPos--] = context->jobs[i].jobID;
        }
    }
    
    free(processed);
}

/**
 * 计算给定调度顺序下的总完成时间
 * 
 * @param context 调度上下文指针
 * @return 总完成时间
 */
int calculateMakespan(SchedulingContext* context) {
    int machineM1Time = 0;  // 机器1的当前时间
    int machineM2Time = 0;  // 机器2的当前时间
    
    // 按照调度顺序处理每个作业
    for (int i = 0; i < context->jobCount; i++) {
        int jobIndex = context->optimalOrder[i];
        
        // 更新机器1的完成时间
        machineM1Time += context->jobs[jobIndex].processingTimeM1;
        
        // 更新机器2的完成时间
        // 机器2只能在机器1完成当前作业且机器2完成前一个作业后才能开始
        machineM2Time = (machineM1Time > machineM2Time) ? 
                         machineM1Time + context->jobs[jobIndex].processingTimeM2 : 
                         machineM2Time + context->jobs[jobIndex].processingTimeM2;
    }
    
    return machineM2Time;
}

/**
 * 处理单个测试用例
 * 
 * @return 处理是否成功
 */
bool processTestCase() {
    int jobCount;
    
    // 读取作业数量
    if (scanf("%d", &jobCount) != 1) {
        return false;
    }
    
    // 初始化调度上下文
    SchedulingContext context;
    if (!initSchedulingContext(&context, jobCount)) {
        fprintf(stderr, "初始化失败\n");
        return false;
    }
    
    // 读取作业数据
    if (!readJobData(&context)) {
        fprintf(stderr, "数据读取失败\n");
        cleanupSchedulingContext(&context);
        return false;
    }
    
    // 计算最优调度顺序
    calculateOptimalSchedule(&context);
    
    // 计算并输出最短完成时间
    int minMakespan = calculateMakespan(&context);
    printf("%d\n", minMakespan);
    
    // 清理资源
    cleanupSchedulingContext(&context);
    
    return true;
}

/**
 * 程序入口
 */
int main() {
    int testCases;
    
    // 读取测试用例数量
    if (scanf("%d", &testCases) != 1) {
        fprintf(stderr, "输入格式错误\n");
        return EXIT_FAILURE;
    }
    
    // 处理每个测试用例
    for (int i = 0; i < testCases; i++) {
        if (!processTestCase()) {
            fprintf(stderr, "处理测试用例失败\n");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
