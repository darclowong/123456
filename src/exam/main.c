//#include <stdio.h>
//#include <limits.h>
//
//// 函数声明
//int matrixChainOrder(int p[], int n);
//
//int main() {
//    int n;
//    scanf("%d", &n); // 读取矩阵的数量
//
//    // 定义一个数组来存储每个矩阵的行数和列数
//    int p[n + 1];
//
//    // 读取每个矩阵的行数和列数
//    int i;
//    for (i = 0; i < n; i++) {
//        scanf("%d %d", &p[i], &p[i + 1]);
//    }
//
//    // 计算并输出最少的乘法次数
//    printf("%d\n", matrixChainOrder(p, n));
//
//    return 0;
//}
//
//// 动态规划函数，计算最少的乘法次数
//int matrixChainOrder(int p[], int n) {
//    // 创建一个二维数组来存储子问题的解
//    int dp[n][n];
//
//    // 初始化 dp 数组，对角线上的元素为 0，因为单个矩阵的乘法次数为 0
//    int i;
//    for (i = 1; i < n; i++) {
//        dp[i][i] = 0;
//    }
//
//    // l 是链长
//    int l;
//    for (l = 2; l <= n; l++) { // l 从 2 开始，因为单个矩阵的乘法次数为 0
//        int i;
//        for (i = 1; i <= n - l + 1; i++) {
//            int j = i + l - 1;
//            dp[i][j] = INT_MAX; // 初始化为最大值
//            int k;
//            for (k = i; k <= j - 1; k++) {
//                // 计算将矩阵链分成两部分的乘法次数
//                int q = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
//                if (q < dp[i][j]) {
//                    dp[i][j] = q; // 更新最小乘法次数
//                }
//            }
//        }
//    }
//
//    // 返回计算矩阵链 A[1] 到 A[n] 的最少乘法次数
//    return dp[1][n - 1];
//}

//测试用例
//4   矩阵个数
//50 10   第一个矩阵行数和列数
//10 40   第二个矩阵行数和列数
//40 30   第三个矩阵行数和列数
//30 5    第四个矩阵行数和列数
//10500   输出一个整数，表示最少需要的乘法次数

//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//
//int main() {
//    int n;
//    scanf("%d", &n);
//    int* p = (int*)malloc((n + 1) * sizeof(int));
//    scanf("%d %d", &p[0], &p[1]);
//    for (int i = 2; i <= n; i++) {
//        int x;
//        scanf("%d %d", &x, &p[i]);
//    }
//
//    int** m = (int**)malloc((n + 1) * sizeof(int*));
//    for (int i = 0; i <= n; i++) {
//        m[i] = (int*)malloc((n + 1) * sizeof(int));
//    }
//
//    for (int i = 1; i <= n; i++) {
//        m[i][i] = 0;
//    }
//
//    for (int L = 2; L <= n; L++) {
//        for (int i = 1; i <= n - L + 1; i++) {
//            int j = i + L - 1;
//            m[i][j] = INT_MAX;
//            for (int k = i; k < j; k++) {
//                int temp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
//                if (temp < m[i][j]) {
//                    m[i][j] = temp;
//                }
//            }
//        }
//    }
//
//    printf("%d\n", m[1][n]);
//
//    free(p);
//    for (int i = 0; i <= n; i++) {
//        free(m[i]);
//    }
//    free(m);
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int* p = (int*)malloc((n + 1) * sizeof(int));
    scanf("%d %d", &p[0], &p[1]);
    int i;
    for (i = 2; i <= n; i++) {
        int x;
        scanf("%d %d", &x, &p[i]);
    }

    int** m = (int**)malloc((n + 1) * sizeof(int*));
//    int i;
    for (i = 0; i <= n; i++) {
        m[i] = (int*)malloc((n + 1) * sizeof(int));
    }
//    int i;
    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    int L, j, k, temp;
    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++) {
                temp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (temp < m[i][j]) {
                    m[i][j] = temp;
                }
            }
        }
    }

    printf("%d\n", m[1][n]);

    return 0;
}
