//
// Created by 王智杰 on 2025/6/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * 矩阵最大子矩阵和问题求解器
 * 采用前缀和优化的二维Kadane算法实现
 */

/**
 * 矩阵区域定义结构体
 */
typedef struct {
    int startRow;    // 起始行
    int endRow;      // 结束行
    int startCol;    // 起始列
    int endCol;      // 结束列
    int sum;         // 区域和
} MatrixRegion;

/**
 * 矩阵数据容器
 */
typedef struct {
    int rows;           // 矩阵行数
    int cols;           // 矩阵列数
    int** elements;     // 矩阵元素
    int** prefixSums;   // 前缀和数组(优化计算)
} Matrix;

/**
 * 初始化矩阵结构
 * 
 * @param matrix 矩阵指针
 * @param rowCount 行数
 * @param colCount 列数
 * @return 初始化是否成功
 */
bool initializeMatrix(Matrix* matrix, int rowCount, int colCount) {
    if (rowCount <= 0 || colCount <= 0) {
        return false;
    }
    
    matrix->rows = rowCount;
    matrix->cols = colCount;
    
    // 分配矩阵元素内存
    matrix->elements = (int**)malloc(rowCount * sizeof(int*));
    if (!matrix->elements) {
        return false;
    }
    
    for (int i = 0; i < rowCount; i++) {
        matrix->elements[i] = (int*)malloc(colCount * sizeof(int));
        if (!matrix->elements[i]) {
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(matrix->elements[j]);
            }
            free(matrix->elements);
            return false;
        }
    }
    
    // 分配前缀和数组内存 (大小为(rows+1)*(cols+1)便于计算)
    matrix->prefixSums = (int**)malloc((rowCount + 1) * sizeof(int*));
    if (!matrix->prefixSums) {
        // 释放矩阵元素内存
        for (int i = 0; i < rowCount; i++) {
            free(matrix->elements[i]);
        }
        free(matrix->elements);
        return false;
    }
    
    for (int i = 0; i <= rowCount; i++) {
        matrix->prefixSums[i] = (int*)calloc(colCount + 1, sizeof(int));
        if (!matrix->prefixSums[i]) {
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(matrix->prefixSums[j]);
            }
            free(matrix->prefixSums);
            
            for (int j = 0; j < rowCount; j++) {
                free(matrix->elements[j]);
            }
            free(matrix->elements);
            return false;
        }
    }
    
    return true;
}

/**
 * 清理矩阵资源
 * 
 * @param matrix 矩阵指针
 */
void cleanupMatrix(Matrix* matrix) {
    if (matrix->elements) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->elements[i]);
        }
        free(matrix->elements);
        matrix->elements = NULL;
    }
    
    if (matrix->prefixSums) {
        for (int i = 0; i <= matrix->rows; i++) {
            free(matrix->prefixSums[i]);
        }
        free(matrix->prefixSums);
        matrix->prefixSums = NULL;
    }
}

/**
 * 从标准输入读取矩阵数据
 * 
 * @param matrix 矩阵指针
 * @return 读取是否成功
 */
bool loadMatrixData(Matrix* matrix) {
    // 读取矩阵元素
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (scanf("%d", &matrix->elements[i][j]) != 1) {
                return false;
            }
        }
    }
    
    // 计算二维前缀和
    // prefixSums[i][j]表示从(0,0)到(i-1,j-1)的子矩阵和
    for (int i = 1; i <= matrix->rows; i++) {
        for (int j = 1; j <= matrix->cols; j++) {
            matrix->prefixSums[i][j] = matrix->elements[i-1][j-1]
                                     + matrix->prefixSums[i-1][j]
                                     + matrix->prefixSums[i][j-1]
                                     - matrix->prefixSums[i-1][j-1];
        }
    }
    
    return true;
}

/**
 * 计算指定范围内的子矩阵和
 * 使用前缀和实现O(1)时间复杂度的查询
 * 
 * @param matrix 矩阵指针
 * @param r1 起始行
 * @param c1 起始列
 * @param r2 结束行
 * @param c2 结束列
 * @return 子矩阵和
 */
int getSubmatrixSum(const Matrix* matrix, int r1, int c1, int r2, int c2) {
    // 注意：前缀和数组的索引比实际矩阵大1
    return matrix->prefixSums[r2+1][c2+1]
         - matrix->prefixSums[r2+1][c1]
         - matrix->prefixSums[r1][c2+1]
         + matrix->prefixSums[r1][c1];
}

/**
 * 寻找一维数组的最大子段和及其位置
 * 
 * @param array 输入数组
 * @param length 数组长度
 * @param startPos 输出参数：最大子段的起始位置
 * @param endPos 输出参数：最大子段的结束位置
 * @return 最大子段和
 */
int findMaxSubarrayWithPosition(const int* array, int length, int* startPos, int* endPos) {
    if (length <= 0) return 0;
    
    int maxSum = array[0];
    int currentSum = array[0];
    int currentStart = 0;
    *startPos = 0;
    *endPos = 0;
    
    for (int i = 1; i < length; i++) {
        // 如果当前累计和为负，则重新开始累计
        if (currentSum < 0) {
            currentSum = array[i];
            currentStart = i;
        } else {
            currentSum += array[i];
        }
        
        // 更新最大和及其位置
        if (currentSum > maxSum) {
            maxSum = currentSum;
            *startPos = currentStart;
            *endPos = i;
        }
    }
    
    return maxSum;
}

/**
 * 计算矩阵的最大子矩阵和
 * 
 * @param matrix 矩阵指针
 * @return 最大子矩阵和
 */
int findMaximumSubmatrixSum(Matrix* matrix) {
    int maxSum = matrix->elements[0][0]; // 初始化为第一个元素
    
    // 临时数组用于存储列的累加和
    int* tempArray = (int*)malloc(matrix->cols * sizeof(int));
    if (!tempArray) return maxSum;
    
    // 枚举所有可能的行范围
    for (int startRow = 0; startRow < matrix->rows; startRow++) {
        // 重置临时数组
        memset(tempArray, 0, matrix->cols * sizeof(int));
        
        for (int endRow = startRow; endRow < matrix->rows; endRow++) {
            // 累加当前行到临时数组
            for (int col = 0; col < matrix->cols; col++) {
                tempArray[col] += matrix->elements[endRow][col];
            }
            
            // 在临时数组上应用Kadane算法找最大子段和
            int startCol, endCol;
            int currentSum = findMaxSubarrayWithPosition(tempArray, matrix->cols, &startCol, &endCol);
            
            // 更新全局最大和
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }
        }
    }
    
    free(tempArray);
    return maxSum;
}

/**
 * 处理单个测试用例
 * 
 * @return 处理是否成功
 */
bool solveTestCase() {
    int rowCount, colCount;
    
    // 读取矩阵维度
    if (scanf("%d %d", &rowCount, &colCount) != 2) {
        return false;
    }
    
    // 初始化矩阵
    Matrix matrix;
    if (!initializeMatrix(&matrix, rowCount, colCount)) {
        fprintf(stderr, "矩阵初始化失败\n");
        return false;
    }
    
    // 加载矩阵数据
    if (!loadMatrixData(&matrix)) {
        fprintf(stderr, "矩阵数据加载失败\n");
        cleanupMatrix(&matrix);
        return false;
    }
    
    // 计算最大子矩阵和
    int result = findMaximumSubmatrixSum(&matrix);
    
    // 输出结果
    printf("%d\n", result);
    
    // 清理资源
    cleanupMatrix(&matrix);
    
    return true;
}

/**
 * 程序入口
 */
int main() {
    int testCaseCount;
    
    // 读取测试用例数量
    scanf("%d", &testCaseCount);
    
    // 处理每个测试用例
    for (int i = 0; i < testCaseCount; i++) {
        if (!solveTestCase()) {
            break;
        }
    }
    
    return 0;
}
