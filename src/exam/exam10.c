//
// Created by 王智杰 on 2025/6/14.
//
//10.整数划分问题（分治）
//
//Description
//将一个正整数n表示成一系列正整数之和：n = n1 + n2 + … + nk，其中 n1 ≥ n2 ≥ … ≥ nk ≥ 1  ，  k ≥ 1 。
//正整数n的这种表示称为正整数n的划分。求正整数n的不同划分方案数。例如，正整数6有如下11种满足以上规则的不同的划分：
//6，        5+1，       4+2，        4+1+1，
//3+3，      3+2+1，      3+1+1+1，
//2+2+2，    2+2+1+1，    2+1+1+1+1，
//1+1+1+1+1+1
//Input
//多行，每行一个正整数 n （ 1 ≤ n ≤ 50 ）
//Output
//为每个正整数输出一行结果。
//Sample Input
//6
//1
//
//Sample Output
//11
//1

/********************************************
*范例编号：15_05
*范例说明：整数划分问题
*********************************************/
//#include <stdio.h>
//#include <stdlib.h>
//int DivideNum(int n,int m)//n表示需要划分的整数，m表示最大加数
//   {
//      if(n==1||m==1)//如果n或m为1，则只有一种划分方法，返回1
//          return 1;
//      else if(n==m&&n>1)
//          return DivideNum(n,n-1)+1;
//      else if(n<m)//如果m>n,则令m=n
//          return DivideNum(n,n);
//      else if(n>m)
//        return DivideNum(n,m-1)+DivideNum(n-m,m);//2种情况:不包含m的情况和包含m的情况
//       return 0;
//   }
//void main(){
//       int n,r;
//       while(EOF != scanf("%d",&n)){
//       r=DivideNum(n,n);
//       printf("%d\n",r);
//   }
//       return;
//}


//#include <stdio.h>
//#include <stdlib.h>
//int DivideNum(int n){ // n表示需要划分的整数
//    if (n == 1) // 如果n为1，则只有一种划分方法，返回1
//        return 1;
//    else if (n > 1){
//        int count = 0;
//        for (int m = n; m >= 1; m--){
//            if (n - m == 0) // 当前加数等于n的情况
//                count += 1;
//            else
//                count += DivideNum(n - m); // 递归调用，分解问题
//        }
//        return count;
//    }
//    return 0;
//}
//
//void main(){
//    int n, r;
//    while (EOF != scanf("%d", &n)){
//        r = DivideNum(n);
//        printf("%d\n", r);
//    }
//    return;
//}



//#include <stdio.h>
//#include <string.h>
//#define MAX_N 51
//int main() {
//    int dp[MAX_N][MAX_N]; // dp[i][j]：正整数i划分中最大加数不超过j的方案数
//    // 初始化动态规划表
//    for (int i = 0; i < MAX_N; i++) {  //外层循环遍历所有可能的 i 值（即需要划分的整数，从 0 到 50）
//        for (int j = 0; j < MAX_N; j++) { //内层循环遍历所有可能的 j 值（即最大加数，从 0 到 50）
//            if (i == 0) {  //如果 i == 0，表示划分整数为 0，此时只有一种划分方式（空划分），所以 dp[0][j] = 1
//                dp[i][j] = 1; // 0只有一种划分（空划分）
//            } else if (j == 0) {  //如果 j == 0，表示最大加数不能为 0，因此无法进行划分，所以 dp[i][0] = 0
//                dp[i][j] = 0; // 没有可用的正整数
//            } else if (j > i) {  //如果 j > i，最大加数不可能超过 i，所以直接取 dp[i][i] 的值
//                dp[i][j] = dp[i][i]; // 最大加数不能超过i本身
//            } else { //如果 j <= i，则根据动态规划状态转移方程：
////                     dp[i][j - 1]：表示不包含 j 的划分方案数。
////                      dp[i - j][j]：表示至少包含一个 j 的划分方案数。
////                        两者相加得到最终的划分方案数。
//                dp[i][j] = dp[i][j - 1] + dp[i - j][j];  // 状态转移方程：包含j和不包含j的方案数之和
//            }
//        }
//    }
//    int n;  //声明变量 n，用于存储用户输入的待划分整数
//    //使用 while 循环持续读取用户的输入，直到遇到文件结束符 EOF
//    while (scanf("%d", &n) != EOF) {  // 读取输入并输出结果
//        //打印 dp[n][n] 的值，表示将整数 n 划分为最大加数不超过 n 的方案数
//        printf("%d\n", dp[n][n]);   // 输出将n划分为最大加数不超过n的方案数
//    }
//    return 0;
//}
//
//#include<stdio.h>
//#include<stdlib.h>
//#define MAXNUM 51
//
//int main(){
//    int dp[MAXNUM][MAXNUM];
//
//    for(int i = 0; i< MAXNUM; i++){
//        for(int j = 0; j<  MAXNUM;j++){
//            if(i == 0){
//              dp[i][j] = 1;
//            }else if( j == 0){
//                dp[i][j] = 0;
//            }else if(i < j){
//                dp[i][j] = dp[i][i];
//            }else{
//                dp[i][j] = dp[i][j-1] + dp[i - j][j];
//            }
//        }
//    }
//    int n;
//    while(scanf("%d",&n) != EOF){
//        printf("%d\n",dp[n][n]);
//    }
//    return 0;
//}


#include<stdio.h>
int DividedNum(int n,int m){ //n表示需要划分的整数，m表示最大加数
    if(n==1 ||m==1){ //如果n或m为1，则只有一种划分方法，返回1
        return 1;
    }else if(n == m&& n>1){ //如果 n==m且n>1,最大加数进行递归n-1并+1
        return DividedNum(n,n-1)+1;
    }else if(n < m){  //如果m>n,不存在这种情况，所以令m=n
        return DividedNum(n,n);
    }else if(n > m)  //2种情况:不包含m的情况（m-1）和包含m的情况（m）
        return DividedNum(n,m-1) + DividedNum(n-m,m);
    return 0;
}
int main(){
    int n;
    while(EOF != scanf("%d",&n)){ //使用 while 循环持续读取用户的输入，直到遇到文件结束符 EOF
        printf("%d\n",DividedNum(n,n)); //打印DividedNum(n,n)的值，表示将整数 n 划分为最大加数不超过 n 的方案数
    }
    return 0;
}
