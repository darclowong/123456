//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <stdbool.h>

/**
 * 检查当前位置是否允许放置皇后
 * @param row 当前行号
 * @param col 当前列号
 * @param boardSize 棋盘尺寸
 * @param occupiedCols 已占用列的位掩码
 * @param diag1 主对角线掩码(row-col)需做偏移处理
 * @param diag2 副对角线掩码(row+col)
 * @return 是否可用位置
 */
bool isPositionValid(int row, int col, int boardSize,
                     int occupiedCols, int diag1, int diag2) {
    // 检查列冲突
    if ((occupiedCols & (1 << col)) != 0) return false;

    // 检查主对角线冲突（row - col + boardSize - 1 避免负数）
    if ((diag1 & (1 << (row - col + boardSize - 1))) != 0) return false;

    // 检查副对角线冲突（row + col）
    if ((diag2 & (1 << (row + col))) != 0) return false;

    return true;
}

/**
 * 回溯法放置皇后
 * @param row 当前处理行
 * @param solutionCount 解法计数器
 * @param boardSize 棋盘尺寸
 * @param occupiedCols 已占用列掩码
 * @param diag1 主对角线掩码
 * @param diag2 副对角线掩码
 */
void placeQueen(int row, int *solutionCount, int boardSize,
                int occupiedCols, int diag1, int diag2) {
    if (row == boardSize) {
        (*solutionCount)++;
        return;
    }

    int col = 0;
    // 使用while循环替代常规for循环
    while (col < boardSize) {
        if (isPositionValid(row, col, boardSize,
                            occupiedCols, diag1, diag2)) {
            // 位运算更新占用状态
            int newColMask = occupiedCols | (1 << col);
            int newDiag1Mask = diag1 | (1 << (row - col + boardSize - 1));
            int newDiag2Mask = diag2 | (1 << (row + col));

            placeQueen(row + 1, solutionCount, boardSize,
                       newColMask, newDiag1Mask, newDiag2Mask);
        }
        col++;
    }
}

/**
 * 解决n皇后问题接口函数
 * @param n 棋盘尺寸
 * @return 解法总数
 */
int solveNQueens(int n) {
    int solutionCount = 0;
    // 从第0行开始递归
    placeQueen(0, &solutionCount, n, 0, 0, 0);
    return solutionCount;
}

int main() {
    int T;
    scanf("%d", &T);

    // 处理每个测试用例
    for (int i = 0; i < T; i++) {
        int n;
        scanf("%d", &n);
        int result = solveNQueens(n);
        printf("%d\n", result);
    }

    return 0;
}
