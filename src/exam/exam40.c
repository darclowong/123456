//
// Created by 王智杰 on 2025/6/14.
//
//40.二分查找（分治）
//
//Description
//二分查找又叫折半查找。它采用的是"分治策略"。
//给出从小到大排好序的M个整数，查找是否存在某个整数，如果存在，则输出其位置。
//Input
//第一行是一个整数 M ( 0 < M ≤ 200000 ) 表示整数的个数。
//接下来是M个整数，每个整数之间用一个空格分隔。
//接下来一行是一个整数N，表示要查找的关键字个数。
//接下来N个整数，表示要查找的关键字key。每个key之间一个空格分隔。
//Output
//对每个要查找的key，输出一行结果。
//如果找到，输出key在这M个整数的位置，位置从0开始编号。
//如果找不到，则输出 Not Found
//Sample Input
//10
//1 2 4 6 7 8 9 11 20 85
//4
//1 5 20 99
//
//Sample Output
//0
//Not Found
//8
//Not Found

//#include<stdio.h>
//#include<stdlib.h>
//
//int binarySearch(int *a, int b,int size) {
//    int Start = 0;
//    int End = size - 1;
//    while(Start <= End) {
//        int Mid = (Start + End) / 2; //防止整数溢出
//        if (b == a[Mid]) {
//            return Mid;
//        } else if (b < a[Mid]) {
//            End = Mid - 1;
//        } else {
//            Start = Mid + 1;
//        }
//    }
//    return -1;
//}
//int main() {
//    int *a,*b;
//    int index,N,M;
//
//    scanf("%d\n", &M);
//    a = (int *) malloc(M * sizeof(int));
//
//    for (int i = 0; i < M; i++) {
//        scanf("%d", &a[i]);
//    }
//
//    scanf("%d\n", &N);
//    b = (int *) malloc(N * sizeof(int));
//
//    for (int i = 0; i < N; i++) {
//        scanf("%d", &b[i]);
//
//        index = binarySearch(a,b[i],M);
//        if(index == -1){
//            printf("Not Found\n");
//        }else{
//            printf("%d\n", index);
//        }
//    }
//
//    free(a);
//    free(b);
//    return 0;
//}


#include<stdio.h>
#include<stdlib.h>

int binarySearch(int *a,int b,int size){ //定义二分查找函数
    int start = 0;//定义左边界（起始）
    int end = size - 1;//定义右边界（结束）
    while(start <= end){ //当左边界大于右边界时停止循环
        int mid = (start +end) / 2;  //中间值（中点）
        if(b == a[mid]) //等于查找值key时，返回下标
            return mid;
        else if(b < a[mid]) //大于查找值key时，重新定义右边界（结束）
            end = mid - 1;
        else   //小于查找值key时，重新定义左边界（起始）
            start = mid + 1;
    }
    return -1; //没有找到key，返回-1
}

int main(){
    int *a,*b;//定义整数数组，和key数组
    int M,N,index;

    scanf("%d",&M);//输入整数个数
    a = (int *)malloc(M * sizeof(int));//动态分配整数数组
    for(int i = 0; i < M; i++)
        scanf("%d",&a[i]);//输入整数

    scanf("%d",&N);//输入key的个数
    b = (int *)malloc(N * sizeof(int));//动态分配key数组
    for(int i = 0; i < N; i++){
        scanf("%d",&b[i]);//输入key
        index = binarySearch(a,b[i],M);//调用二分查找函数，返回key值下标
        if(index == -1)
            printf("Not Found\n");//打印输出
        else
            printf("%d\n",index);//打印输出下标
    }
    free(a);//释放动态分配内存空间
    free(b);//释放动态分配内存空间
    return 0;
}