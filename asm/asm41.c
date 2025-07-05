//
// Created by 王智杰 on 2025/6/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (1 << 8) // 2^8 = 256

int board[MAX_SIZE][MAX_SIZE]; // 0: empty, -1: special, 1~...: tile ID
int tile_id = 1; // 当前使用的tile编号

// 映射tile编号为 a, b, c, d
char get_tile_char(int id) {
    return "abcd"[(id - 1) % 4];
}

// 覆盖棋盘的递归函数
void cover(int tr, int tc, int size, int sx, int sy) {
    if (size == 1) return;

    int half = size / 2;
    int mid_x = tr + half;
    int mid_y = tc + half;

    // 确定特殊格子所在的子块
    int quadrant = 0;
    if (sx >= mid_x && sy < mid_y) quadrant = 1; // 左下
    else if (sx < mid_x && sy >= mid_y) quadrant = 2; // 右上
    else if (sx >= mid_x && sy >= mid_y) quadrant = 3; // 右下

    // 放置中心L型骨牌
    if (quadrant != 0) {
        board[mid_x - 1][mid_y - 1] = tile_id;
        board[mid_x - 1][mid_y] = tile_id;
        board[mid_x][mid_y - 1] = tile_id;
    }
    if (quadrant != 1) {
        board[mid_x][mid_y - 1] = tile_id;
        board[mid_x][mid_y] = tile_id;
        board[mid_x - 1][mid_y] = tile_id;
    }
    if (quadrant != 2) {
        board[mid_x][mid_y - 1] = tile_id;
        board[mid_x - 1][mid_y - 1] = tile_id;
        board[mid_x][mid_y] = tile_id;
    }
    if (quadrant != 3) {
        board[mid_x - 1][mid_y] = tile_id;
        board[mid_x][mid_y] = tile_id;
        board[mid_x - 1][mid_y - 1] = tile_id;
    }

    tile_id++;

    // 递归处理四个子块
    // 左上
    if (!(sx < mid_x && sy < mid_y)) {
        cover(tr, tc, half, mid_x - 1, mid_y - 1);
    } else {
        cover(tr, tc, half, sx, sy);
    }

    // 右上
    if (!(sx < mid_x && sy >= mid_y)) {
        cover(tr, mid_y, half, mid_x - 1, mid_y);
    } else {
        cover(tr, mid_y, half, sx, sy);
    }

    // 左下
    if (!(sx >= mid_x && sy < mid_y)) {
        cover(mid_x, tc, half, mid_x, mid_y - 1);
    } else {
        cover(mid_x, tc, half, sx, sy);
    }

    // 右下
    if (!(sx >= mid_x && sy >= mid_y)) {
        cover(mid_x, mid_y, half, mid_x, mid_y);
    } else {
        cover(mid_x, mid_y, half, sx, sy);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int K, X, Y;
        scanf("%d %d %d", &K, &X, &Y);

        int size = 1 << K; // 2^K
        tile_id = 1;

        // 初始化棋盘
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board[i][j] = 0;
            }
        }

        // 设置特殊格子
        board[X - 1][Y - 1] = -1;

        // 调用递归函数
        cover(0, 0, size, X - 1, Y - 1);

        // 输出结果
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == -1) {
                    printf("*");
                } else {
                    printf("%c", get_tile_char(board[i][j]));
                }
            }
            printf("\n");
        }
    }

    return 0;
}
