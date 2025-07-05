//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义最大字符串长度
#define STRING_MAX_LENGTH 1001

/**
 * 子序列比较器 - 实现最长公共子序列(LCS)算法
 * 使用自底向上的动态规划方法，但采用一维数组优化空间复杂度
 */

/**
 * 计算两个字符串的最长公共子序列长度
 * 使用滚动数组优化空间复杂度
 * 
 * @param firstSeq 第一个字符串
 * @param secondSeq 第二个字符串
 * @return 最长公共子序列的长度
 */
int findLongestCommonSubsequence(const char* firstSeq, const char* secondSeq) {
    int firstLen = strlen(firstSeq);
    int secondLen = strlen(secondSeq);
    
    // 为了优化空间复杂度，使用两个一维数组交替使用
    int* current = (int*)malloc((secondLen + 1) * sizeof(int));
    int* previous = (int*)malloc((secondLen + 1) * sizeof(int));
    
    if (!current || !previous) {
        fprintf(stderr, "内存分配失败\n");
        exit(1);
    }
    
    // 初始化第一行（空字符串与secondSeq的LCS为0）
    for (int j = 0; j <= secondLen; j++) {
        previous[j] = 0;
    }
    
    // 动态规划主循环
    for (int i = 1; i <= firstLen; i++) {
        // 每行开始时，与空字符串的LCS为0
        current[0] = 0;
        
        for (int j = 1; j <= secondLen; j++) {
            // 如果当前字符相同，则LCS长度加1
            if (firstSeq[i-1] == secondSeq[j-1]) {
                current[j] = previous[j-1] + 1;
            } else {
                // 否则取上方或左方的最大值
                current[j] = (previous[j] > current[j-1]) ? previous[j] : current[j-1];
            }
        }
        
        // 交换当前行和上一行
        int* temp = previous;
        previous = current;
        current = temp;
    }
    
    // 结果存储在previous数组中（因为最后做了一次交换）
    int result = previous[secondLen];
    
    // 释放内存
    free(current);
    free(previous);
    
    return result;
}

/**
 * 递归方法构建最长公共子序列（可选功能，用于输出LCS内容）
 * 
 * @param firstSeq 第一个字符串
 * @param secondSeq 第二个字符串
 * @param lcsTable 动态规划表
 * @param i 第一个字符串当前索引
 * @param j 第二个字符串当前索引
 * @param lcsResult 存储LCS结果的字符数组
 * @param index LCS结果的当前索引
 */
void backtrackLCS(const char* firstSeq, const char* secondSeq, int** lcsTable, 
                  int i, int j, char* lcsResult, int* index) {
    // 基本情况：如果到达任一字符串的起始位置，则结束
    if (i == 0 || j == 0) {
        return;
    }
    
    // 如果当前字符相同，则该字符是LCS的一部分
    if (firstSeq[i-1] == secondSeq[j-1]) {
        // 递归处理前面的部分
        backtrackLCS(firstSeq, secondSeq, lcsTable, i-1, j-1, lcsResult, index);
        // 添加当前字符到结果中
        lcsResult[(*index)++] = firstSeq[i-1];
    }
    // 如果当前字符不同，则选择较大的方向继续
    else if (lcsTable[i-1][j] > lcsTable[i][j-1]) {
        backtrackLCS(firstSeq, secondSeq, lcsTable, i-1, j, lcsResult, index);
    }
    else {
        backtrackLCS(firstSeq, secondSeq, lcsTable, i, j-1, lcsResult, index);
    }
}

/**
 * 主函数 - 处理输入并计算LCS
 */
int main() {
    // 分配字符串缓冲区
    char firstSequence[STRING_MAX_LENGTH];
    char secondSequence[STRING_MAX_LENGTH];
    
    // 读取输入字符串
    if (scanf("%s", firstSequence) != 1) {
        fprintf(stderr, "读取第一个字符串失败\n");
        return 1;
    }
    
    if (scanf("%s", secondSequence) != 1) {
        fprintf(stderr, "读取第二个字符串失败\n");
        return 1;
    }
    
    // 计算并输出LCS长度
    int lcsLength = findLongestCommonSubsequence(firstSequence, secondSequence);
    printf("%d\n", lcsLength);
    
    return 0;
}
