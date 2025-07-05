//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 边信息结构体：存储最小权值和对应顶点
 */
typedef struct {
    int minWeight;      // 当前最小权值
    int adjacentVertex; // 对应的邻接顶点
} MinEdge;

/**
 * 读取邻接矩阵
 * @param n 顶点数量
 * @return 邻接矩阵
 */
int** readAdjacencyMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

/**
 * 初始化最小边数组
 * @param n 顶点数量
 * @return 初始化的最小边数组
 */
MinEdge* initializeMinEdges(int n) {
    MinEdge* edges = (MinEdge*)malloc(n * sizeof(MinEdge));
    for (int i = 0; i < n; i++) {
        edges[i].minWeight = INT_MAX;
        edges[i].adjacentVertex = -1;
    }
    return edges;
}

/**
 * 寻找最小权值的边
 * @param minEdges 最小边数组
 * @param n 顶点数量
 * @param visited 访问标记数组
 * @return 最小权值的顶点索引
 */
int findMinEdgeIndex(MinEdge* minEdges, int n, int* visited) {
    int minIndex = -1;
    int minWeight = INT_MAX;

    // 优化点：使用while循环替代for循环
    int i = 0;
    while (i < n) {
        if (!visited[i] && minEdges[i].minWeight < minWeight) {
            minWeight = minEdges[i].minWeight;
            minIndex = i;
        }
        i++;
    }

    return minIndex;
}

/**
 * Prim算法计算最小生成树权重
 * @param matrix 邻接矩阵
 * @param n 顶点数量
 * @return 最小生成树权重
 */
int primMST(int** matrix, int n) {
    // 初始化访问标记和最小边数组
    int* visited = (int*)calloc(n, sizeof(int));
    MinEdge* minEdges = initializeMinEdges(n);

    // 从顶点0开始
    minEdges[0].minWeight = 0;

    int totalWeight = 0;  // 总权重

    // 优化点：使用while循环替代for循环
    int processed = 0;
    while (processed < n) {
        // 寻找当前最小权值的顶点
        int u = findMinEdgeIndex(minEdges, n, visited);

        // 添加该边的权值到总权重
        totalWeight += minEdges[u].minWeight;
        visited[u] = 1;  // 标记为已访问

        // 更新其他顶点的最小权值
        int v = 0;
        while (v < n) {
            if (!visited[v] && matrix[u][v] > 0 && matrix[u][v] < minEdges[v].minWeight) {
                minEdges[v].minWeight = matrix[u][v];
                minEdges[v].adjacentVertex = u;
            }
            v++;
        }
        processed++;
    }

    // 释放资源
    free(visited);
    free(minEdges);
    return totalWeight;
}

int main() {
    int n;
    scanf("%d", &n);

    // 读取邻接矩阵
    int** adjacencyMatrix = readAdjacencyMatrix(n);

    // 计算并输出结果
    int result = primMST(adjacencyMatrix, n);
    printf("%d\n", result);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}
