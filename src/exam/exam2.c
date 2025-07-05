//
// Created by 王智杰 on 2025/6/14.
//
//2.活动安排问题（贪心算法）**
//
//Description
//设有n个活动的集合E={1, 2, ..., n}，其中，每个活动都要求使用同一资源，如演讲会场等，而在同一时间内只有一个活动能使用这一资源。
//每个活动i 都有一个要求使用该资源的起始时间 si 和一个结束时间 fi ，且si < fi。如果选择了活动i，则它在半开时间区间[si, fi)内占用资源。
//若区间[si, fi)与区间[sj, fj)不相交，则称活动i与活动j是相容的。也就是说，当 si ≥ fj 或 sj ≥ fi 时，活动 i 与活动 j 相容。
//活动安排问题就是要在所给的活动集合中选出最大的相容活动子集合。
//
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是一个整数n（ n ≤ 1000 ），表示有n个活动。
//接下来n行，每行两个整数 si 和 fi 表示第 i 个活动的起始时间和结束时间。
//
//Output
//对应每个测试样例输出一行，格式为"Case #: D"，其中'#'表示第几个测试样例（从1开始计），D为最大的相容活动子集合的活动数量。
//Sample Input
//1
//11
//1 4
//3 5
//0 6
//5 7
//3 8
//5 9
//6 10
//8 11
//8 12
//2 13
//12 14
//
//Sample Output
//Case 1: 4



//1.先按左边界排序
//cmp()
//#include<stdio.h>
//#include<stdlib.h>
////2.
//
//int cmp(const void *a, const void *b){
//    return ((int *)a)[0] - ((int *)b)[0];
//
//int main() {
////定义二维数组nums[i][j]
//    int nums[1000][2];
////输入测试用例个数
//    int T;
//    scanf("%d", &T);
////输入活动个数
//    int activityNum;
//    scanf("%d", &activityNum);
////遍历二维数组赋值
//    for(int i = 0; i < activityNum; i++){
//    scanf("%d %d", &nums[i][0], &nums[i][1]);
//    }
//
//    for (int i = 0; i < activityNum; i++) {
//    cmp(nums[i][0], nums[i + 1][0]);
//    }
//    for (int i = 1; i < n; i++) {
//        if (nums[i][0] < nums[i - 1][1]) {
//            count++;
//            nums[i][1] = min(nums[i][1], nums[i - 1][1]);
//        }
//    }
//    return n - count;
//}


#include <stdio.h>
#include <stdlib.h>
#include <minmax.h>

// 比较函数，按结束时间升序排序(按右边界排序)
int compare(const void *a, const void *b) {
//    按左边界排序（0是左边界，1是右边界）
    return ((int *)a)[0] - ((int *)b)[0];
}

int main() {
    int T;  //用于存储测试用例的个数
    scanf("%d", &T);//输入测试用例个数
    int t;   //用于循环计数，表示当前处理的测试用例编号
    for (t = 1; t <= T; t++) {
        int n;   //用于存储当前测试用例中活动的数量
        scanf("%d", &n);//输入活动个数n
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
        //左边界排序（开始时间）
        qsort(nums, n, sizeof (int *), compare);
        int count = 0;  //初始化计数器，表示重叠的区间的数量
        for (i = 1; i < n; i++) {
            //遍历剩余的活动，判断当前活动开始时间是否大于等于上一个活动的结束时间
            if (nums[i][0] < nums[i-1][1]) {
                count++;  //增加计数器，表示可以完成更多的活动
                nums[i][1] = min(nums[i][1], nums[i-1][1]);  //将当前活动的右边界取（本活动右边界和上一活动右边界）的较小值
            }
        }
        printf("Case %d: %d\n", t, n - count);  //输出当前测试用例的结果
    }
    return 0;
}

//活动安排问题逻辑思路
//1.定义左边界比较函数compare
//2.输入用例个数和活动数、活动始末时间（特殊情况：活动数为0，结束打印结果）
//3.qsort活动时间排序
//4.活动时间比较是否重叠
//5.更新活动右边界
//6.打印输出结果