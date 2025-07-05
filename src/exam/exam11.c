//
// Created by 王智杰 on 2025/6/14.
//
//11.大整数的乘法（分治）
//
//Description
//设计一个有效的算法，可以进行两个n位大整数的乘法运算
//Input
//有多组输入数据，每个数据有两行，每行代表一个不小于0的整数（每个整数位数小于16）
//Output
//输出两个大整数的乘积
//Sample Input
//972442
//0
//3877923682893532066
//151811172251614534

//Sample Output
//0
//588712140202365414517861194400647244

//
//#include <stdio.h>
//#include <string.h>

//作用：移除字符串前导的零（如 "00123" → "123"）。
//关键点：
//while 循环跳过所有前导零，直到遇到非零字符或字符串末尾。
//memmove 将有效字符前移，覆盖前导零。

//void trim(char *s) {
//    int i = 0;
//    while (s[i] == '0' && s[i+1]) i++; // 跳过前导0
//    if (i) memmove(s, s+i, strlen(s)-i+1); // 移动字符串
//}

//作用：将字符串转换为逆序存储的数字数组（低位在前）。
//关键点：
//输入 "123" → 数组 [3,2,1,0,...]（假设 n=8）。
//逆序是为了方便后续计算进位（从低位到高位处理）。
//void str2arr(const char *s, int *a, int n) {
//    int len = strlen(s);
//    for (int i = 0; i < n; i++)
//        a[i] = (i < len) ? s[len-1-i] - '0' : 0; // 逆序存储
//}

// 作用：将数字数组转换回字符串，去除前导零。
//关键点：
//从高位向低位遍历，跳过前导零。
//将数字转换为字符并拼接结果（如 [3,2,1] → "123"）。
//void arr2str(int *a, int n, char *s) {
//    int i = n-1, j = 0;
//    while (i > 0 && a[i] == 0) i--; // 跳过高位0
//    for (; i >= 0; i--) s[j++] = a[i] + '0'; // 转为字符
//    s[j] = 0;
//}

// 作用：递归分治实现大整数乘法（Karatsuba 思想）。
//关键点：
//递归终止条件：当 n == 1 时直接相乘。
//拆分高低位：
//将输入数组 a 和 b 分为高半部分（A, B）和低半部分（C, D）。
//例如 a = [1,2,3,4] → A = [3,4]（高位），C = [1,2]（低位）。
//分治计算：
//AC = A * B
//BD = C * D
//AB_CD = (A+C) * (B+D)
//组合结果：
//最终结果公式： res = AC * 10^(2m) + (AB_CD - AC - BD) * 10^m + BD
//对应代码中的三段加法。
//进位处理：
//处理超过 10 的进位（如 12 → 2，进位 1）。
//处理负数（如 -1 → 9，借位 -1）。
//void multiply(int *a, int *b, int n, int *res) {
//    if (n == 1) { // 基本情况：一位数相乘
//        res[0] = a[0] * b[0];
//        return;
//    }
//    int m = n/2;
//    int A[8]={0}, B[8]={0}, C[8]={0}, D[8]={0};
//    int AC[16]={0}, BD[16]={0}, AB_CD[16]={0};
//    for (int i = 0; i < m; i++) { // 拆分高低位
//        A[i] = a[i+m]; B[i] = b[i+m];
//        C[i] = a[i];   D[i] = b[i];
//    }
//    multiply(A, B, m, AC); // 高位相乘
//    multiply(C, D, m, BD); // 低位相乘
//    int S1[8]={0}, S2[8]={0};
//    for (int i = 0; i < m; i++) { // (A+C), (B+D)
//        S1[i] = A[i] + C[i];
//        S2[i] = B[i] + D[i];
//    }
//    multiply(S1, S2, m, AB_CD); // (A+C)*(B+D)
//    for (int i = 0; i < n*2; i++) // res清零
//        res[i] = 0;
//    // res = AC*10^(2m) + (AB_CD-AC-BD)*10^m + BD
//    for (int i = 0; i < n; i++) res[i] += BD[i];
//    for (int i = 0; i < n; i++) res[i+m] += AB_CD[i] - AC[i] - BD[i];
//    for (int i = 0; i < n; i++) res[i+n] += AC[i];
//    // 进位处理
//    for (int i = 0; i < n*2-1; i++) {
//        if (res[i] >= 10) { res[i+1] += res[i]/10; res[i] %= 10; }
//        if (res[i] < 0) { res[i+1] -= 1; res[i] += 10; }
//    }
//}

//作用：主程序入口，处理输入、调用乘法、输出结果。
//关键点：
//输入处理：
//使用 scanf 读取两个字符串形式的大整数。
//调用 trim 去除前导零。
//如果任一输入为 0，直接输出 0。
//统一长度：
//取较长字符串的长度 n，若为奇数则加 1（保证偶数分割）。
//转换与计算：
//将字符串转换为逆序数组（str2arr）。
//调用 multiply 进行分治乘法。
//结果转换：
//将结果数组转换回字符串（arr2str），并输出。
//int main() {
//    char sa[20], sb[20];
//    while (scanf("%s%s", sa, sb) == 2) { // 读入两个大整数
//        trim(sa); trim(sb); // 去除前导0
//        if (strcmp(sa, "0") == 0 || strcmp(sb, "0") == 0) { // 有0直接输出0
//            puts("0");
//            continue;
//        }
//        int n = (int)strlen(sa) > strlen(sb) ? strlen(sa) : strlen(sb);
//        if (n & 1) n++; // 保证n为偶数
//        int a[16]={0}, b[16]={0}, res[32]={0};
//        str2arr(sa, a, n); // 字符串转数组
//        str2arr(sb, b, n);
//        multiply(a, b, n/2, res); // 分治乘法
//        char ans[40];
//        arr2str(res, n*2, ans); // 数组转字符串
//        puts(ans); // 输出结果
//    }
//    return 0;
//}

//核心逻辑总结
//        分治策略：将大整数拆分为高低位，递归计算子问题，最后合并结果。
//Karatsuba 优化：通过三次乘法代替四次（传统分治），降低时间复杂度（从 O(n²) 到 O(n^log3)）。
//逆序存储：便于处理进位（从低位到高位）。
//进位处理：确保每一位在 0-9 之间，处理负数时需借位。
//
//示例流程
//        输入：sa = "123"，sb = "456"
//trim 后仍为 "123" 和 "456"。
//str2arr 转换为 a = [3,2,1,0,0,0,0,0]，b = [6,5,4,0,0,0,0,0]（假设 n=8）。
//multiply 递归拆分计算，最终结果数组为 [8,7,0,8,0,0,0,0,0,0,0,0,0,0,0,0]（对应 56088）。
//arr2str 转换为字符串 "56088"，输出结果。

//常见问题
//        为何逆序存储？ 为了方便从低位到高位计算进位（与手算乘法一致）。
//为何需要 n 为偶数？ 便于分治拆分（每次拆分为两半），简化递归逻辑。
//如何处理负数进位？ 当 (AB_CD - AC - BD) 为负数时，通过借位调整（如 res[i] += 10，res[i+1] -= 1）。

//代码实现逻辑说明
//输入与预处理
//读入两个大整数字符串，去除前导0。若有0直接输出0。
//数据转换
//将字符串逆序转为int数组，低位在前，方便模拟竖式乘法。
//补齐为偶数长度，便于分治。
//分治乘法（Karatsuba思想）
//将每个n位数拆成高m位和低m位（n=2m）。
//递归计算高位乘积AC、低位乘积BD、中间项(AB+CD)。
//合并结果：res = AC10^(2m) + (AB_CD-AC-BD)10^m + BD。
//处理进位。
//输出
//结果数组转字符串，去除高位0，输出。
//如何理解实现逻辑
//分治思想：将大整数拆分为高低两部分，递归处理，减少乘法次数（Karatsuba算法核心）。
//数组模拟：用数组逆序存储每一位，方便进位和合并。
//进位处理：每次合并后都要处理进位，保证每位是0~9。
//效率：适合16位以内的整数，递归深度有限，效率高，代码精简。



#include <stdio.h>
#include <string.h>
void trim(char *s) {
    int i = 0;
    while (s[i] == '0' && s[i+1]) i++; // 跳过前导0
    if (i) memmove(s, s+i, strlen(s)-i+1); // 移动字符串
}

void str2arr(const char *s, int *a, int n) {
    int len = strlen(s);
    for (int i = 0; i < n; i++)
        a[i] = (i < len) ? s[len-1-i] - '0' : 0; // 逆序存储
}

void arr2str(int *a, int n, char *s) {
    int i = n-1, j = 0;
    while (i > 0 && a[i] == 0) i--; // 跳过高位0
    for (; i >= 0; i--) s[j++] = a[i] + '0'; // 转为字符
    s[j] = 0;
}

void multiply(int *a, int *b, int n, int *res) {
    if (n == 1) { // 基本情况：一位数相乘
        res[0] = a[0] * b[0];
        return;
    }
    int m = n/2;
    int A[8]={0}, B[8]={0}, C[8]={0}, D[8]={0};
    int AC[16]={0}, BD[16]={0}, AB_CD[16]={0};
    for (int i = 0; i < m; i++) { // 拆分高低位
        A[i] = a[i+m]; B[i] = b[i+m];
        C[i] = a[i];   D[i] = b[i];
    }
    multiply(A, B, m, AC); // 高位相乘
    multiply(C, D, m, BD); // 低位相乘
    int S1[8]={0}, S2[8]={0};
    for (int i = 0; i < m; i++) { // (A+C), (B+D)
        S1[i] = A[i] + C[i];
        S2[i] = B[i] + D[i];
    }
    multiply(S1, S2, m, AB_CD); // (A+C)*(B+D)
    for (int i = 0; i < n*2; i++) // res清零
        res[i] = 0;
    // res = AC*10^(2m) + (AB_CD-AC-BD)*10^m + BD
    for (int i = 0; i < n; i++) res[i] += BD[i];
    for (int i = 0; i < n; i++) res[i+m] += AB_CD[i] - AC[i] - BD[i];
    for (int i = 0; i < n; i++) res[i+n] += AC[i];
    // 进位处理
    for (int i = 0; i < n*2-1; i++) {
        if (res[i] >= 10) { res[i+1] += res[i]/10; res[i] %= 10; }
        if (res[i] < 0) { res[i+1] -= 1; res[i] += 10; }
    }
}

int main() {
    char sa[20], sb[20];
    while (scanf("%s%s", sa, sb) == 2) { // 读入两个大整数
        trim(sa); trim(sb); // 去除前导0
        if (strcmp(sa, "0") == 0 || strcmp(sb, "0") == 0) { // 有0直接输出0
            puts("0");
            continue;
        }
        int n = (int)strlen(sa) > strlen(sb) ? strlen(sa) : strlen(sb);
        if (n & 1) n++; // 保证n为偶数
        int a[16]={0}, b[16]={0}, res[32]={0};
        str2arr(sa, a, n); // 字符串转数组
        str2arr(sb, b, n);
        multiply(a, b, n/2, res); // 分治乘法
        char ans[40];
        arr2str(res, n*2, ans); // 数组转字符串
        puts(ans); // 输出结果
    }
    return 0;
}