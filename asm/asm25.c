//
// Created by 王智杰 on 2025/5/28.
// 修改版二分查找实现：风格重构 + 独立实现
//

#include <stdio.h>
#include <stdlib.h>

// 查找目标值在有序数组中的索引
int findTargetIndex(int *array, int arraySize, int target) {
    // 初始化搜索区间 [start, end]
    int start = 0;
    int end = arraySize - 1;

    // 开始查找
    for (; start <= end;) {
        int mid = start + (end - start) / 2;  // 防止溢出

        if (array[mid] == target) {
            return mid;  // 找到目标
        } else if (array[mid] < target) {
            start = mid + 1;  // 向右半段查找
        } else {
            end = mid - 1;   // 向左半段查找
        }
    }

    return -1;  // 未找到
}

// 打印单个查找结果
void printSearchResult(int index, int key) {
    if (index != -1) {
        printf("%d\n", index);
    } else {
        printf("Not Found\n");
    }
}


int main() {
    int totalElements;
    scanf("%d", &totalElements);

    // 动态分配数组空间
    int *sortedArray = (int *)malloc(totalElements * sizeof(int));
    if (!sortedArray) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // 输入数据
    for (int i = 0; i < totalElements; ++i) {
        scanf("%d", &sortedArray[i]);
    }

    // 查询数量
    int queryCount;
    scanf("%d", &queryCount);

    // 处理每个查询
    for (int i = 0; i < queryCount; ++i) {
        int searchKey;
        scanf("%d", &searchKey);

        int resultIndex = findTargetIndex(sortedArray, totalElements, searchKey);
        printSearchResult(resultIndex, searchKey);
    }

    // 释放资源
    free(sortedArray);

    return 0;
}
