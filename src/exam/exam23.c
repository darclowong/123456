//
// Created by 王智杰 on 2025/6/14.
//
//23.0/1背包问题（DP）
//
//Description
//给定n个物品和一个背包。物品i的重量是wi，其价值为vi，背包的容量为C。
//问：应该如何选择装入背包的物品，使得装入背包中物品的总价值最大？
//Input
//输入的第一行为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是物品个数n（1 ≤ n ≤ 3500）和背包容量C（C ≤ 13000），
//接下来n行，每行两个正整数 wi和 vi（ wi ≤ 1000,  vi ≤ 1000 ），分别表示第i件物品的重量 wi及其价值 vi。
//Output
//对应每个测试样例输出一行，只有一个整数，表示总价值的最大值。
//Sample Input
//2
//1 2
//1 1
//2 3
//2 3
//2 4
//
//Sample Output
//1  用例1的结果
//4  用例2的结果

#include<stdio.h>
#include<stdlib.h>
#include<minmax.h>

//输入的第一行为测试样例的个数T，接下来有T个测试样例。
int main() {

    int T, n, C;
    scanf("%d", &T);//输入测试用例个数
    while(T--) {
        scanf("%d %d", &n, &C);//输入物品个数n和背包容量C

        int *w = (int *)malloc(n * sizeof(int));  //重量 动态分配内存
        int *v = (int *)malloc(n * sizeof(int)); //价值 动态分配内存

        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &w[i], &v[i]);//输入每个物品的重量和价值
        }

        int **dp =(int **)malloc(n * sizeof(int *));  //初始化dp二维数组动态分配内存，记录

        for(int i = 0;i < n; ++i){
            dp[i] = (int *)malloc((C + 1) * sizeof(int));  //物品dp[i]动态分配内存
            for(int j = 0;j <= C;++j){
                dp[i][j] = 0;  //初始化dp二维数组
            }
        }

        for(int j = w[0]; j <= C;j++){
            dp[0][j] = v[0];  //初始化第一个物品，第一行每个容量
        }

        for(int i = 1; i < n; i++){  //先遍历物品（从第二个物品开始），再遍历背包容量
            for(int j = 0; j <= C; j++) {
                if (j < w[i]) {  //其实就是剩余容量小于物品重量时
                    dp[i][j] = dp[i - 1][j];//不放物品i
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);//放物品i
                }
            }
        }
         printf("%d\n",dp[n-1][C]);  //打印dp二维数组（因为遍历时是不包含n但是包含C的）

        free(w);  //释放内存
        free(v);  //释放内存

        for(int i = 0; i < n;++i){
            free(dp[i]);  //释放内存
        }
        free(dp);  //释放内存
    }
    return 0;
}