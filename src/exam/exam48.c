//
// Created by 王智杰 on 2025/6/14.
//
//48.装载问题（回溯、分支限界）**
//
//Description
//有一批概共n个集装箱要装上两艘载重量分别为c1和c2的轮船，其中，集装箱i的重量为wi，且。
//装载问题要求确定是否有一个合理的装载方案可将这n个集装箱装上这两艘轮船。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。每个测试样例的第一行是集装箱个数n（ n ≤ 20 ），第二行是两个整数c1和c2，表示两艘轮船的载重量，
//接下来n行，每行一个整数wi，表示第i个集装箱的重量，（ 0 < wi < 1000，i = 1, 2, …, n， 0 < c1, c2 < 30000 ）
//Output
//对应每个测试样例输出两行，第一行格式为"Case #:"，其中'#'表示第几个测试样例（从1开始计）。
//第二行格式为：如果找不到合理的装载方案，则输出"No"，否则输出最优载重量。
//Sample Input
//2
//3
//50 50
//10 40 40
//3
//50 50
//20 40 40
//
//Sample Output
//Case 1:
//50
//Case 2:
//No


#include<stdio.h>

#define MAX 50
int BoxNum;//集装箱个数
int BoxWeight[MAX];//某个集装箱的重量
int C1;//轮船1的容量
int curC1Wt;//当前轮船1的装载重量
int X[MAX];//集装箱的状态（0表示未装入，1表示装入轮船）
int globalMaxWt;//轮船1的最大装载重量
int restBoxWt;//剩余的集装箱的重量（未装入轮船）

void loadingBackTrack(int t){ //装载回溯算法，t表示集装箱的序号
    if(t == BoxNum){//此时表示已经到最后一个集装箱了，表明所有集装箱已经装入
        globalMaxWt = curC1Wt;//此时轮船1的最大装载重量等于轮船1当前的装载重量
        return;//然后结束
    }
    restBoxWt -= BoxWeight[t]; //剩余集装箱重量减去当前集装箱重量，表示提前准备装入集装箱
    if(C1 >= curC1Wt + BoxWeight[t]){//当轮船1的容量大于轮船1当前装载量+当前集装箱重量
        X[t] = 1;//然后将当前集装箱装入状态改为1，表示已装入
        curC1Wt += BoxWeight[t];//然后将当前轮船装载重量加上当前集装箱的重量
        loadingBackTrack(t+1);//回溯递归下一个集装箱
        curC1Wt -= BoxWeight[t];//回溯，将当前轮船1的重量减去当前集装箱的重量
    }
    if(curC1Wt + restBoxWt > globalMaxWt){//如果当前轮船1装载量+剩余集装箱重量 大于 轮船1的最大装载重量
        X[t] = 0;//将当前集装箱的状态设置为未装入
        loadingBackTrack(t+1);//装载回溯算法递归下一个集装箱
    }
    restBoxWt += BoxWeight[t]; //回溯，将剩余集装箱重量加回当前集装箱的重量
}
int main(){
    int T,C2,totalBoxWt;
    scanf("%d",&T);//输入测试用例个数
    for(int t = 1; t <= T;t++ ){
        scanf("%d",&BoxNum);//输入集装箱个数BoxNum
        scanf("%d%d",&C1,&C2);//输入轮船1、2的容量
        totalBoxWt = 0;//初始化所有集装箱重量为0
        for(int i = 0; i < BoxNum;i++){
            scanf("%d",&BoxWeight[i]);//输入每个集装箱的重量
            totalBoxWt += BoxWeight[i];//
        }
        //初始化全局变量
        restBoxWt = totalBoxWt;//将所有集装箱重量 赋值给 剩余集装箱重量
        curC1Wt = 0;//初始化当前轮船1的装载量为0
        globalMaxWt = 0;//初始化轮船1的最大装载重量为0
        loadingBackTrack(0);//从第0号集装箱开始装载回溯递归
        if(C2 >= totalBoxWt - globalMaxWt){ //船2容量大于剩余集装箱重量（集装箱总重量totalBoxWt - 船1最大装载量globalMaxWt）
            printf("Case %d:\n%d\n",t,globalMaxWt);//打印输出轮船1的最大装载重量
        }else{
            printf("Case %d:\nNo\n",t);//打印输出No
        }
    }
    return 0;
}


























//
//#include<stdio.h>
//
//#define MAX_BOX 25
//int BoxNum;
//int BoxWeight[MAX_BOX];
//int C1;
//int curC1Wt;
//int X[MAX_BOX];
//int globalMaxWt;
//int restBoxWt;
//
//void loadingBacktrack(int t){
//    if(t == BoxNum) {
//        globalMaxWt = curC1Wt;
//        return;
//    }
//    restBoxWt -= BoxWeight[t];
//    if(curC1Wt + BoxWeight[t] <= C1){ //是小于等于C1
//        X[t] = 1;
//        curC1Wt += BoxWeight[t];
//        loadingBacktrack(t + 1);
//        curC1Wt -= BoxWeight[t];
//    }
//    if(curC1Wt + restBoxWt > globalMaxWt ){
//        X[t] = 0;
//        loadingBacktrack(t+1);
//    }
//    restBoxWt += BoxWeight[t];
//
//}
//
//int main(){
//    int T;
//    int C2,totalWt;
//    scanf("%d",&T);
//    for(int t=1; t <= T;t++){
//        scanf("%d",&BoxNum);
//        scanf("%d%d",&C1,&C2);
//        totalWt = 0;
//        for(int i =0; i < BoxNum;i++){
//            scanf("%d",&BoxWeight[i]);
//            totalWt += BoxWeight[i];
//        }
//        //初始化全局变量
//        restBoxWt = totalWt;
//        curC1Wt = 0;
//        globalMaxWt = 0;
//        loadingBacktrack(0);
//        if(C2 >= totalWt - globalMaxWt){
//            printf("Case %d:\n%d\n",t,globalMaxWt);
//        }else{
//            printf("Case %d:\nNo\n",t);
//        }
//    }
//    return 0;
//}
