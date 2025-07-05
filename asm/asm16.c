//
// Created by 王智杰 on 2025/5/29.
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#define MAX_VERTEX 10
//
//int graph[MAX_VERTEX][MAX_VERTEX]; // 邻接矩阵
//int colorAssignments[MAX_VERTEX]; // 颜色分配数组
//int validColoringCount; // 有效颜色分配方案的数量
//
//// 检查当前顶点颜色是否与相邻顶点颜色冲突
//int isSafe(int vertex, int color, int n) {
//    for (int i = 0; i < vertex; i++) {
//        if (graph[vertex][i] && colorAssignments[i] == color) {
//            return 0; // 颜色冲突
//        }
//    }
//    return 1;
//}
//
//// 回溯算法尝试所有可能的颜色分配
//void backtrack(int vertex, int n, int m) {
//    if (vertex == n) { // 已经为所有顶点分配了颜色
//        validColoringCount++; // 有效颜色分配方案数量增加
//        return;
//    }
//
//    for (int color = 1; color <= m; color++) { // 尝试每种颜色
//        if (isSafe(vertex, color, n)) {
//            colorAssignments[vertex] = color; // 分配颜色
//            backtrack(vertex + 1, n, m); // 递归处理下一个顶点
//        }
//    }
//}
//
//int main() {
//    int T; // 测试样例数量
//    scanf("%d", &T);
//
//    for (int caseNum = 1; caseNum <= T; caseNum++) {
//        int n, M, m; // 顶点数、边数、可用颜色数
//        scanf("%d %d %d", &n, &M, &m);
//
//        // 初始化邻接矩阵
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                graph[i][j] = 0;
//            }
//        }
//
//        // 输入边信息并构建邻接矩阵
//        for (int i = 0; i < M; i++) {
//            int u, v;
//            scanf("%d %d", &u, &v);
//            graph[u-1][v-1] = 1;
//            graph[v-1][u-1] = 1;
//        }
//
//        validColoringCount = 0;
//        backtrack(0, n, m); // 从第一个顶点开始回溯
//
//        // 输出结果
//        printf("Case %d: %d\n", caseNum, validColoringCount);
//    }
//
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10

int adjacency[MAX_NODES][MAX_NODES]; // 邻接矩阵
int nodeColors[MAX_NODES];           // 每个节点的颜色分配
int totalValidAssignments;           // 合法颜色方案总数

// 检查当前颜色是否与邻接节点冲突
int isColorSafe(int node, int color, int totalNodes) {
    for (int neighbor = 0; neighbor < node; ++neighbor) {
        if (adjacency[node][neighbor] && nodeColors[neighbor] == color) {
            return 0; // 存在冲突
        }
    }
    return 1;
}

// 回溯搜索所有可能的颜色组合
void exploreColorings(int currentNode, int totalNodes, int maxColor) {
    if (currentNode == totalNodes) {
        totalValidAssignments++;
        return;
    }

    for (int chosenColor = 1; chosenColor <= maxColor; ++chosenColor) {
        if (isColorSafe(currentNode, chosenColor, totalNodes)) {
            nodeColors[currentNode] = chosenColor;
            exploreColorings(currentNode + 1, totalNodes, maxColor);
        }
    }
}

// 初始化邻接矩阵
void resetGraph(int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            adjacency[i][j] = 0;
        }
    }
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    for (int caseNumber = 1; caseNumber <= testCases; ++caseNumber) {
        int nodeCount, edgeCount, colorCount;
        scanf("%d %d %d", &nodeCount, &edgeCount, &colorCount);

        resetGraph(nodeCount);

        // 输入边并构建邻接矩阵
        for (int i = 0; i < edgeCount; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            adjacency[u - 1][v - 1] = 1;
            adjacency[v - 1][u - 1] = 1;
        }

        totalValidAssignments = 0;
        exploreColorings(0, nodeCount, colorCount);

        printf("Case %d: %d\n", caseNumber, totalValidAssignments);
    }

    return 0;
}