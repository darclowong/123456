//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * 活动调度问题求解器
 * 目标：在活动集合中选择最大的相容活动子集
 */

/**
 * 活动时间区间结构体
 */
typedef struct {
    int beginTime;   // 活动开始时间
    int finishTime;  // 活动结束时间
    int originalIndex; // 原始活动编号（可用于追踪）
} Activity;

/**
 * 自定义冒泡排序实现
 * 按活动结束时间排序（从早到晚）
 * 
 * @param activities 活动数组
 * @param count 活动数量
 */
void sortActivitiesByEndTime(Activity* activities, int count) {
    bool swapped;
    
    // 外层循环：每次将最晚结束的活动冒泡到末尾
    for (int i = 0; i < count - 1; i++) {
        swapped = false;
        
        // 内层循环：比较相邻活动并交换
        for (int j = 0; j < count - i - 1; j++) {
            if (activities[j].finishTime > activities[j + 1].finishTime) {
                // 交换活动
                Activity temp = activities[j];
                activities[j] = activities[j + 1];
                activities[j + 1] = temp;
                swapped = true;
            }
        }
        
        // 如果没有发生交换，说明已经排序完成
        if (!swapped) {
            break;
        }
    }
}

/**
 * 检查两个活动是否相容（不冲突）
 * 
 * @param first 第一个活动
 * @param second 第二个活动
 * @return 如果相容返回true，否则返回false
 */
bool areActivitiesCompatible(const Activity* first, const Activity* second) {
    return (first->finishTime <= second->beginTime) || 
           (second->finishTime <= first->beginTime);
}

/**
 * 贪心算法寻找最大相容活动子集
 * 
 * @param activities 已按结束时间排序的活动数组
 * @param count 活动总数
 * @param selected 用于存储选中活动的数组（可选）
 * @return 最大相容活动数量
 */
int findMaxCompatibleActivities(Activity* activities, int count, bool* selected) {
    // 边界检查
    if (count <= 0) return 0;
    
    // 初始化：选择第一个结束最早的活动
    int compatibleCount = 1;
    int lastSelectedIndex = 0;
    
    // 如果提供了选择数组，则标记第一个活动为已选
    if (selected != NULL) {
        selected[0] = true;
    }
    
    // 贪心选择：每次选择与已选活动相容且结束最早的活动
    for (int i = 1; i < count; i++) {
        // 检查当前活动是否与最近选择的活动相容
        if (activities[i].beginTime >= activities[lastSelectedIndex].finishTime) {
            // 选择当前活动
            compatibleCount++;
            lastSelectedIndex = i;
            
            // 如果提供了选择数组，则标记当前活动为已选
            if (selected != NULL) {
                selected[i] = true;
            }
        }
    }
    
    return compatibleCount;
}

/**
 * 处理单个测试用例
 * 
 * @param caseNumber 测试用例编号
 */
void solveTestCase(int caseNumber) {
    // 读取活动数量
    int activityCount;
    scanf("%d", &activityCount);
    
    // 分配活动数组内存
    Activity* activities = (Activity*)malloc(activityCount * sizeof(Activity));
    if (!activities) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    
    // 读取每个活动的开始和结束时间
    for (int i = 0; i < activityCount; i++) {
        scanf("%d %d", &activities[i].beginTime, &activities[i].finishTime);
        activities[i].originalIndex = i + 1;  // 记录原始编号
    }
    
    // 按结束时间排序活动
    sortActivitiesByEndTime(activities, activityCount);
    
    // 分配选择数组（可选，用于记录哪些活动被选中）
    bool* selectedActivities = (bool*)calloc(activityCount, sizeof(bool));
    if (!selectedActivities) {
        fprintf(stderr, "内存分配失败\n");
        free(activities);
        exit(EXIT_FAILURE);
    }
    
    // 求解最大相容活动子集
    int maxCompatible = findMaxCompatibleActivities(activities, activityCount, selectedActivities);
    
    // 输出结果
    printf("Case %d: %d\n", caseNumber, maxCompatible);
    
    // 可选：输出选中的活动编号（本题不需要）
    /*
    printf("选中的活动: ");
    for (int i = 0; i < activityCount; i++) {
        if (selectedActivities[i]) {
            printf("%d ", activities[i].originalIndex);
        }
    }
    printf("\n");
    */
    
    // 释放内存
    free(activities);
    free(selectedActivities);
}

/**
 * 主函数 - 程序入口点
 */
int main() {
    int testCaseCount;
    scanf("%d", &testCaseCount);
    
    // 处理每个测试用例
    for (int i = 1; i <= testCaseCount; i++) {
        solveTestCase(i);
    }
    
    return 0;
}
