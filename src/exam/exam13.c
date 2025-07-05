//
// Created by 王智杰 on 2025/6/14.
//
//13.最优装载（贪心算法）**
//
//Description
//有一批集装箱要装上一艘载重量为C的轮船。其中集装箱i的重量为wi。最优装载问题要求确定在装载体积不受限制的情况下，将尽可能多的集装箱装上轮船。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是一个非负整数n（ n ≤ 1000 ）和一个非负整数C（ C ≤ 10000 ），分别表示集装箱的个数以及轮船的载重量。
//接下来有n行，每行一个非负数，表示每个集装箱的重量。
//Output
//对应每个测试样例输出一行，格式为"Case #: D V"，其中'#'表示第几个测试样例（从1开始计），D为轮船可以装载的集装箱数量的最大值，
// V为满足D最大时轮船的实际载重量。
//Sample Input
//1
//5 100
//20
//50
//120
//99
//30
//
//Sample Output
//Case 1: 3 100


#include <stdio.h>
#include <stdlib.h>
// 比较函数：用于qsort排序（从小到大）
int compare(const void *a, const void *b) { //因为 void 类型没有大小或数据结构，无法知道如何解引用它
    return (*(int*)a - *(int*)b);  //(int*)a：将 void* 指针 a 转换为 int* 类型，表示它现在指向一个 int 值。
}  //*(int*)a：解引用这个 int* 指针，获取它所指向的实际 int 值。
    //必须通过类型转换将 void* 转换为具体的指针类型（如 int*）后，再解引用获取值
//    使用 (*(int*)a - *(int*)b) 可以确保 qsort 正确地根据 int 值进行比较和排序

int main() {
    int T;
    scanf("%d", &T); // 测试样例个数

    for (int t = 1; t <= T; t++) {
        int n, C;
        scanf("%d %d", &n, &C); // 集装箱个数和轮船载重量

        int *BoxWeight = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &BoxWeight[i]); // 读取每个集装箱重量
        }
//        获取所有集装箱重量后进行从小到大排序
        // 按重量从小到大排序（贪心策略关键）
        qsort(BoxWeight, n, sizeof(int), compare);

        int count = 0;      // 装载的集装箱数量
        int currentWt = 0;    // 当前装载的总重量

        for (int i = 0; i < n; i++) {  // 尝试装载每个集装箱
            if (currentWt + BoxWeight[i] <= C) { // 检查装载后是否超重
                currentWt += BoxWeight[i]; // 更新当前重量
                count++;               // 增加计数
            } else {
                break; // 超重则停止装载break
            }
        }
        // 输出结果（注意实际载重量是currentWt而非C）
        printf("Case %d: %d %d\n", t, count, currentWt);

        free(BoxWeight); // 释放内存
    }
    return 0;
}


//疑惑点解析：
//，qsort() 是 C 语言标准库 <stdlib.h> 中提供的一个内置函数，
//用于对数组进行快速排序（Quick Sort）。它是一个通用排序函数，可以对任意类型的数组进行排序，只要提供合适的比较函数。
//函数原型：
//void qsort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));
//参数说明：
//base
//指向要排序的数组第一个元素的指针。例如：BoxWeight。
//类型为 void*，表示可以传入任何类型的数组。
//nmemb
//数组中元素的个数（不是字节数）。
//例如你代码中的变量 n。
//size
//每个元素所占的字节数，通常使用 sizeof(type) 来获取。
//例如：sizeof(int) 表示每个元素是一个整型。
//compare
//指向比较函数的函数指针。
//这个函数需要接受两个 const void* 类型的参数，并返回一个 int 值来决定它们的顺序。
//你的代码中使用的是 compare 函数。
//示例调用：
//你当前的调用：
//qsort(BoxWeight, n, sizeof(int), compare);
//这行代码的作用是：
//对数组 BoxWeight 进行排序；
//数组中有 n 个元素；
//每个元素的大小是 sizeof(int)；
//使用 compare 函数作为比较规则。
//比较函数要求：
//你的比较函数应该遵循如下格式：
//返回值说明：
//如果返回负值，则 a 应排在 b 前面；
//如果返回零，则两者相等或顺序不变；
//如果返回正值，则 b 应排在 a 前面。
//例如：
//int compare(const void *a, const void *b) {
//    return (*(int*)a - *(int*)b); // 升序排列
//}
//注意事项：
//qsort() 是原地排序（不会创建新数组），排序后的结果会直接反映在原始数组上。
//比较函数必须符合规范，否则可能导致未定义行为。
//qsort() 的效率较高，平均时间复杂度为 O(n log n)，但最坏情况下为 O(n²)（取决于数据分布）。
//如果你希望实现降序排序，只需将比较函数改为：return (*(int*)b - *(int*)a);