////////
//////// Created by 王智杰 on 2025/5/27.
////////
//////#include <stdio.h>
//////#include <stdlib.h>
//////#include <stdbool.h>
//////
///////**
////// * N皇后问题求解器
////// * 目标：计算在N×N棋盘上放置N个互不攻击的皇后的方案数
////// */
//////
///////**
////// * 棋盘状态结构体
////// * 使用三个位图来快速检查列和对角线冲突
////// */
//////typedef struct {
//////    int size;           // 棋盘大小
//////    int solutionCount;  // 解的数量
//////    bool* columns;      // 列占用情况
//////    bool* diag1;        // 主对角线占用情况 (行+列)
//////    bool* diag2;        // 副对角线占用情况 (行-列+size-1)
//////} ChessBoard;
//////
///////**
////// * 初始化棋盘状态
////// *
////// * @param board 棋盘状态指针
////// * @param size 棋盘大小
////// * @return 初始化是否成功
////// */
//////bool initializeBoard(ChessBoard* board, int size) {
//////    board->size = size;
//////    board->solutionCount = 0;
//////
//////    // 分配内存
//////    board->columns = (bool*)calloc(size, sizeof(bool));
//////    board->diag1 = (bool*)calloc(2 * size - 1, sizeof(bool));
//////    board->diag2 = (bool*)calloc(2 * size - 1, sizeof(bool));
//////
//////    // 检查内存分配是否成功
//////    if (!board->columns || !board->diag1 || !board->diag2) {
//////        // 释放已分配的内存
//////        if (board->columns) free(board->columns);
//////        if (board->diag1) free(board->diag1);
//////        if (board->diag2) free(board->diag2);
//////        return false;
//////    }
//////
//////    return true;
//////}
//////
///////**
////// * 释放棋盘资源
////// *
////// * @param board 棋盘状态指针
////// */
//////void destroyBoard(ChessBoard* board) {
//////    free(board->columns);
//////    free(board->diag1);
//////    free(board->diag2);
//////    board->columns = NULL;
//////    board->diag1 = NULL;
//////    board->diag2 = NULL;
//////}
//////
///////**
////// * 检查在指定位置放置皇后是否安全
////// *
////// * @param board 棋盘状态
////// * @param row 行坐标
////// * @param col 列坐标
////// * @return 是否安全
////// */
//////bool isSafe(ChessBoard* board, int row, int col) {
//////    // 检查列冲突
//////    if (board->columns[col]) return false;
//////
//////    // 检查主对角线冲突 (行+列)
//////    int diag1Index = row + col;
//////    if (board->diag1[diag1Index]) return false;
//////
//////    // 检查副对角线冲突 (行-列+size-1)
//////    int diag2Index = row - col + board->size - 1;
//////    if (board->diag2[diag2Index]) return false;
//////
//////    return true;
//////}
//////
///////**
////// * 标记或取消标记棋盘上的位置
////// *
////// * @param board 棋盘状态
////// * @param row 行坐标
////// * @param col 列坐标
////// * @param occupy 是否占用
////// */
//////void markPosition(ChessBoard* board, int row, int col, bool occupy) {
//////    board->columns[col] = occupy;
//////    board->diag1[row + col] = occupy;
//////    board->diag2[row - col + board->size - 1] = occupy;
//////}
//////
///////**
////// * 递归回溯解决N皇后问题
////// *
////// * @param board 棋盘状态
////// * @param row 当前处理的行
////// */
//////void solveQueens(ChessBoard* board, int row) {
//////    // 如果所有行都已处理完，找到一个解
//////    if (row == board->size) {
//////        board->solutionCount++;
//////        return;
//////    }
//////
//////    // 尝试在当前行的每一列放置皇后
//////    for (int col = 0; col < board->size; col++) {
//////        if (isSafe(board, row, col)) {
//////            // 放置皇后
//////            markPosition(board, row, col, true);
//////
//////            // 递归处理下一行
//////            solveQueens(board, row + 1);
//////
//////            // 回溯：移除皇后
//////            markPosition(board, row, col, false);
//////        }
//////    }
//////}
//////
///////**
////// * 计算N皇后问题的解的数量
////// *
////// * @param boardSize 棋盘大小
////// * @return 解的数量，如果内存分配失败则返回-1
////// */
//////int countNQueensSolutions(int boardSize) {
//////    // 特殊情况快速处理
//////    if (boardSize <= 0) return 0;
//////    if (boardSize == 1) return 1;
//////    if (boardSize == 2 || boardSize == 3) return 0;
//////
//////    // 创建并初始化棋盘
//////    ChessBoard board;
//////    if (!initializeBoard(&board, boardSize)) {
//////        return -1; // 内存分配失败
//////    }
//////
//////    // 求解N皇后问题
//////    solveQueens(&board, 0);
//////
//////    // 获取结果并释放资源
//////    int result = board.solutionCount;
//////    destroyBoard(&board);
//////
//////    return result;
//////}
//////
///////**
////// * 处理单个测试用例
////// *
////// * @param caseNumber 测试用例编号
////// */
//////void solveTestCase() {
//////    int boardSize;
//////    scanf("%d", &boardSize);
//////
//////    int solutionCount = countNQueensSolutions(boardSize);
//////    printf("%d\n", solutionCount);
//////}
//////
///////**
////// * 主函数 - 程序入口
////// */
//////int main() {
//////    int testCaseCount;
//////    scanf("%d", &testCaseCount);
//////
//////    // 处理每个测试用例
//////    for (int i = 0; i < testCaseCount; i++) {
//////        solveTestCase();
//////    }
//////
//////    return 0;
//////}
//////
////
////#include<stdio.h>
////#include<stdlib.h>
////#include<string.h>
////
////
////char ***ans;          // 三维指针，存储所有解的棋盘布局,也是三维数组
////char **path;          // 二维指针，存储当前解的棋盘布局，也是二维数组
////int ansTop;           // ans的外层数组索引, 即当前解的深度depth
////int pathTop;          // path的外层数组索引, 即当前解的行数row
////
////// 将path中元素复制到ans中，相当于push_back()
////void copyPath(int n) {
////    // 为ans的当前行分配pathTop个char*空间
////    char **tempPath = (char**)malloc(sizeof(char*) * pathTop);
////    int i;
////    for(i = 0; i < pathTop; ++i) {
////        // 为每个字符串分配n+1空间（含结束符）
////        tempPath[i] = (char*)malloc(sizeof(char) * n + 1);
////        int j;
////        for(j = 0; j < n; ++j)
////            // 复制字符
////            tempPath[i][j] = path[i][j];
////        tempPath[i][j] = '\0';  // 添加字符串结束符
////    }
////    ans[ansTop++] = tempPath;  // 存入ans并移动指针
////}
////
////// 判断当前位置是否有效（是否不被其它皇后影响）
////int isValid(int x, int y, int n) {
////    int i, j;
////    // 检查同一行/列是否有皇后
////    for(i = 0; i < n; ++i) {
////        if(path[y][i] == 'Q' || path[i][x] == 'Q')
////            return 0;
////    }
////    // 检查45度对角线（左上-右下）
////    i = y - 1;
////    j = x - 1;
////    while(i >= 0 && j >= 0) {
////        if(path[i][j] == 'Q') return 0;
////        --i, --j;
////    }
////
////    i = y + 1;
////    j = x + 1;
////    while(i < n && j < n) {
////        if(path[i][j] == 'Q') return 0;
////        ++i, ++j;
////    }
////
////    // 检查135度对角线（右上-左下）
////    i = y - 1;
////    j = x + 1;
////    while(i >= 0 && j < n) {
////        if(path[i][j] == 'Q') return 0;
////        --i, ++j;
////    }
////
////    i = y + 1;
////    j = x -1;
////    while(j >= 0 && i < n) {
////        if(path[i][j] == 'Q') return 0;
////        ++i, --j;
////    }
////    return 1;  // 所有检查通过
////}
////
////// 回溯算法核心
////void backTracking(int n, int depth) {
////    // 当前深度达到n层时，找到有效解
////    if(pathTop == n) {
////        copyPath(n);  // 复制当前解到ans
////        return;
////    }
////
////    // 遍历当前行的所有列
////    int i;
////    for(i = 0; i < n; ++i) {
////        // 如果位置有效
////        if(isValid(i, depth, n)) {
////            path[depth][i] = 'Q';  // 放置皇后
////            ++pathTop;             // 路径计数+1
////
////            backTracking(n, depth + 1);  // 递归下一层
////
////            path[depth][i] = '.';  // 回溯：撤销放置
////            --pathTop;             // 路径计数-1
////        }
////    }
////}
////
////// 初始化棋盘
////void initPath(int n) {
////    int i, j;
////    for(i = 0; i < n; i++) {
////        // 为每行分配空间
////        path[i] = (char*)malloc(sizeof(char) * n + 1);
////        // 初始化为'.'
////        for(j = 0; j < n; j++)
////            path[i][j] = '.';
////        path[i][j] = '\0';  // 添加结束符
////    }
////}
////
////// 主函数
////char *** solveNQueens(int n, int* returnSize, int** returnColumnSizes){
////    // 初始化存储结构
////    ans = (char***)malloc(sizeof(char**) * 400);  // 最大存储400个解
////    path = (char**)malloc(sizeof(char*) * n);     // path行数=n
////    ansTop = pathTop = 0;                          // 索引初始化
////
////    initPath(n);            // 初始化棋盘
////    backTracking(n, 0);     // 从第0层开始搜索
////
////    // 设置返回参数
////    *returnSize = ansTop;   // 返回解的数量
////    int i;
////    // 分配列尺寸数组
////    *returnColumnSizes = (int*)malloc(sizeof(int) * ansTop);
////    for(i = 0; i < ansTop; ++i) {
////        (*returnColumnSizes)[i] = n;  // 每个解的列数=n
////    }
////    return ans;  // 返回所有解
////}
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// 检查在指定位置放置皇后是否有效
//int isValidPosition(int row, int col, char** chessboard, int boardSize) {
//    // 检查同一列是否有皇后
//    for (int i = 0; i < row; i++) {
//        if (chessboard[i][col] == 'Q') {
//            return 0;
//        }
//    }
//
//    // 检查左上对角线45度
//    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
//        if (chessboard[i][j] == 'Q') {
//            return 0;
//        }
//    }
//
//    // 检查右上对角线135度
//    for (int i = row - 1, j = col + 1; i >= 0 && j < boardSize; i--, j++) {
//        if (chessboard[i][j] == 'Q') {
//            return 0;
//        }
//    }
//
//    return 1; // 位置有效
//}
//
//// 保存当前有效的棋盘状态
//void saveSolution(char*** allSolutions, int* solutionCount, char** currentBoard, int boardSize) {
//    // 分配新棋盘内存
//    char** solution = (char**)malloc(boardSize * sizeof(char*));
//
//    // 复制棋盘内容
//    for (int i = 0; i < boardSize; i++) {
//        solution[i] = (char*)malloc((boardSize + 1) * sizeof(char));
//        strcpy(solution[i], currentBoard[i]); // 复制整行
//    }
//
//    // 保存到解决方案列表
//    allSolutions[*solutionCount] = solution;
//    (*solutionCount)++;
//}
//
//// 回溯核心函数
//void backtrackSolutions(int boardSize, int currentRow, char*** allSolutions,
//                        int* solutionCount, char** currentBoard) {
//    // 找到完整解决方案
//    if (currentRow == boardSize) {
//        saveSolution(allSolutions, solutionCount, currentBoard, boardSize);
//        return;
//    }
//
//    // 尝试在当前行的每一列放置皇后
//    for (int col = 0; col < boardSize; col++) {
//        if (isValidPosition(currentRow, col, currentBoard, boardSize)) {
//            // 放置皇后
//            currentBoard[currentRow][col] = 'Q';
//
//            // 递归处理下一行
//            backtrackSolutions(boardSize, currentRow + 1, allSolutions, solutionCount, currentBoard);
//
//            // 回溯：移除皇后
//            currentBoard[currentRow][col] = '.';
//        }
//    }
//}
//
//// 初始化棋盘
//char** initializeChessboard(int boardSize) {
//    char** chessboard = (char**)malloc(boardSize * sizeof(char*));
//    for (int i = 0; i < boardSize; i++) {
//        chessboard[i] = (char*)malloc((boardSize + 1) * sizeof(char));
//        for (int j = 0; j < boardSize; j++) {
//            chessboard[i][j] = '.'; // 初始化为空位
//        }
//        chessboard[i][boardSize] = '\0'; // 字符串结束符
//    }
//    return chessboard;
//}
//
//// 主解决函数
//char*** solveNQueens(int boardSize, int* solutionCount, int** solutionDimensions) {
//    // 初始化解决方案存储
//    char*** allSolutions = (char***)malloc(400 * sizeof(char**));
//    *solutionCount = 0;
//
//    // 初始化当前棋盘
//    char** currentBoard = initializeChessboard(boardSize);
//
//    // 开始回溯搜索
//    backtrackSolutions(boardSize, 0, allSolutions, solutionCount, currentBoard);
//
//    // 设置解决方案的维度信息
//    *solutionDimensions = (int*)malloc(*solutionCount * sizeof(int));
//    for (int i = 0; i < *solutionCount; i++) {
//        (*solutionDimensions)[i] = boardSize; // 每个解决方案有boardSize行
//    }
//
//    // 释放当前棋盘内存（解决方案已保存）
//    for (int i = 0; i < boardSize; i++) {
//        free(currentBoard[i]);
//    }
//    free(currentBoard);
//
//    return allSolutions;
//}
//
//int main(){
//    int T;
//    scanf("%d",&T);
//    while(T--){
//        int n;
//        scanf("%d",&n);
//    }
//}


//数组结构：placedCols 是一个一维整型数组，大小为 N（棋盘大小）
//索引与值的含义：
//索引：表示行号（0 到 N-1）
//值：表示该行皇后所在的列位置


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局计数器
int solutionCount;

// 检查当前位置是否有效（是否不被其它皇后影响）
int isValidPosition(int row, int col, int* placedCols) {
    // 检查列和对角线，i从零开始到当前行row=currentRow,当前列col=currentCol
    for (int i = 0; i < row; i++) {
        // 检查是否在同一列
        if (placedCols[i] == col)
            return 0;

        // 检查左上对角线45度（行差 == 列差）
        if (row - i == col - placedCols[i])
            return 0;

        // 检查右上对角线135度（行差 == 列差的绝对值）
        if (row - i == placedCols[i] - col)
            return 0;
    }
    return 1; // 位置有效
}

// 回溯算法核心
void backtrackSolutions(int currentRow, int n, int* placedCols) {  //传递参数：当前行、棋盘大小、已放置的皇后行列位置
    // 找到完整解决方案
    if (currentRow == n) {  //当前行等于棋盘大小说明找到方案通过
        solutionCount++;
        return;
    }

    // 尝试当前行的所有列
    for (int col = 0; col < n; col++) {
        //判断皇后放置位置是否正确
        if (isValidPosition(currentRow, col, placedCols)) {  //传入参数：当前行、当前列、placedCols皇后存放的行列位置
            // 记录当前行皇后放置的列
            placedCols[currentRow] = col;

            // 递归处理下一行
            backtrackSolutions(currentRow + 1, n, placedCols);
        }
    }
}

// 主解决函数
int totalNQueens(int n) { //n表示棋盘大小n*n
    solutionCount = 0; // 重置解决方案计数器

    // 分配数组记录每行皇后放置的列
    int* placedCols = (int*)malloc(n * sizeof(int));  // 分配数组空间
    memset(placedCols, -1, n * sizeof(int)); // placedCols数组初始化为-1
//    当然，也可以自己初始化
//    for (int i = 0; i < n; i++) {
//        placedCols[i] = -1;
//    }
    // 开始回溯搜索
    backtrackSolutions(0, n, placedCols);  //从零行开始回溯搜索然后递归到下一行直到棋盘大小

    free(placedCols); // 回溯结束后释放内存
    return solutionCount;//返回方案个数
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", totalNQueens(n));
    }

    return 0;
}