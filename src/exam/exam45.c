//
// Created by 王智杰 on 2025/6/14.
//
//45.矩阵连乘（DP）**

//Description
//给定n个矩阵{ A1，A2，…，An }，保证Ai与Ai+1是可乘的，i = 1，2，…，n-1。考察这n个矩阵的连乘积A1A2…An。
//由于矩阵乘法满足结合律，故计算矩阵的连乘积可以有许多不同的计算次序。这种计算次序可以用加括号的方式来确定。
//现要求设计一个高效的算法，对给定的n个矩阵确定一个计算次序使得总的乘法次数最少，并输出该最优值。
//Input
//输入的第一行是单独一个整数T，表示案例的数目。每个案例的第一行是单独一个n ( 1 ≤ n ≤ 600 )，表示矩阵的个数。
//接下来第n行，依序分别对应第i个矩阵，每行包括两个整数xi，yi (1 ≤ i ≤ n，1 ≤ xi , yi ≤ 100 )，表示该矩阵的行数和列数。保证n个矩阵依序是可乘的。
//Output
//每个案例输出一个整数，表示最少需要的乘法次数。 运算过程及结果不会超出int范围。
//Sample Input
//1
//4
//50 10
//10 40
//40 30
//30 5

//Sample Output
//10500

#include<stdio.h>

#define MAX_NUM 1000
#define LONG_MAX 100000000

int p[MAX_NUM]; //存储矩阵的维度
int dp[MAX_NUM][MAX_NUM]; //存储矩阵最优连乘次数
int s[MAX_NUM][MAX_NUM];  //存储矩阵的最佳划分k位置

int main(){
    int T;
    scanf("%d",&T);//输入测试用例个数
    while(T--){
        int n;//矩阵的个数
        scanf("%d",&n);//输入矩阵个数

        scanf("%d %d",&p[0],&p[1]);//输入第一个矩阵的行与列
        int x,y; //输入后续矩阵的行与列（因为行 == 前列）
        for(int i = 1; i < n; i++){
            scanf("%d %d",&x,&y);//输入后面矩阵的行和列
            p[i+1] = y; //保存当前矩阵的列
        }

        // 初始化矩阵链（初始化单矩阵）
        for(int i = 1; i <= n; i++){//从1开始
            dp[i][i] = 0;  //单矩阵时的dp数组为0
            s[i][i] = i;  //单矩阵的s数组最佳划分位置为自己
        }

        for(int len = 2;len <= n;len++){ //当矩阵个数大于等于2时
            for(int i = 1; i <= n -len + 1;i++){
                int j = i +len -1;
                dp[i][j] = LONG_MAX;

                int k0 = s[i][j-1]; //左边界
                int k1 = s[i+1][j]; //右边界，即左边界+1
                if(len == 2)
                    k0 = k1 = i; //左右边界

                for(int k = k0; k <= k1 && k < j;k++){
                    int cost = dp[i][k] +dp[k+1][j] +p[i-1]*p[k]*p[j];
                    if(cost < dp[i][j]){ //如果cost小于dp数组，更新dp数组和s数组
                        dp[i][j] = cost;  //目的是找到最小连乘次数cost
                        s[i][j] = k; //目的是找到最佳划分k
                    }
                }
            }
        }
        printf("%d\n",dp[1][n]); //打印最小乘法次数(矩阵从1到n)
    }
    return 0;
}