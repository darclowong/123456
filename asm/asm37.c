#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 1000000000
#define MAX_NODES 1005

// 定义边结构体
typedef struct Edge {
    int to;         // 边的目标节点
    int weight;     // 边的权重
    struct Edge* next; // 下一条边
} Edge;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // 邻接表初始化
    Edge* adj[MAX_NODES] = {NULL}; // adj[i] 指向节点 i 的邻接边链表

    // 读取边并构建邻接表
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        Edge* new_edge = (Edge*)malloc(sizeof(Edge));
        new_edge->to = v;
        new_edge->weight = w;
        new_edge->next = adj[u];
        adj[u] = new_edge;
    }

    // Dijkstra 算法初始化
    int dist[MAX_NODES];        // 距离数组
    int visited[MAX_NODES] = {0}; // 是否已处理

    for (int i = 1; i <= N; ++i)
        dist[i] = INF;
    dist[1] = 0;

    // 主循环：每次选最近未处理节点并松弛
    for (int count = 1; count <= N; ++count) {
        int current_node = -1;
        int min_dist = INF;

        // 找当前未处理的最短路径节点
        for (int v = 1; v <= N; ++v) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                current_node = v;
            }
        }

        if (current_node == -1)
            break; // 剩余节点不可达

        visited[current_node] = 1;

        // 遍历邻接边并松弛
        Edge* iter = adj[current_node];
        while (iter) {
            int neighbor = iter->to;
            int weight = iter->weight;

            if (dist[current_node] + weight < dist[neighbor])
                dist[neighbor] = dist[current_node] + weight;

            iter = iter->next;
        }
    }

    // 计算总和（节点 2 到 N 的最短路径之和）
    long long total = 0;
    for (int i = 2; i <= N; ++i)
        total += dist[i];
    printf("%lld\n", total);

    // 释放邻接表内存
    for (int i = 1; i <= N; ++i) {
        Edge* current = adj[i];
        while (current) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
