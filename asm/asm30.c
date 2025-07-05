//
// Created by 王智杰 on 2025/6/1.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 符号三角形问题求解器
 * 计算具有相同数量的"+"和"-"的不同符号三角形的数量
 */

// 符号枚举，增强代码可读性
typedef enum {
    PLUS = '+',
    MINUS = '-'
} Symbol;

// 前向声明
long long countBalancedTriangles(int size);
void generateTriangles(char* row, int rowLength, int plusCount, int minusCount, int level, int maxLevel, long long* count);
char deriveSymbol(char parent1, char parent2);
int validateTriangle(char* row, int size, int* plusCount, int* minusCount);

/**
 * 根据父节点的符号生成子节点符号
 * 规则：相同符号下方为'+'，不同符号下方为'-'
 * 
 * @param parent1 左父节点符号
 * @param parent2 右父节点符号
 * @return 子节点符号
 */
char deriveSymbol(char parent1, char parent2) {
    return (parent1 == parent2) ? PLUS : MINUS;
}

/**
 * 验证三角形是否有效（+和-数量相等）
 * 
 * @param row 最后一行的符号数组
 * @param size 三角形大小
 * @param plusCount 返回+的数量
 * @param minusCount 返回-的数量
 * @return 1=有效三角形（+和-数量相等），0=无效
 */
int validateTriangle(char* row, int size, int* plusCount, int* minusCount) {
    int plus = 0;
    int minus = 0;
    
    // 计算每种符号的数量
    for (int level = 0, pos = 0; level < size; level++) {
        for (int i = 0; i <= level; i++, pos++) {
            if (row[pos] == PLUS) {
                plus++;
            } else {
                minus++;
            }
        }
    }
    
    // 返回符号计数
    if (plusCount) *plusCount = plus;
    if (minusCount) *minusCount = minus;
    
    // 验证是否平衡
    return (plus == minus);
}

/**
 * 递归生成所有可能的符号三角形
 * 
 * @param row 存储整个三角形的一维数组（按行优先顺序存储）
 * @param rowLength 当前行长度
 * @param plusCount 当前+号数量
 * @param minusCount 当前-号数量
 * @param level 当前行号
 * @param maxLevel 最大行号
 * @param count 平衡三角形计数器
 */
void generateTriangles(char* row, int rowLength, int plusCount, int minusCount, int level, int maxLevel, long long* count) {
    // 基本情况：已经完成了整个三角形
    if (level == maxLevel) {
        // 检查是否平衡
        int totalPlus, totalMinus;
        if (validateTriangle(row, maxLevel, &totalPlus, &totalMinus) && totalPlus == totalMinus) {
            (*count)++;
        }
        return;
    }
    
    // 计算当前行和下一行的起始位置
    int currentRowStart = (level * (level + 1)) / 2;
    int nextRowStart = ((level + 1) * (level + 2)) / 2;
    
    // 生成下一行的符号
    for (int i = 0; i < rowLength - 1; i++) {
        row[nextRowStart + i] = deriveSymbol(row[currentRowStart + i], row[currentRowStart + i + 1]);
    }
    
    // 更新符号计数
    int newPlusCount = plusCount;
    int newMinusCount = minusCount;
    
    for (int i = 0; i < rowLength - 1; i++) {
        if (row[nextRowStart + i] == PLUS) {
            newPlusCount++;
        } else {
            newMinusCount++;
        }
    }
    
    // 剪枝：如果不可能平衡，则提前返回
    int remainingPositions = (maxLevel * (maxLevel + 1)) / 2 - nextRowStart - rowLength + 1;
    if (abs(newPlusCount - newMinusCount) > remainingPositions) {
        return;
    }
    
    // 递归处理下一行
    generateTriangles(row, rowLength - 1, newPlusCount, newMinusCount, level + 1, maxLevel, count);
}

/**
 * 计算具有n个符号的第一行、且+和-数量相等的不同符号三角形的数量
 * 
 * @param size 第一行的符号数
 * @return 平衡符号三角形的数量
 */
long long countBalancedTriangles(int size) {
    // 如果第一行符号数为奇数，则不可能有平衡的三角形
    // (因为总符号数 = n(n+1)/2，如果n为奇数，则总符号数为奇数，不可能平分为+和-)
    if (size % 2 != 0 && ((size * (size + 1)) / 2) % 2 != 0) {
        return 0;
    }
    
    // 分配内存存储整个三角形
    int totalElements = (size * (size + 1)) / 2;
    char* triangle = (char*)malloc(totalElements + 1);
    if (!triangle) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    
    long long validCount = 0;
    
    // 生成所有可能的第一行组合
    int maxPossiblePlus = (size <= totalElements / 2) ? size : totalElements / 2;
    
    // 枚举第一行中+号的数量
    for (int plusInFirstRow = 0; plusInFirstRow <= size; plusInFirstRow++) {
        // 如果无法平衡，跳过当前组合
        int minusInFirstRow = size - plusInFirstRow;
        
        // 生成第一行
        for (int i = 0; i < size; i++) {
            triangle[i] = (i < plusInFirstRow) ? PLUS : MINUS;
        }
        
        // 使用回溯法生成其余部分
        generateTriangles(triangle, size, plusInFirstRow, minusInFirstRow, 0, size, &validCount);
    }
    
    free(triangle);
    return validCount;
}

/**
 * 主函数
 */
int main() {
    int testCases;
    scanf("%d", &testCases);
    
    for (int caseNum = 1; caseNum <= testCases; caseNum++) {
        int n;
        scanf("%d", &n);
        
        long long result = countBalancedTriangles(n);
        printf("Case %d: %lld\n", caseNum, result);
    }
    
    return 0;
}
