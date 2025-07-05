//
// Created by 王智杰 on 2025/6/2.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 二分查找函数，返回目标值首次出现的位置（若存在），否则返回 -1
 */
int findFirstOccurrence(int *arr, int size, int key) {
    int start = 0;
    int end = size - 1;
    int result = -1;

    while (start <= end) {
        int midPoint = start + (end - start) / 2;

        if (arr[midPoint] == key) {
            result = midPoint; // 记录当前匹配位置
            end = midPoint - 1; // 继续向左查找更小索引
        } else if (arr[midPoint] < key) {
            start = midPoint + 1;
        } else {
            end = midPoint - 1;
        }
    }

    return result;
}

int main() {
    int M;
    scanf("%d", &M);

    // 动态分配数组空间
    int *array = (int *)malloc(M * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 读取数组元素
    for (int i = 0; i < M; ++i) {
        scanf("%d", &array[i]);
    }

    int N;
    scanf("%d", &N);

    // 动态分配关键字数组
    int *keys = (int *)malloc(N * sizeof(int));
    if (keys == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(array);
        return 1;
    }

    // 读取关键字
    for (int i = 0; i < N; ++i) {
        scanf("%d", &keys[i]);
    }

    // 对每个关键字进行查找
    for (int i = 0; i < N; ++i) {
        int position = findFirstOccurrence(array, M, keys[i]);
        if (position == -1) {
            printf("Not Found\n");
        } else {
            printf("%d\n", position);
        }
    }

    // 释放内存
    free(array);
    free(keys);

    return 0;
}
