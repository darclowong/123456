//
// Created by 王智杰 on 2025/4/1.
//

//Description
//设有n个活动的集合E={1, 2, ..., n}，其中，每个活动都要求使用同一资源，如演讲会场等，而在同一时间内
//只有一个活动能使用这一资源。每个活动i 都有一个要求使用该资源的起始时间 si 和一个结束时间 fi ，
// 且si < fi。如果选择了活动i，则它在半开时间区间[si, fi)内占用资源。
// 若区间[si, fi)与区间[sj, fj)不相交，则称活动i与活动j是相容的。
// 也就是说，当 si ≥ fj 或 sj ≥ fi 时，活动 i 与活动 j 相容。
// 活动安排问题就是要在所给的活动集合中选出最大的相容活动子集合。

//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是一个整数n（ n ≤ 1000 ），表示有n个活动。
//Output
//对应每个测试样例输出一行，格式为"Case #: D"，其中'#'表示第几个测试样例（从1开始计），
//D为最大的相容活动子集合的活动数量。*

//#include <stdio.h>
//#include <stdlib.h>
//
//// 定义一个结构体Activity，用于存储活动的开始时间和结束时间
//typedef struct {
//    int start;  //活动开始时间
//    int end;  //活动结束时间
//} Activity;
//
//// 比较函数，按结束时间升序排序(按右边界排序)
//int compare(const void *a, const void *b) {
//    Activity *actA = (Activity *)a;  //将第一个参数转换为Activity类型
//    Activity *actB = (Activity *)b;  //将第二个参数转换为Activity类型
//    return actA->end - actB->end;  //结果返回两个活动结束时间的差值，实现升序排序
//}
//
//int main() {
//    int T;  //用于存储测试用例的个数
//    scanf("%d", &T);
//    int t;   //用于循环计数，表示当前处理的测试用例编号
//    for (t = 1; t <= T; t++) {
//        int n;   //用于存储当前测试用例中活动的数量
//        scanf("%d", &n);
//        Activity acts[1005];   //定义一个数组，最多存储1005个活动的信息
//        int i;  //用于循环计数，表示当前处理的活动编号
//        for (i = 0; i < n; i++) {
//            //输出活动的开始时间和结束时间
//            scanf("%d %d", &acts[i].start, &acts[i].end);
//        }
//        if (n == 0) {
//            //如果活动个数为0，输出当前测试用例结果为0
//            printf("Case %d: 0\n", t);
//            continue;   //跳过后续逻辑，直接处理下一个测试用例
//        }
//        // 按结束时间升序排序活动数组
//        qsort(acts, n, sizeof(Activity), compare);
//        int count = 1;  //初始化计数器，表示至少可以完成一个活动
//        int last_end = acts[0].end;  //记录第一个活动的结束时间
//        for (i = 1; i < n; i++) {
//            //遍历剩余的活动，判断当前活动开始时间是否大于等于上一个活动的结束时间
//            if (acts[i].start >= last_end) {
//                count++;  //增加计数器，表示可以完成更多的活动
//                last_end = acts[i].end;  //将当前活动的结束时间赋值给last_end，更新记录的结束时间
//            }
//        }
//        printf("Case %d: %d\n", t, count);  //输出当前测试用例的结果
////        count为最大的相容活动子集合的活动数量
//    }
//    return 0;
//}

//Sample Input
1
11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 14

//Sample Output
//Case 1: 4


#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体Activity，用于存储活动的开始时间和结束时间
//typedef struct {
//    int start;  //活动开始时间
//    int end;  //活动结束时间
//} Activity;

// 比较函数，按结束时间升序排序(按右边界排序)
int compare(const void *a, const void *b) {
//    按左边界排序
    return ((int *)a)[0] - ((int *)b)[0];
}

int main() {
    int T;  //用于存储测试用例的个数
    scanf("%d", &T);
    int t;   //用于循环计数，表示当前处理的测试用例编号
    for (t = 1; t <= T; t++) {
        int n;   //用于存储当前测试用例中活动的数量
        scanf("%d", &n);
        int nums[1005][2];//定义一个数组，最多存储1005个活动的信息
        int i;  //用于循环计数，表示当前处理的活动编号
        for (i = 0; i < n; i++) {
            //输出活动的开始时间和结束时间
            scanf("%d %d", &nums[i][0], &nums[i][1]);
        }
        if (n == 0) {
            //如果活动个数为0，输出当前测试用例结果为0
            printf("Case %d: 0\n", t);
            continue;   //跳过后续逻辑，直接处理下一个测试用例
        }
        // 按结束时间升序排序活动数组
        qsort(nums, n, sizeof(nums), compare);
        int count = 1;  //初始化计数器，表示至少可以完成一个活动
        int last_end = nums[0][1];  //记录第一个活动的结束时间
        for (i = 1; i < n; i++) {
            //遍历剩余的活动，判断当前活动开始时间是否大于等于上一个活动的结束时间
            if (nums[i][0] < last_end) {
                count++;  //增加计数器，表示可以完成更多的活动
                last_end = nums[i][1];  //将当前活动的结束时间赋值给last_end，更新记录的结束时间
            }
        }
        printf("Case %d: %d\n", t, count);  //输出当前测试用例的结果
//        count为最大的相容活动子集合的活动数量
    }
    return 0;
}