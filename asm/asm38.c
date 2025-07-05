//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 1000000000
#define MAX_N 18

int main() {
    int T;
    scanf("%d", &T);

    for (int case_num = 1; case_num <= T; ++case_num) {
        int n, m;
        scanf("%d %d", &n, &m);

        // 初始化邻接矩阵
        int adj[MAX_N][MAX_N];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                adj[i][j] = INF;
            }
        }

        // 读取边并更新邻接矩阵
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            u -= 1;
            v -= 1;

            // 保留最小权值
            if (adj[u][v] > w) {
                adj[u][v] = w;
                adj[v][u] = w;
            }
        }

        // 初始化动态规划数组
        int size = 1 << n;
        int dp[size][n];

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = INF;
            }
        }

        // 初始状态：仅访问起点
        dp[1 << 0][0] = 0;

        // 状态转移
        for (int mask = 0; mask < size; ++mask) {
            for (int u = 0; u < n; ++u) {
                // 检查当前状态是否包含u
                if ((mask & (1 << u)) == 0 || dp[mask][u] == INF) continue;

                // 尝试转移到未访问节点
                for (int v = 0; v < n; ++v) {
                    if ((mask & (1 << v)) || adj[u][v] == INF) continue;

                    int new_mask = mask | (1 << v);
                    if (dp[new_mask][v] > dp[mask][u] + adj[u][v]) {
                        dp[new_mask][v] = dp[mask][u] + adj[u][v];
                    }
                }
            }
        }

        // 计算最终结果
        int full_mask = (1 << n) - 1;
        int min_cost = INF;

        for (int u = 0; u < n; ++u) {
            if (dp[full_mask][u] != INF && adj[u][0] != INF) {
                int total = dp[full_mask][u] + adj[u][0];
                if (total < min_cost) {
                    min_cost = total;
                }
            }
        }

        // 输出结果
        if (min_cost == INF) {
            printf("Case %d: -1\n", case_num);
        } else {
            printf("Case %d: %d\n", case_num, min_cost);
        }
    }

    return 0;
}
