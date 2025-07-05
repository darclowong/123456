//
// Created by 王智杰 on 2025/6/14.
//
//46.n后问题（回溯、分支限界）**

//Description
//在n×n格的棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
//n后问题等价于在n×n格的棋盘上放置n个皇后，任何2个皇后不放在同一行或同一列或同一斜线上。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。每个测试样例的只有一行一个数n （ n <= 15 ），表示棋盘的大小。
//Output
//对应每个测试样例输出一行结果：可行方案数。
//Sample Input
//2
//3
//4

//Sample Output
//0
//2


#include<stdio.h>

int solutionCount = 0;//定义全局变量：可行方案数
int isValid(int row,int col,int *placedCols){//判断位置是否合法

    for(int i = 0; i < row;i++ ) {  //从第i行判断到第row行
        //判断放置位置是否为同一列
    if(col == placedCols[i])
        return 0;

    //判断放置位置是否为左上对角线45度(行差 == 列差)
    if(row- i == col -placedCols[i])//row - i 行差/ col - placedCols[i]列差
        return 0;

    //判断放置位置是否为右上对角线135度（行差 == 列差的绝对值）
    if(row - i == placedCols[i] - col) //row - i行差 / placedCols[i] - col 列差的绝对值
        return 0;
    }

    return 1; //如果都通过，则返回1，表示位置合法
}

void backtracking(int row,int n, int *placedCols){//回溯算法

    //判断当前行是否 == 棋盘大小n
    if( row == n) { //如果相等说明本方案通过
        solutionCount++;//因此可行方案数+1
    return;//然后结束
    }

    //遍历当前行的所有列
    for(int col = 0; col < n; col++){
        if(isValid(row,col,placedCols)){//判断位置是否合法
            placedCols[row] = col; //合法时将当前列加入皇后放置的列数组
            //本行位置放置合法，递归下一行
            backtracking(row+1,n,placedCols);//然后递归下一行row+1
        }
    }
}

int totalQueens(int n){
    solutionCount = 0; //初始化可行方案数为0

    int placedCols[n];//定义放置皇后的列的一维数组

    backtracking(0,n,placedCols);//调用回溯函数，从第0行开始，到n,并传入皇后放置的列数组

    return solutionCount;//返回最终可行方案数
}

int main(){
    int T;
    scanf("%d",&T);//输入测试用例个数
    while(T--){
        int n;
        scanf("%d",&n);//输入棋盘大小n
        printf("%d\n",totalQueens(n));//打印输出最终可行方案数
    }
    return 0;
}