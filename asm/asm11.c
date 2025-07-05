//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//#define MAX_DIGITS 16
//
//char* multiply(char num1[], char num2[]) {
//    int len1 = strlen(num1);
//    int len2 = strlen(num2);
//    int resultLen = len1 + len2;
//    int *result = (int *)calloc(resultLen, sizeof(int));
//
//    // 处理特殊情况
//    if (len1 == 0 || len2 == 0) {
//        free(result);
//        char *zero = (char *)malloc(sizeof(char) * 2);
//        strcpy(zero, "0");
//        return zero;
//    }
//
//    // 从右到左遍历
//    for (int i = len1-1; i >= 0; i--) {
//        for (int j = len2-1; j >= 0; j--) {
//            int digit1 = num1[i] - '0';
//            int digit2 = num2[j] - '0';
//
//            // 计算乘积和对应位置
//            int product = digit1 * digit2;
//            int sum = result[i + j + 1] + product;
//
//            // 更新结果
//            result[i + j + 1] = sum % 10;
//            result[i + j] += sum / 10;
//        }
//    }
//
//    // 转换为字符串
//    char *resultStr = (char *)malloc(sizeof(char) * (resultLen + 1));
//    int index = 0;
//
//    // 跳过前导零
//    while (index < resultLen && result[index] == 0) {
//        index++;
//    }
//
//    if (index == resultLen) {
//        resultStr[0] = '0';
//        resultStr[1] = '\0';
//    } else {
//        int k = 0;
//        while (index < resultLen) {
//            resultStr[k++] = result[index] + '0';
//            index++;
//        }
//        resultStr[k] = '\0';
//    }
//
//    free(result);
//    return resultStr;
//}
//
//int main() {
//    char num1[MAX_DIGITS+1], num2[MAX_DIGITS+1];
//
//    // 读取多组输入
//    while (scanf("%s%s", num1, num2) != EOF) {
//        char *result = multiply(num1, num2);
//        printf("%s\n", result);
//        free(result);
//    }
//
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大支持数字长度
#define MAX_DIGITS 32

/**
 * 判断输入字符串是否为 "0"
 */
int isZero(const char* str) {
    return strlen(str) == 1 && str[0] == '0';
}

/**
 * 将字符串逆序存储到新的字符数组中
 */
void reverseString(const char* src, char* dest) {
    int length = (int)strlen(src);
    for (int i = 0; i < length; ++i) {
        dest[i] = src[length - 1 - i];
    }
    dest[length] = '\0';
}

/**
 * 实现两个大整数相乘的核心函数
 */
char* multiplyTwoLargeNumbers(const char* num1, const char* num2) {
    // 特殊情况处理：任意一个为0，直接返回"0"
    if (isZero(num1) || isZero(num2)) {
        char* zeroResult = (char*)malloc(2);
        strcpy(zeroResult, "0");
        return zeroResult;
    }

    int len1 = (int)strlen(num1);
    int len2 = (int)strlen(num2);
    int totalLength = len1 + len2;

    // 初始化结果数组
    int* productArray = (int*)calloc(totalLength, sizeof(int));

    // 转换为逆序字符串以便从低位开始计算
    char reversedNum1[MAX_DIGITS], reversedNum2[MAX_DIGITS];
    reverseString(num1, reversedNum1);
    reverseString(num2, reversedNum2);

    // 执行每一位相乘并累加
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            int digit1 = reversedNum1[i] - '0';
            int digit2 = reversedNum2[j] - '0';
            productArray[i + j] += digit1 * digit2;
            productArray[i + j + 1] += productArray[i + j] / 10;
            productArray[i + j] %= 10;
        }
    }

    // 转换为字符串结果
    char* resultStr = (char*)malloc(totalLength + 1);
    int index = totalLength - 1;

    // 去除前导零
    while (index >= 0 && productArray[index] == 0) {
        --index;
    }

    if (index < 0) {
        resultStr[0] = '0';
        resultStr[1] = '\0';
    } else {
        int k = 0;
        while (index >= 0) {
            resultStr[k++] = productArray[index--] + '0';
        }
        resultStr[k] = '\0';
    }

    free(productArray);
    return resultStr;
}

/**
 * 主函数：支持多组输入输出
 */
int main() {
    char input1[MAX_DIGITS + 1], input2[MAX_DIGITS + 1];

    // 循环读取输入并输出结果
    while (scanf("%s%s", input1, input2) != EOF) {
        char* result = multiplyTwoLargeNumbers(input1, input2);
        printf("%s\n", result);
        free(result);  // 释放每次的结果内存
    }

    return 0;
}
