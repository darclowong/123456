//
// Created by 王智杰 on 2025/6/3.
//
#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f
#define MAX_N 18

// 邻接矩阵和动态规划表
int adjacency[MAX_N][MAX_N];
int dpTable[1 << MAX_N][MAX_N]; // 使用更具语义的命名

/**
 * 初始化邻接矩阵，所有权重初始化为无穷大
 */
void initAdjacency(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adjacency[i][j] = INF;
        }
    }
}

/**
 * 读取输入边数据并填充邻接矩阵
 */
void populateAdjacency(int m, int n) {
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        u--; v--; // 转换为0-based索引
        if (adjacency[u][v] > weight) {
            adjacency[u][v] = adjacency[v][u] = weight;
        }
    }
}

/**
 * 初始化动态规划表，起点为0号节点（原1号）
 */
void initDPTable(int n) {
    int totalMasks = 1 << n;
    for (int mask = 0; mask < totalMasks; ++mask) {
        for (int node = 0; node < n; ++node) {
            dpTable[mask][node] = INF;
        }
    }
    dpTable[1 << 0][0] = 0; // 起点初始化
}

/**
 * 执行动态规划状态转移
 */
void performTransitions(int n) {
    int totalMasks = 1 << n;
    for (int mask = 0; mask < totalMasks; ++mask) {
        for (int current = 0; current < n; ++current) {
            if ((mask & (1 << current)) == 0) continue;

            for (int nextNode = 0; nextNode < n; ++nextNode) {
                if ((mask & (1 << nextNode))) continue;

                if (adjacency[current][nextNode] < INF) {
                    int newMask = mask | (1 << nextNode);
                    if (dpTable[mask][current] + adjacency[current][nextNode] < dpTable[newMask][nextNode]) {
                        dpTable[newMask][nextNode] = dpTable[mask][current] + adjacency[current][nextNode];
                    }
                }
            }
        }
    }
}

/**
 * 计算最终的最短路径长度
 */
int computeResult(int n) {
    int fullMask = (1 << n) - 1;
    int shortestPath = INF;
    for (int node = 0; node < n; ++node) {
        if (adjacency[node][0] < INF && dpTable[fullMask][node] != INF) {
            int total = dpTable[fullMask][node] + adjacency[node][0];
            if (total < shortestPath) {
                shortestPath = total;
            }
        }
    }
    return shortestPath;
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        int n, m;
        scanf("%d %d", &n, &m);

        initAdjacency(n);
        populateAdjacency(m, n);

        initDPTable(n);
        performTransitions(n);

        int result = computeResult(n);

        if (result < INF) {
            printf("Case %d: %d\n", caseNum, result);
        } else {
            printf("Case %d: -1\n", caseNum);
        }
    }

    return 0;
}
