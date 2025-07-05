//
// Created by 王智杰 on 2025/6/4.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 棋盘最大尺寸
#define BOARD_MAX 256

// 棋盘和相关变量
int boardDimension;
char board[BOARD_MAX][BOARD_MAX];

// L型骨牌形状映射表
const char TILE_SHAPES[4] = {'a', 'd', 'b', 'c'};

/**
 * 初始化棋盘状态
 * 将所有格子设置为空格
 */
void initializeBoard() {
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            board[row][col] = ' ';
        }
    }
}

/**
 * 放置一个L型骨牌到棋盘上
 * @param shape 骨牌类型索引(0-3)
 * @param coordinates 骨牌的三个格子坐标
 */
void fillTile(int shape, int coordinates[3][2]) {
    // 获取当前骨牌的字符表示
    char tileChar = TILE_SHAPES[shape];
    
    // 将骨牌放置到指定位置
    for (int i = 0; i < 3; i++) {
        int row = coordinates[i][0];
        int col = coordinates[i][1];
        board[row][col] = tileChar;
    }
}

/**
 * 棋盘覆盖算法的核心实现
 * 使用分治法递归解决覆盖问题
 * @param topRow 当前区域的左上角行坐标
 * @param leftCol 当前区域的左上角列坐标
 * @param regionSize 当前区域的大小
 * @param markedRow 特殊格子的行坐标
 * @param markedCol 特殊格子的列坐标
 */
void solveChessboardCovering(int topRow, int leftCol, int regionSize, 
                             int markedRow, int markedCol) {
    // 基本情况：如果区域大小为1，无需放置骨牌
    if (regionSize == 1) return;
    
    // 计算子区域大小和中心点位置
    int subSize = regionSize / 2;
    int centerRow = topRow + subSize;
    int centerCol = leftCol + subSize;
    
    // 确定特殊格子所在的象限
    int region;
    if (markedRow < centerRow) {
        if (markedCol < centerCol) region = 0; // 左上
        else region = 1;                       // 右上
    } else {
        if (markedCol < centerCol) region = 2; // 左下
        else region = 3;                       // 右下
    }
    
    // 确定中心点周围的三个格子坐标（用于放置L型骨牌）
    int tilePositions[3][2];
    int idx = 0;
    
    // 根据不同情况确定L型骨牌的三个格子位置
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            // 计算当前格子坐标
            int row = centerRow - 1 + r;
            int col = centerCol - 1 + c;
            
            // 跳过特殊格子所在的子区域中心
            int currentRegion = (r * 2) + c;
            if (currentRegion == region) continue;
            
            // 记录骨牌坐标
            tilePositions[idx][0] = row;
            tilePositions[idx][1] = col;
            idx++;
        }
    }
    
    // 放置L型骨牌
    fillTile(region, tilePositions);
    
    // 递归处理四个子区域
    // 计算每个子区域的新特殊格子位置
    int newSpecialRow[4], newSpecialCol[4];
    int subRegionTopRow[4], subRegionLeftCol[4];
    
    // 左上子区域
    subRegionTopRow[0] = topRow;
    subRegionLeftCol[0] = leftCol;
    newSpecialRow[0] = (region == 0) ? markedRow : centerRow - 1;
    newSpecialCol[0] = (region == 0) ? markedCol : centerCol - 1;
    
    // 右上子区域
    subRegionTopRow[1] = topRow;
    subRegionLeftCol[1] = centerCol;
    newSpecialRow[1] = (region == 1) ? markedRow : centerRow - 1;
    newSpecialCol[1] = (region == 1) ? markedCol : centerCol;
    
    // 左下子区域
    subRegionTopRow[2] = centerRow;
    subRegionLeftCol[2] = leftCol;
    newSpecialRow[2] = (region == 2) ? markedRow : centerRow;
    newSpecialCol[2] = (region == 2) ? markedCol : centerCol - 1;
    
    // 右下子区域
    subRegionTopRow[3] = centerRow;
    subRegionLeftCol[3] = centerCol;
    newSpecialRow[3] = (region == 3) ? markedRow : centerRow;
    newSpecialCol[3] = (region == 3) ? markedCol : centerCol;
    
    // 递归覆盖四个子区域
    for (int i = 0; i < 4; i++) {
        solveChessboardCovering(
            subRegionTopRow[i], subRegionLeftCol[i], subSize,
            newSpecialRow[i], newSpecialCol[i]
        );
    }
}

/**
 * 打印棋盘当前状态
 */
void displayBoard() {
    for (int row = 0; row < boardDimension; row++) {
        for (int col = 0; col < boardDimension; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

/**
 * 主函数
 */
int main() {
    int testCases;
    scanf("%d", &testCases);
    
    for (int caseNum = 0; caseNum < testCases; caseNum++) {
        int powerK, specialRow, specialCol;
        scanf("%d %d %d", &powerK, &specialRow, &specialCol);
        
        // 计算棋盘大小
        boardDimension = 1 << powerK; // 2^k
        
        // 初始化棋盘
        initializeBoard();
        
        // 标记特殊格子（坐标从1开始，转为从0开始）
        board[specialRow-1][specialCol-1] = '*';
        
        // 解决棋盘覆盖问题
        solveChessboardCovering(0, 0, boardDimension, specialRow-1, specialCol-1);
        
        // 输出结果
        displayBoard();
    }
    
    return 0;
}
