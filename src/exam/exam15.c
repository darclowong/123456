//
// Created by 王智杰 on 2025/6/14.
//
//15.n后问题（回溯、分支限界）**
//
//Description
//在n×n格的棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
//n后问题等价于在n×n格的棋盘上放置n个皇后，任何2个皇后不放在同一行或同一列或同一斜线上。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。每个测试样例的只有一行一个数n （ n < 15 ），表示棋盘的大小。
//Output
//对应每个测试样例输出一行结果：可行方案数。
//Sample Input
//2
//3
//4
//
//Sample Output
//0
//2


#include<stdio.h>

int solutionCount;//定义解决方案个数全局变量（可行方案数）

int isValid(int row,int col,int *placedCol){ //（三个判断：同列，同斜线）
    for(int i = 0;i < row;i++){
        //判断位置是否为同一列
        if(col == placedCol[i])
            return 0;

        //判断位置是否为左上对角线45度(行差 == 列差)
        if((row - i) == (col - placedCol[i])){
            return 0;
        }

        //判断位置是否为右上对角线135度（行差 == 列差的绝对值）
        if((row - i) == ( placedCol[i]) - col){
            return 0;
        }
    }
    return 1;
}


void backtracking(int row,int n,int *placedCol) {

    //如果当前行 == n，则表示找到了一个可行方案，solutionCount++
    if (row == n) {
        solutionCount++;
        return;
    }
        //遍历当前行的所有列
        for (int col = 0; col < n; col++) {
            if (isValid(row, col, placedCol)) {
                placedCol[row] = col;

                //本行放置位置合法，递归下一行
                backtracking(row + 1, n ,placedCol);
            }
        }
}

int totalQueens(int n){
    solutionCount = 0;//初始化可行方案数为零

    int placedCol[n]; //定义放置皇后的列位置数组

    for(int i = 0; i < n;i++)
        placedCol[i] = -1; //初始化皇后列位置数组为-1

    backtracking(0,n,placedCol); //从零开始回溯递归（第一行）

    return solutionCount; //返回本棋盘大小最终可行方案数
}

int main(){
    int T;
    scanf("%d",&T); //输入测试用例个数
    while(T--) {
        int n;//定义棋盘大小
        scanf("%d", &n); //输入棋盘大小
        printf("%d\n", totalQueens(n)); //输出最终可行方案数
    }
    return 0;
}