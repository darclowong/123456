//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 使用摩尔投票法寻找候选主元素
 * @param elements 数组指针
 * @param length 数组长度
 * @return 候选主元素
 */
int findCandidate(int* elements, int length) {
    int candidate = elements[0];
    int count = 1;

    // 优化点：使用while循环替代for循环
    int index = 1;
    while (index < length) {
        if (elements[index] == candidate) {
            count++;
        } else if (count == 0) {
            // 当计数为0时更新候选元素
            candidate = elements[index];
            count = 1;
        } else {
            count--;
        }
        index++;
    }

    return candidate;
}

/**
 * 验证候选元素是否为真正的主元素
 * @param elements 数组指针
 * @param length 数组长度
 * @param candidate 候选主元素
 * @return 是否为主元素
 */
int verifyCandidate(int* elements, int length, int candidate) {
    int occurrences = 0;

    // 优化点：使用do-while循环
    int i = 0;
    do {
        if (elements[i] == candidate) {
            occurrences++;
        }
    } while (++i < length);

    return occurrences > length / 2;
}

/**
 * 处理单个测试用例
 * @param caseNumber 测试用例编号
 */
void processTestCase(int caseNumber) {
    int length;
    scanf("%d", &length);

    // 动态分配数组
    int* elements = (int*)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        scanf("%d", &elements[i]);
    }

    // 查找并验证候选元素
    int candidate = findCandidate(elements, length);
    if (verifyCandidate(elements, length, candidate)) {
        printf("%d\n", candidate);
    } else {
        printf("no");
    }

    // 释放资源
    free(elements);
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    // 优化点：使用while循环替代for循环
    int currentCase = 1;
    while (currentCase <= testCases) {
        processTestCase(currentCase);
        currentCase++;
    }

    return 0;
}
