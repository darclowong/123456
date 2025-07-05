////
//// Created by 王智杰 on 2025/5/27.
////
////#include <stdio.h>
////#include <limits.h>
////
////#define MAX_N 605  // 最大矩阵数 + 一些余量
////
////int dp[MAX_N][MAX_N];  // dp[i][j] 表示从第i到第j个矩阵相乘的最小乘法次数
////int p[2 * MAX_N];     // 存储矩阵的维度信息
////
////// 返回两个数中的较小值
////int min(int a, int b) {
////    return a < b ? a : b;
////}
////
////int matrixChainMultiplication(int n) {
////    // 初始化 dp[i][i] = 0
////    int i;
////    for (i = 1; i <= n; ++i) {
////        dp[i][i] = 0;
////    }
////
////    // l 是当前考虑的矩阵链长度
////    int l;
////    for (l = 2; l <= n; ++l) {
////        int i;
////        for (i = 1; i <= n - l + 1; ++i) {
////            int j = i + l - 1;
////            dp[i][j] = INT_MAX;
////
////            // 尝试在不同位置 k 分割矩阵链
////            int k;
////            for (k = i; k < j; ++k) {
////                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
////                dp[i][j] = min(dp[i][j], cost);
////            }
////        }
////    }
////
////    return dp[1][n];
////}
////
////int main() {
////    int T;
////    scanf("%d", &T);
////
////    while (T--) {
////        int n;
////        scanf("%d", &n);
////
////        // 输入矩阵维度
////        int i;
////        for (i = 0; i < n; ++i) {
////            int x, y;
////            scanf("%d %d", &x, &y);
////            p[i] = x;
////            if (i == n - 1) {
////                p[n] = y;  // 第n个矩阵的列作为最后一个维度
////            }
////        }
////
////        // 计算并输出最小乘法次数
////        printf("%d\n", matrixChainMultiplication(n));
////    }
////
////    return 0;
////}
//
//
//#include <stdio.h>
//#include <limits.h>
//
//// 最大支持矩阵数
//#define MAX_MATRICES 605
//
//// 存储每个矩阵的维度（行数和列数）
//int dimensions[2 * MAX_MATRICES];
//
//// 二维DP数组，存储最优解
//long long minMultiplyCost[MAX_MATRICES][MAX_MATRICES];
//
///**
// * 使用三目计算两个数中的较小值
// */
//long long getMin(long long a, long long b) {
//    return a < b ? a : b;
//}
//
///**
// * 动态规划求解矩阵链乘法的最小代价
// * @param matrixCount 矩阵数量
// * @return 最小乘法次数
// */
//long long computeOptimalMultiplication(int matrixCount) {
//    // 初始化对角线为0（单个矩阵无需相乘）
//    int i;
//    for (i = 1; i <= matrixCount; ++i) {
//        minMultiplyCost[i][i] = 0;
//    }
//
//    // 按照链长度从小到大处理
//    int chainLength;
//    for (chainLength = 2; chainLength <= matrixCount; ++chainLength) {
//        for (int start = 1; start <= matrixCount - chainLength + 1; ++start) {
//            int end = start + chainLength - 1;
//            minMultiplyCost[start][end] = LLONG_MAX;
//
//            // 尝试在不同位置分割矩阵链
//            int split;
//            for (split = start; split < end; ++split) {
//                long long currentCost = minMultiplyCost[start][split] +
//                                        minMultiplyCost[split + 1][end] +
//                                        dimensions[start - 1] *
//                                        dimensions[split] *
//                                        dimensions[end];
//
//                minMultiplyCost[start][end] = getMin(minMultiplyCost[start][end], currentCost);
//            }
//        }
//    }
//
//    return minMultiplyCost[1][matrixCount];
//}
//
///**
// * 主程序入口
// */
//int main() {
//    int testCases;
//    scanf("%d", &testCases);
//
//    while (testCases--) {
//        int matrixCount;
//        scanf("%d", &matrixCount);
//
//        // 读取每个矩阵的维度
//        int i;
//        for (i = 0; i < matrixCount; ++i) {
//            int rows, cols;
//            scanf("%d %d", &rows, &cols);
//            dimensions[i] = rows;
//
//            if (i == matrixCount - 1) {
//                dimensions[matrixCount] = cols;  // 最后一个矩阵的列单独保存
//            }
//        }
//
//        // 调用核心算法并输出结果
//        printf("%lld\n", computeOptimalMultiplication(matrixCount));
//    }
//
//    return 0;
//}
//


//#include<stdio.h>
//
//#define MaxNum 1000 //定义
//
//#define LONG_MAX 100000000 //定义一个充分大的数
//long MatrixChain(int);
//int dimensions[MaxNum];
//long memoTable[MaxNum][MaxNum]; //记录最优值的数组，表示理论分析部分的m
//int bestK[MaxNum][MaxNum]; //记录最优划分位置k的数组，表示理论分析部分的s
//
//int main(){
//    int i,matrixNum;
//    while(EOF != scanf("%d",&matrixNum)) {  //输入矩阵数量
//        for ( i = 0; i <= matrixNum; i++)
//            scanf("%d", &dimensions[i]);  //读入矩阵的维度信息
//        printf("%ld", MatrixChain(matrixNum));
//    }
//        return 0;
//}
//
////自底向上地计算最优值，结果保存在全局变量memoTable和bestK中
//long MatrixChain(int matrixNum){
//    int i,j,k,len;
//    for(i = 1; i <= matrixNum; i++) //单个矩阵的情形，定义数乘次数为0
//        memoTable[i][i] = 0;
//    for(len = 2; len <=matrixNum;len++){  //计算长度为len的矩阵链的最优值
//        for(i = 1; i <= matrixNum-len+1;i++){  //矩阵链的开始矩阵下标
//            j = i + len - 1; //矩阵链的结束矩阵下标
//            memoTable[i][j] = LONG_MAX;
//            for(k = i; k < j; k++) {  //枚举划分位置
//                long ans = memoTable[i][k] + memoTable[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
//                if (ans < memoTable[i][j]) {//更新最优信息
//                    bestK[i][j] = k;
//                    memoTable[i][j] = ans;
//                }
//            }
//        }
//    }
//    return memoTable[1][matrixNum];
//}
//


#include<stdio.h>

#define MaxNum 1000
#define LONG_MAX 100000000
int p[MaxNum]; // 全局变量：存储矩阵维度：p[0]=A1行, p[1]=A1列/A2行, p[2]=A2列/A3行, ..., p[n]=An列
int dp[MaxNum][MaxNum]; //全局变量：dp二维数组存储动态规划结果
int s[MaxNum][MaxNum];  //全局变量：s二维数组存储划分位置

int main(){
    int T; //输入测试用例个数
    scanf("%d",&T);
    while(T--) {
        int n; //读取矩阵个数
        scanf("%d", &n);
        scanf("%d %d", &p[0], &p[1]);  //读取第一个矩阵的矩阵维度（行与列）

        //读取后续矩阵的维度（只需要读取列，因为行 == 前列）
        int x, y;
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &x, &y);
            p[i + 1] = y; //将列添加到p矩阵维度数组中
        }

        //初始化dp数组
        for (int i = 1; i <= n; i++) {
            dp[i][i] = 0; //单个矩阵的乘法次数为0
            s[i][i] = i;  //s[i][j]表示矩阵i到j的最优划分位置,单矩阵的最佳划分位置是自己
        }

        //遍历矩阵链
        for (int len = 2; len <= n; len++) { //矩阵的个数从2开始
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                dp[i][j] = LONG_MAX; //dp数组初始化为非常大的数

                int k0 = s[i][j - 1]; //左边界
                int k1 = s[i + 1][j]; //右边界
                if (len == 2) {  //处理矩阵个数为2的情况
                    k0 = i;  //左边界
                    k1 = i;  //右边界
                }

                for (int k = k0; k <= k1 && k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];

                    if (cost < dp[i][j]) {
                        dp[i][j] = cost; //如果当前的cost小于dp[i][j]，则更新dp[i][j]和s[i][j]
                        s[i][j] = k;
                    }
                }
            }
        }
    printf("%d\n",dp[1][n]);  //打印dp数组中的最小值
    }
    return 0;
}