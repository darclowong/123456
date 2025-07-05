////
//// Created by 王智杰 on 2025/5/27.
////
//#include <stdio.h>
//#include <string.h>
//
//#define MAX_LEN 32
//
//void multiply(char *num1, char *num2, char *result) {
//    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
//        strcpy(result, "0");
//        return;
//    }
//    int len1 = strlen(num1);
//    int len2 = strlen(num2);
//
//    // 结果最多可能有len1 + len2位
//    int resultNums[len1 + len2];
//    memset(resultNums, 0, sizeof(resultNums));
//
//    // 转换为逆序的整型数组
//    int n1[MAX_LEN], n2[MAX_LEN];
//    int i;
//    for (i = 0; i < len1; i++) {
//        n1[i] = num1[len1 - 1 - i] - '0';
//    }
//    for (i = 0; i < len2; i++) {
//        n2[i] = num2[len2 - 1 - i] - '0';
//    }
//
//    // 相乘并累加到对应位置
//    for (i = 0; i < len1; i++) {
//        for (int j = 0; j < len2; j++) {
//            resultNums[i + j] += n1[i] * n2[j];
//        }
//    }
//
//    // 进位处理
//    for (i = 0; i < len1 + len2 - 1; i++) {
//        if (resultNums[i] >= 10) {
//            resultNums[i + 1] += resultNums[i] / 10;
//            resultNums[i] %= 10;
//        }
//    }
//
//    // 找到最高位的位置
//    int highestIndex = len1 + len2 - 1;
//    while (highestIndex > 0 && resultNums[highestIndex] == 0) {
//        highestIndex--;
//    }
//
//    // 转换为字符串结果
//    for (i = 0; i <= highestIndex; i++) {
//        result[i] = resultNums[highestIndex - i] + '0';
//    }
//    result[highestIndex + 1] = '\0';
//}
//
//int main() {
//    char num1[MAX_LEN], num2[MAX_LEN], result[2 * MAX_LEN];
//
//    // 读取输入
//    scanf("%s", num1);
//    scanf("%s", num2);
//
//    // 计算乘积
//    multiply(num1, num2, result);
//
//    // 输出结果
//    printf("%s\n", result);
//
//    return 0;
//}














#include <stdio.h>
#include <string.h>

// 定义最大数字长度
#define MAX_DIGITS 32

/**
 * 将字符串形式的数字转换为逆序的整型数组
 * @param str 输入数字字符串
 * @param arr 输出整型数组
 * @return 数组有效长度
 */
int strToDigitArray(const char* str, int* arr) {
    int len = (int)strlen(str);
    int i;
    for (i = 0; i < len; ++i) {
        arr[i] = str[len - 1 - i] - '0';
    }
    return len;
}

/**
 * 将整型数组转换为字符串形式的结果
 * @param digits 整型数组
 * @param length 数组长度
 * @param result 输出字符串
 */
void digitArrayToStr(int* digits, int length, char* result) {
    int index = length;
    while (index > 0 && digits[index - 1] == 0) {
        --index;
    }

    if (index == 0) {
        strcpy(result, "0");
        return;
    }
    int i;
    for (i = 0; i < index; ++i) {
        result[i] = digits[index - 1 - i] + '0';
    }
    result[index] = '\0';
}

/**
 * 实现两个大整数的乘法运算
 * @param num1 第一个操作数
 * @param num2 第二个操作数
 * @param result 输出结果
 */

void bigMultiply(const char* num1, const char* num2, char* result) {
    // 特殊情况处理：如果任意一方为0直接返回0
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        strcpy(result, "0");
        return;
    }

    int numArray1[MAX_DIGITS], numArray2[MAX_DIGITS];
    int len1 = strToDigitArray(num1, numArray1);
    int len2 = strToDigitArray(num2, numArray2);

    // 初始化结果数组
    int productDigits[MAX_DIGITS * 2] = {0};

    // 逐位相乘并累加
    int i = 0;
    while (i < len1) {
        int j = 0;
        while (j < len2) {
            productDigits[i + j] += numArray1[i] * numArray2[j];
            ++j;
        }
        ++i;
    }

    // 处理进位
    int k;
    for (k = 0; k < len1 + len2 - 1; ++k) {
        if (productDigits[k] >= 10) {
            productDigits[k + 1] += productDigits[k] / 10;
            productDigits[k] %= 10;
        }
    }

    // 转换为字符串输出
    digitArrayToStr(productDigits, len1 + len2, result);
}

int main() {
    char input1[MAX_DIGITS], input2[MAX_DIGITS], output[2 * MAX_DIGITS];

//    printf("请输入第一个非负整数: ");
    scanf("%s", input1);

//    printf("请输入第二个非负整数: ");
    scanf("%s", input2);

    bigMultiply(input1, input2, output);

//    printf("两数乘积为: %s\n", output);
    printf("%s\n", output);

    return 0;
}

/*
Description

设计一个有效的算法，可以进行两个n位大整数的乘法运算
Input
单测试用例，输入数据有两行，每行代表一个不小于0的整数（每个整数位数小于16）
Output
输出两个大整数的乘积
Sample Input
972442
0

Sample Output
0

Sample Input
3877923682893532066
151811172251614534

Sample Output
588712140202365414517861194400647244
 */