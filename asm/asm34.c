//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 交换两个整数的值
 * @param a 第一个元素指针
 * @param b 第二个元素指针
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * 随机化分区函数
 * @param arr 数组指针
 * @param left 左边界
 * @param right 右边界
 * @return 分区点位置
 */
int randomPartition(int* arr, int left, int right) {
    // 随机选择pivot
    srand(time(NULL));
    int randomIndex = left + rand() % (right - left + 1);
    swap(&arr[randomIndex], &arr[right]);  // 将随机pivot移到末尾

    int partitionValue = arr[right];  // 以最后一个元素为基准
    int i = left;  // 小于基准的元素起始位置

    // 优化点：使用while循环替代for循环
    int j = left;
    while (j < right) {
        if (arr[j] <= partitionValue) {
            swap(&arr[i], &arr[j]);
            i++;
        }
        j++;
    }

    swap(&arr[i], &arr[right]);  // 将基准值放到正确位置
    return i;
}

/**
 * 快速选择算法实现
 * @param arr 数组指针
 * @param left 左边界
 * @param right 右边界
 * @param k 要查找的第k小元素
 * @return 第k小元素的值
 */
int quickSelect(int* arr, int left, int right, int k) {
    // 优化点：调整条件判断顺序
    if (left == right) {
        return arr[left];  // 当数组只有一个元素时
    }

    // 找到分区点
    int partitionIndex = randomPartition(arr, left, right);

    // 优化点：使用switch-case替代if-else
    int elementsCount = partitionIndex - left + 1;
    switch (elementsCount - k) {
        case 0:  // 正好找到第k小元素
            return arr[partitionIndex];
        case 1:  // k在左半部分
        case -1:
        case -2:
        default:
            if (k < elementsCount) {
                return quickSelect(arr, left, partitionIndex - 1, k);
            } else {  // k在右半部分
                return quickSelect(arr, partitionIndex + 1, right, k - elementsCount);
            }
    }
}

/**
 * 处理单个测试用例
 * @param n 数组长度
 * @param k 要查找的第k小元素
 */
void processTestCase(int n, int k) {
    // 动态分配数组
    int* elements = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
    }

    // 查找并输出结果
    int result = quickSelect(elements, 0, n - 1, k);
    printf("%d\n", result);

    // 释放内存
    free(elements);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    processTestCase(n, k);
    return 0;
}
