//
// Created by 王智杰 on 2025/6/14.
//
//12.棋盘覆盖（分治）**
//
//Description
//在一个2k × 2k 个方格组成的棋盘中，恰有一个方格与其他方格不同，称该方格为一特殊方格，且称该棋盘为一特殊棋盘。
//在棋盘覆盖问题中，要用图示的4种不同形态的L型骨牌覆盖给定的棋盘上除特殊方格以外的所有方格，L型骨牌不能旋转，且任何两个L型骨牌不得重叠覆盖。
//1913_1.png
//棋盘和标记为红色的特殊方格                      4种L型骨牌
//Input
//第一行是一个T，表示案例数。对于每一个案例，有三个数K，X，Y分别表示在一个2k × 2k的棋盘中，在第X行第Y列有一个特殊方格。1 ≤ K ≤ 8
//1 ≤ X, Y ≤ 2k
//Output
//输出这个被骨牌覆盖的棋盘，分别用a,b,c,d表示四种骨牌（分别用以下四种字符图形表示），特殊方格用*号表示。
//aa      bb    c      d
//a        b    cc    dd
//具体输出见sample Output
//Sample Input
//2
//2 1 2
//1 1 1
//
//Sample Output
//c*bb
//ccdb
//cddd
//ccdd
//*d
//dd

//问题求解：棋盘中的方格数= 2^k * 2^k = 4^k ,覆盖使用的L型骨牌个数=(4^k - 1)/3
//采用的方法是：将棋盘划分为4个大小相同4个象限，根据特殊方格的位置(dr,dc),在中间位置放置一个合适的L型骨牌
//用(tr,tc)表示一个象限左上角方格的坐标，(dr,dc)是特殊方格所在的坐标，size是棋盘的行数和列数


//#include<stdio.h>
//#define MAX 1025
////问题表示
//int k;  //棋盘大小
//int x,y;  //特殊方格的位置
////求解问题表示
//int board[MAX][MAX];
//int tile = 1;
//
//void ChessBoard(int tr,int tc,int dr,int dc,int size){
//    if(size == 1) //棋盘大小为1直接返回
//        return;//递归出口
//    int t = tile++; //取一个L型骨牌，其牌号为tile
//    int s = size/2;  //分割棋盘，左右上下对半
//    //考虑左上角象限
//    if(dr < tr + s && dc < tc + s)  //特殊方格在此象限中
//        ChessBoard(tr,tc,dr,dc,s);
//    else{  //此象限中无特殊方格
//        board[tr+s-1][tc+s-1] = t;  //用t号L型骨牌覆盖右下角
//        ChessBoard(tr,tc,tr+s-1,tc+s-1,s);  //将右下角作为特殊方格继续处理该象限
//    }
//    //考虑右上角象限
//    if(dr < tr + s && dc >= tc +s)
//        ChessBoard(tr,tc+s,dr,dc,s); //特殊方格在此象限中
//    else{   //此象限中无特殊方格
//        board[tr+s-1][tc+s] = t;  //用t号L型骨牌覆盖左下角
//        ChessBoard(tr,tc+s,tr+s-1,tc+s,s); //将左下角作为特殊方格继续处理该象限
//    }
//    //处理左下角象限
//    if(dr >= tr +s && dc < tc + s)  //特殊方格在此象限中
//        ChessBoard(tr+s,tc,dr,dc,s);
//    else{       //此象限中无特殊方格
//        board[tr+s][tc+s-1] = t; //用t号L型骨牌覆盖右上角
//        ChessBoard(tr+s,tc,tr+s,tc+s-1,s);  //将右上角作为特殊方格继续处理该象限
//    }
//    //处理右下角象限
//    if(dr >= tr + s && dc >= tc + s)  //特殊方格在此象限中
//        ChessBoard(tr+s,tc+s,dr,dc,s);
//    else{       //此象限中无特殊方格
//        board[tr+s][tc+s] = t;  //用t号L型骨牌覆盖左上角
//        ChessBoard(tr+s,tc+s,tr+s,tc+s,s);  //将左上角作为特殊方格继续处理该象限
//    }
//}
//
//int main(){
//    k = 3;
//    x = 1;
//    y = 2;
//    int size = 1 << k;  //size = 2^k
//    ChessBoard(0,0,x,y,size);//x,y表示特殊方格位置，0,0表示左上角坐标
//    for(int i = 0; i < size; i++){
//        for(int j = 0;j < size;j++){
//            printf("%4d\n",board[i][j]);
//        }
//    }
//    return 0;
//}

//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//// 全局变量：四种骨牌类型
//const char TILE_CHARS[4] = {'a', 'b', 'c', 'd'};
//
//// 棋盘覆盖函数
//void ChessBoard(char **board, int tr, int tc, int dr, int dc, int size, int *tile_type) {
//    if (size == 1) {
//        return;
//    }
//
//    int s = size / 2;
//    int tile = (*tile_type)++;
//    *tile_type %= 4; // 循环使用四种骨牌类型
//
//    // 特殊方格在左上象限
//    if (dr < tr + s && dc < tc + s) {
//        board[tr + s - 1][tc + s] = TILE_CHARS[3];     // 右上
//        board[tr + s][tc + s - 1] = TILE_CHARS[3];     // 左下
//        board[tr + s][tc + s] = TILE_CHARS[3];         // 右下
//
//        // 递归覆盖四个子棋盘
//        ChessBoard(board, tr, tc, dr, dc, s, tile_type); // 左上
//        ChessBoard(board, tr, tc + s, tr + s - 1, tc + s, s, tile_type); // 右上
//        ChessBoard(board, tr + s, tc, tr + s, tc + s - 1, s, tile_type); // 左下
//        ChessBoard(board, tr + s, tc + s, tr + s, tc + s, s, tile_type); // 右下
//    }
//        // 特殊方格在右上象限
//    else if (dr < tr + s && dc >= tc + s) {
//        board[tr + s - 1][tc + s - 1] = TILE_CHARS[2]; // 左上
//        board[tr + s][tc + s - 1] = TILE_CHARS[2];     // 左下
//        board[tr + s][tc + s] = TILE_CHARS[2];         // 右下
//
//        ChessBoard(board, tr, tc, tr + s - 1, tc + s - 1, s, tile_type);
//        ChessBoard(board, tr, tc + s, dr, dc, s, tile_type);
//        ChessBoard(board, tr + s, tc, tr + s, tc + s - 1, s, tile_type);
//        ChessBoard(board, tr + s, tc + s, tr + s, tc + s, s, tile_type);
//    }
//        // 特殊方格在左下象限
//    else if (dr >= tr + s && dc < tc + s) {
//        board[tr + s - 1][tc + s - 1] = TILE_CHARS[1]; // 左上
//        board[tr + s - 1][tc + s] = TILE_CHARS[1];     // 右上
//        board[tr + s][tc + s] = TILE_CHARS[1];         // 右下
//
//        ChessBoard(board, tr, tc, tr + s - 1, tc + s - 1, s, tile_type);
//        ChessBoard(board, tr, tc + s, tr + s - 1, tc + s, s, tile_type);
//        ChessBoard(board, tr + s, tc, dr, dc, s, tile_type);
//        ChessBoard(board, tr + s, tc + s, tr + s, tc + s, s, tile_type);
//    }
//        // 特殊方格在右下象限
//    else if (dr >= tr + s && dc >= tc + s) {
//        board[tr + s - 1][tc + s - 1] = TILE_CHARS[0]; // 左上
//        board[tr + s - 1][tc + s] = TILE_CHARS[0];     // 右上
//        board[tr + s][tc + s - 1] = TILE_CHARS[0];     // 左下
//
//        ChessBoard(board, tr, tc, tr + s - 1, tc + s - 1, s, tile_type);
//        ChessBoard(board, tr, tc + s, tr + s - 1, tc + s, s, tile_type);
//        ChessBoard(board, tr + s, tc, tr + s, tc + s - 1, s, tile_type);
//        ChessBoard(board, tr + s, tc + s, dr, dc, s, tile_type);
//    }
//}
//
//int main() {
//    int T;
//    scanf("%d", &T);
//
//    for (int t = 0; t < T; t++) {
//        int K, X, Y;
//        scanf("%d %d %d", &K, &X, &Y);
//
//        // 计算棋盘大小
//        int size = (int)pow(2, K);
//
//        // 动态分配棋盘内存
//        char **board = (char **)malloc(size * sizeof(char *));
//        for (int i = 0; i < size; i++) {
//            board[i] = (char *)malloc((size + 1) * sizeof(char));
//            for (int j = 0; j < size; j++) {
//                board[i][j] = ' '; // 初始化为空格
//            }
//            board[i][size] = '\0'; // 每行末尾添加结束符
//        }
//
//        // 标记特殊方格位置（行列索引从0开始）
//        board[X-1][Y-1] = '*';
//
//        // 使用分治算法覆盖棋盘
//        int tile_type = 0;
//        ChessBoard(board, 0, 0, X-1, Y-1, size, &tile_type);
//
//        // 打印棋盘
//        for (int i = 0; i < size; i++) {
//            printf("%s\n", board[i]);
//        }
//
//        // 释放内存
//        for (int i = 0; i < size; i++) {
//            free(board[i]);
//        }
//        free(board);
//    }
//
//    return 0;
//}
//




//采用的方法是：将棋盘划分为4个大小相同4个象限，根据特殊方格的位置(dr,dc),在中间位置放置一个合适的L型骨牌
//用(tr,tc)表示一个象限左上角方格的坐标，(dr,dc)是特殊方格所在的坐标，size是棋盘的行数和列数

#include <stdio.h>
#include <math.h>

#define MAX 256
// 全局变量：四种骨牌类型
const char TILE_CHARS[4] = {'a', 'b', 'c', 'd'};
char board[MAX][MAX];
// 棋盘覆盖函数
void ChessBoard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }

    int s = size / 2;

    // 特殊方格在左上象限
    if (dr < tr + s && dc < tc + s) {
        board[tr + s - 1][tc + s] = TILE_CHARS[3];     // 右上
        board[tr + s][tc + s - 1] = TILE_CHARS[3];     // 左下
        board[tr + s][tc + s] = TILE_CHARS[3];         // 右下

        // 递归覆盖四个子棋盘
        ChessBoard(tr, tc, dr, dc, s); // 左上
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s); // 右上
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s); // 左下
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s); // 右下
    }
        // 特殊方格在右上象限
    else if (dr < tr + s && dc >= tc + s) {
        board[tr + s - 1][tc + s - 1] = TILE_CHARS[2]; // 左上
        board[tr + s][tc + s - 1] = TILE_CHARS[2];     // 左下
        board[tr + s][tc + s] = TILE_CHARS[2];         // 右下
        // 递归覆盖四个子棋盘

        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        ChessBoard( tr, tc + s, dr, dc, s);
        ChessBoard( tr + s, tc, tr + s, tc + s - 1, s);
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
        // 特殊方格在左下象限
    else if (dr >= tr + s && dc < tc + s) {
        board[tr + s - 1][tc + s - 1] = TILE_CHARS[1]; // 左上
        board[tr + s - 1][tc + s] = TILE_CHARS[1];     // 右上
        board[tr + s][tc + s] = TILE_CHARS[1];         // 右下
        // 递归覆盖四个子棋盘

        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
        ChessBoard(tr + s, tc, dr, dc, s);
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
        // 特殊方格在右下象限
    else if (dr >= tr + s && dc >= tc + s) {
        board[tr + s - 1][tc + s - 1] = TILE_CHARS[0]; // 左上
        board[tr + s - 1][tc + s] = TILE_CHARS[0];     // 右上
        board[tr + s][tc + s - 1] = TILE_CHARS[0];     // 左下
        // 递归覆盖四个子棋盘

        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);
        ChessBoard(tr + s, tc + s, dr, dc, s);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while(T--){
        int K, X, Y;
        scanf("%d %d %d", &K, &X, &Y);

        // 计算棋盘大小
        int size = (int)pow(2, K);

        // 动态分配棋盘内存
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = ' '; // 初始化为空格
            }
            board[i][size] = '\0'; // 每行末尾添加结束符
        }
        // 标记特殊方格位置（行列索引从0开始）
        board[X-1][Y-1] = '*';

        // 使用分治算法覆盖棋盘
        ChessBoard(0, 0, X-1, Y-1, size);

        // 打印棋盘
        for (int i = 0; i < size; i++) {
            printf("%s\n", board[i]);//按行 打印棋盘
        }
    }
    return 0;
}