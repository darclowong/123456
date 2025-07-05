//
// Created by 王智杰 on 2025/6/14.
//
//44.最长公共子序列（DP）**

//Description
//一个给定序列的子序列是在该序列中删去若干元素后得到的序列。
//确切地说，若给定序列 X = { x1，x2，…，xm }，
//则另一序列Z ={ z1，z2，…，zk }，X 的子序列是指存在一个严格递增下标序列{ i1，i2，…，ik }，使得对于所有 j = 1，2，…，k ，有 zj = xij
//给出两个字符序列 X 和 Y ，求出它们的最长公共子序列。
//Input
//输入的第一行为测试样例的个数T，接下来有T个测试样例。每个测试样例的第一行是字符串 X ，第二行是字符串 Y。X 和 Y 只包含大写字母，且长度不大于1000。
//Output
//对应每个测试样例输出一行，只有一个整数，表示字符串 X 和字符串 Y 的最长公共子序列的长度。
//Sample Input
//2
//ABCDE
//ACE
//AAABBBCCC
//AABBCC

//Sample Output
//3
//6

#include<stdio.h>
#include<minmax.h>
#include<string.h>

int main(){

    int T;
    scanf("%d",&T);//输入测试用例个数
    while(T--){
        char X[1005],Y[1005];//定义字符数组X和Y
        scanf("%s\n",X);//输入字符串X
        scanf("%s",Y);//输入字符串Y

        //获取字符串长度
        int Xlen = strlen(X);//strlen(X)
        int Ylen = strlen(Y);//strlen(Y)

        //定义dp二维数组
        int dp[Xlen+1][Ylen+1];
        //初始化dp数组
        for(int i = 0;i < Xlen;i++){ //从0开始遍历
            for(int j =0; j< Ylen;j++){//从0开始遍历
                dp[i][j] = 0; //初始化dp数组为0，即最长公共子序列值为0
            }
        }

        //遍历字符串数组
        for(int i = 1; i <= Xlen;i++){ //从1开始遍历字符串X
            for(int j = 1;j <= Ylen; j++){//从1开始遍历字符串Y
                if(X[i-1] == Y[j-1]){ //如果当前位置相等
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{ //如果当前位置不相等，取较大值（最长公共子序列）
                    dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                }
            }
        }
    printf("%d\n",dp[Xlen][Ylen]);//打印dp数组
    }
    return 0;
}