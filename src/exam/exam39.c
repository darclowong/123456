//
// Created by 王智杰 on 2025/6/14.
//
//39.最优装载问题（贪心算法）**

//Description
//有一批集装箱要装上一艘载重量为C的轮船。其中集装箱i的重量为wi。最优装载问题要求确定在装载体积不受限制的情况下，将尽可能多的集装箱装上轮船。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是一个非负整数n（ n ≤ 1000 ）和一个非负整数C（ C ≤ 10000 ），分别表示集装箱的个数以及轮船的载重量。接下来有n行，每行一个非负数，表示每个集装箱的重量。
//Output
//对应每个测试样例输出一行，格式为"Case #: D V"，其中'#'表示第几个测试样例（从1开始计），D为轮船可以装载的集装箱数量的最大值，V为满足D最大时轮船的实际载重量。
//Sample Input
//1
//5 100
//20
//50
//120
//99
//30

//Sample Output
//Case 1: 3 100

//#include<stdio.h>
//#include<stdlib.h>
//
//int compare(const void *a,const void *b){
//    return (*(int *)a - *(int *)b); //返回的是差（相减）的整体
//}
//
//int main(){
//    int T;
//    scanf("%d",&T);
//    for(int t = 1; t <= T;t++) {
//        int n, C, curWt,count;
//        scanf("%d %d", &n, &C);
//        int *BoxWt = (int *) malloc(n * sizeof(int)); //最后需要释放空间
//        curWt = 0;
//        count = 0;
//        for (int i = 0; i < n; i++) {
//            scanf("%d", &BoxWt[i]);
//        }
//        //贪心算法快排:从小到大
//        qsort(BoxWt, n, sizeof(int), compare);
//        for (int i = 0; i < n; i++) {
//            if (C >= curWt + BoxWt[i]){
//                curWt += BoxWt[i];
//                count++;
//            }else{
//                break;
//            }
//        }
//        printf("Case %d: %d %d\n",t,count,curWt);
//        free(BoxWt);
//    }
//    return 0;
//}



#include<stdio.h>
#include<stdlib.h>

int compare(const void *a,const void *b){  //比较排序，从大到小，需要用到内置函数qsort
    return (*(int *)a - *(int *)b);
}

int main(){
    int T;
    scanf("%d",&T);//输入测试用例个数
    for(int t = 1;t <= T;t++){
        int n,C;
        scanf("%d %d",&n,&C);//输入集装箱个数和船的容量
        int *BoxWt = (int *)malloc(n * sizeof(int)); //动态分配 集装箱重量
        for(int i = 0; i < n;i++){
        scanf("%d",&BoxWt[i]);//输入集装箱的重量
    }
        int curWt = 0;//定义并初始化当前轮船重量
        int count = 0;//定义能装集装箱的最大个数
        //贪心算法快排（关键排序）
        qsort(BoxWt,n,sizeof(int),compare);
        for(int i = 0; i < n; i++){
            if(C >= curWt + BoxWt[i]){
                curWt += BoxWt[i];
                count++;
            }else {
                break;//超重时停止装载break
            }
        }
        printf("Case %d: %d %d\n",t,count,curWt);//打印输出
        free(BoxWt);//释放动态分配内存空间
    }
    return 0;
    }