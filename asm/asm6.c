//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//#define MAX_SIZE 256  // 最大棋盘尺寸
//
//// 棋盘数据结构和大小
//int boardSize;
//char board[MAX_SIZE][MAX_SIZE];
//
//// 获取当前象限对应的骨牌字符
//char getTileChar(int quadrant) {
//    switch (quadrant) {
//        case 0: return 'c';  // 左上象限
//        case 1: return 'b';  // 左下象限
//        case 2: return 'd';  // 右上象限
//        case 3: return 'a';  // 右下象限
//        default: return '?';
//    }
//}
//
//// 放置L型骨牌，根据象限选择对应的字符
//void placeLTile(int quadrant, int r1, int c1, int r2, int c2, int r3, int c3) {
//    char tile = getTileChar(quadrant);
//    board[r1][c1] = tile;
//    board[r2][c2] = tile;
//    board[r3][c3] = tile;
//}
//
//// 递归填充棋盘
//void fillBoard(int topRow, int leftCol, int size, int specialRow, int specialCol) {
//    if (size == 1) return;
//
//    int half = size / 2;
//
//    // 4个象限中心点
//    int center[4][2] = {
//            {topRow + half, leftCol + half},         // 中心点 (右下)
//            {topRow + half, leftCol + half - 1},     // 中心左点 (左下)
//            {topRow + half - 1, leftCol + half},     // 中心上点 (右上)
//            {topRow + half - 1, leftCol + half - 1}  // 中心左上点 (左上)
//    };
//
//    // 确定特殊点所属的象限
//    int quadrant = 0;
//    if (specialRow >= topRow + half && specialCol < leftCol + half) quadrant = 1;
//    else if (specialRow < topRow + half && specialCol >= leftCol + half) quadrant = 2;
//    else if (specialRow >= topRow + half && specialCol >= leftCol + half) quadrant = 3;
//
//    // 在中心区域放置L型骨牌
//    switch (quadrant) {
//        case 0:
//            placeLTile(quadrant, center[0][0], center[0][1], center[1][0], center[1][1], center[2][0], center[2][1]);
//            break;
//        case 1:
//            placeLTile(quadrant, center[0][0], center[0][1], center[2][0], center[2][1], center[3][0], center[3][1]);
//            break;
//        case 2:
//            placeLTile(quadrant, center[0][0], center[0][1], center[1][0], center[1][1], center[3][0], center[3][1]);
//            break;
//        case 3:
//            placeLTile(quadrant, center[1][0], center[1][1], center[2][0], center[2][1], center[3][0], center[3][1]);
//            break;
//    }
//
//    // 递归填充四个子棋盘
//    for (int i = 0; i < 4; ++i) {
//        int r = center[i][0];
//        int c = center[i][1];
//
//        if (board[r][c] == '*') continue;
//
//        int newTop = (i == 0 || i == 1) ? topRow + half : topRow;
//        int newLeft = (i == 0 || i == 2) ? leftCol + half : leftCol;
//        int newSpecialRow = (i == quadrant) ? specialRow : r;
//        int newSpecialCol = (i == quadrant) ? specialCol : c;
//
//        fillBoard(newTop, newLeft, half, newSpecialRow, newSpecialCol);
//    }
//}
//
//// 打印棋盘结果
//void printBoard() {
//    for (int i = 0; i < boardSize; ++i) {
//        for (int j = 0; j < boardSize; ++j) {
//            printf("%c", board[i][j]);
//        }
//        printf("\n");
//    }
//}
//
//// 主函数：控制输入输出与程序流程
//int main() {
//    int testCases;
//    scanf("%d", &testCases);
//
//    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
//        int k, x, y;
//        scanf("%d %d %d", &k, &x, &y);
//
//        boardSize = pow(2, k);
//
//        // 初始化棋盘为空格
//        for (int i = 0; i < boardSize; ++i) {
//            for (int j = 0; j < boardSize; ++j) {
//                board[i][j] = ' ';
//            }
//        }
//
//        // 设置特殊方格
//        board[x - 1][y - 1] = '*';
//
//        // 开始递归填充棋盘
//        fillBoard(0, 0, boardSize, x - 1, y - 1);
//
//        // 输出结果
//        printBoard();
//    }
//
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_BOARD_SIZE 256

// 全局变量定义
int chessBoardSize;
char chessBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

/**
 * 获取对应象限的骨牌标识符
 * @param quadrant 象限编号(0-3)
 * @return 骨牌字符
 */
char getTileChar(int quadrant) {
    const char tiles[] = {'c', 'b', 'd', 'a'};
    return tiles[quadrant];
}

/**
 * 在指定位置放置L型骨牌
 * @param quadrant 当前象限编号
 * @param r1,r2,r3 行坐标
 * @param c1,c2,c3 列坐标
 */
void placeLTile(int quadrant, int r1, int c1, int r2, int c2, int r3, int c3) {
    char tile = getTileChar(quadrant);
    chessBoard[r1][c1] = tile;
    chessBoard[r2][c2] = tile;
    chessBoard[r3][c3] = tile;
}

/**
 * 初始化棋盘
 */
void initializeBoard() {
    for (int i = 0; i < chessBoardSize; ++i) {
        memset(chessBoard[i], ' ', chessBoardSize);
    }
}

/**
 * 递归填充棋盘
 * @param topRow 起始行
 * @param leftCol 起始列
 * @param size 当前区域尺寸
 * @param specialRow 特殊方格行
 * @param specialCol 特殊方格列
 */
void fillChessBoard(int topRow, int leftCol, int size, int specialRow, int specialCol) {
    if (size == 1) return;

    int half = size / 2;
    int rowMid = topRow + half;
    int colMid = leftCol + half;

    // 四个中心点定义
    int centers[4][2] = {
            {rowMid, colMid},         // 右下中心
            {rowMid, colMid - 1},     // 左下中心
            {rowMid - 1, colMid},     // 右上中心
            {rowMid - 1, colMid - 1}  // 左上中心
    };

    // 确定特殊点所在象限
    int quadrant = 0;
    if (specialRow >= rowMid && specialCol < colMid) quadrant = 1;
    else if (specialRow < rowMid && specialCol >= colMid) quadrant = 2;
    else if (specialRow >= rowMid && specialCol >= colMid) quadrant = 3;

    // 根据象限放置L型骨牌
    switch(quadrant) {
        case 0: placeLTile(0, centers[0][0], centers[0][1], centers[1][0], centers[1][1], centers[2][0], centers[2][1]); break;
        case 1: placeLTile(1, centers[0][0], centers[0][1], centers[2][0], centers[2][1], centers[3][0], centers[3][1]); break;
        case 2: placeLTile(2, centers[0][0], centers[0][1], centers[1][0], centers[1][1], centers[3][0], centers[3][1]); break;
        case 3: placeLTile(3, centers[1][0], centers[1][1], centers[2][0], centers[2][1], centers[3][0], centers[3][1]); break;
    }

    // 递归处理四个子区域
    int i = 0;
    while(i < 4) {
        int r = centers[i][0];
        int c = centers[i][1];

        if(chessBoard[r][c] == '*') {
            i++;
            continue;
        }

        // 计算子区域参数
        int newTop = (i == 0 || i == 1) ? rowMid : topRow;
        int newLeft = (i == 0 || i == 2) ? colMid : leftCol;
        int newSpecialRow = (i == quadrant) ? specialRow : r;
        int newSpecialCol = (i == quadrant) ? specialCol : c;

        fillChessBoard(newTop, newLeft, half, newSpecialRow, newSpecialCol);
        i++;
    }
}

/**
 * 打印棋盘
 */
void printChessBoard() {
    for (int i = 0; i < chessBoardSize; ++i) {
        for (int j = 0; j < chessBoardSize; ++j) {
            printf("%c", chessBoard[i][j]);
        }
        printf("\n");
    }
}

/**
 * 主程序入口
 */
int main() {
    int testCases;
    scanf("%d", &testCases);

    for (int currentCase = 1; currentCase <= testCases; ++currentCase) {
        int k, x, y;
        scanf("%d %d %d", &k, &x, &y);

        chessBoardSize = pow(2, k);
        initializeBoard();

        // 设置特殊方格
        chessBoard[x-1][y-1] = '*';

        // 开始填充
        fillChessBoard(0, 0, chessBoardSize, x-1, y-1);

        // 输出结果
        printChessBoard();
    }

    return 0;
}
