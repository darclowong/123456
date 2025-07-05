#include <stdio.h>
#include <stdlib.h>

/**
 * 集装箱信息结构体
 */
typedef struct {
    int mass;       // 集装箱重量
    int identifier; // 集装箱编号
} ShippingBox;

/**
 * 冒泡排序实现 - 按照集装箱重量升序排序
 * 
 * @param boxes 集装箱数组
 * @param count 集装箱数量
 */
void bubbleSortByWeight(ShippingBox* boxes, int count) {
    int swapped;
    ShippingBox temp;
    
    // 外层循环：每次将最重的元素冒泡到末尾
    for (int i = 0; i < count - 1; i++) {
        swapped = 0;
        
        // 内层循环：比较相邻元素并交换
        for (int j = 0; j < count - i - 1; j++) {
            if (boxes[j].mass > boxes[j + 1].mass) {
                // 交换元素
                temp = boxes[j];
                boxes[j] = boxes[j + 1];
                boxes[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // 如果没有发生交换，说明已经排序完成
        if (!swapped) {
            break;
        }
    }
}

/**
 * 装载集装箱并返回结果
 * 
 * @param boxes 集装箱数组
 * @param boxCount 集装箱数量
 * @param shipCapacity 船舶最大载重量
 * @param loadedWeight 输出参数：已装载的总重量
 * @return 成功装载的集装箱数量
 */
int loadShip(ShippingBox* boxes, int boxCount, int shipCapacity, int* loadedWeight) {
    // 初始化结果变量
    int boxesLoaded = 0;
    int currentWeight = 0;
    
    // 从最轻的集装箱开始尝试装载
    for (int i = 0; i < boxCount; i++) {
        // 检查是否可以装载当前集装箱
        if (currentWeight + boxes[i].mass <= shipCapacity) {
            // 装载集装箱
            currentWeight += boxes[i].mass;
            boxesLoaded++;
        } else {
            // 无法继续装载
            break;
        }
    }
    
    // 返回已装载的总重量
    *loadedWeight = currentWeight;
    
    return boxesLoaded;
}

/**
 * 处理单个测试用例
 * 
 * @param testNumber 测试用例编号
 */
void processTestCase(int testNumber) {
    // 读取集装箱数量和船舶载重量
    int boxCount, maxCapacity;
    scanf("%d %d", &boxCount, &maxCapacity);
    
    // 分配内存并读取集装箱数据
    ShippingBox* boxes = (ShippingBox*)malloc(boxCount * sizeof(ShippingBox));
    if (!boxes) {
        fprintf(stderr, "内存分配失败，无法继续执行\n");
        exit(1);
    }
    
    // 读取每个集装箱的重量
    for (int i = 0; i < boxCount; i++) {
        scanf("%d", &boxes[i].mass);
        boxes[i].identifier = i + 1;  // 为每个集装箱分配唯一编号
    }
    
    // 按重量对集装箱进行排序（从轻到重）
    bubbleSortByWeight(boxes, boxCount);
    
    // 执行装载过程
    int totalLoadedWeight;
    int boxesLoaded = loadShip(boxes, boxCount, maxCapacity, &totalLoadedWeight);
    
    // 输出结果
    printf("Case %d: %d %d\n", testNumber, boxesLoaded, totalLoadedWeight);
    
    // 释放内存
    free(boxes);
}

/**
 * 主函数 - 程序入口
 */
int main() {
    // 读取测试用例数量
    int testCaseCount;
    scanf("%d", &testCaseCount);
    
    // 处理每个测试用例
    for (int i = 1; i <= testCaseCount; i++) {
        processTestCase(i);
    }
    
    return 0;
}