//
// Created by 王智杰 on 2025/6/14.
//
//14.装载问题（回溯、分支限界）**
//
//Description
//有一批概共n个集装箱要装上两艘载重量分别为c1和c2的轮船，其中，集装箱i的重量为wi，且        。
//装载问题要求确定是否有一个合理的装载方案可将这n个集装箱装上这两艘轮船。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是集装箱个数n（ n ≤ 20 ），第二行是两个整数c1和c2，表示两艘轮船的载重量，
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
#define MaxBox 1000 //集装箱最多数量
int BoxWeight[MaxBox]; //某个集装箱的重量
int BoxNum; //集装箱的数量
int C1; //船1的容量
int X[MaxBox];//集装箱的状态（0,1）0表示未装入，1表示装入船
int curC1Wt;//当前装入船1的重量
int restBoxWt; //表示当前剩余的集装箱总重量
int globalMaxWt;//表示在所有可能方案中，第一艘船能承载的最大重量。

void loadingBacktrack(int t){ //参数 t 表示当前处理的集装箱序号
    if(t == BoxNum){ //说明已经处理完所有集装箱，此时更新最大装载量 globalMaxWt 为当前装载量 curC1Wt。
        //同时也是一个边界条件，得到一个船1的更好可行解
        globalMaxWt = curC1Wt;
        return;
    }
    restBoxWt -= BoxWeight[t];//剩余的集装箱重量减去集装箱t的重量(扩展子节点时减少 restBoxWt 的值，表示正在尝试将第 t 个集装箱纳入考虑范围)
    if(curC1Wt + BoxWeight[t] <= C1){//判断当前装载量加上第 t 个集装箱的重量是否超过船的容量，如果不超过，则尝试将其装入船，约束剪枝
        X[t] =1;//表示第 t 个集装箱被装入第一艘船。
        curC1Wt += BoxWeight[t];//更新当前装载量 curC1Wt，增加第 t 个集装箱的重量
        loadingBacktrack(t + 1);//递归调用 loadingBacktrack，处理下一个集装箱
        curC1Wt -= BoxWeight[t]; //回溯时恢复当前装载量 curC1Wt，因为该路径尝试失败或已完成(本路径已经尝试过，所以回溯)
    }
    if(curC1Wt + restBoxWt > globalMaxWt){ //界限剪枝,判断当前装载量加上剩余所有集装箱的重量是否大于目前的最优解 globalMaxWt。
        //如果这个条件成立，说明还有可能找到比当前最优解更好的解，因此继续递归探索；否则，直接剪枝，不再继续探索该分支。
        X[t] = 0;//表示第 t 个集装箱未被装入第一艘船。省了这一步curC1Wt -= BoxWeight[t]
        loadingBacktrack(t + 1);//递归调用 loadingBacktrack，处理下一个集装箱
    }
    restBoxWt += BoxWeight[t]; //回溯时恢复剩余集装箱重量 restBoxWt，因为该路径尝试失败或已完成
}

int main(){
    int T;//测试用例个数
    int C2;//船2容量
    int totalBoxWt;//所有集装箱的总重量
    scanf("%d",&T);
    for(int t = 1; t <= T;t++) {
         scanf("%d", &BoxNum);
         scanf("%d%d", &C1, &C2);
            totalBoxWt = 0;//初始化 totalBoxWt 为 0，用于计算所有集装箱的总重量
            for (int i = 0; i < BoxNum; i++) { //使用 for 循环读取每个集装箱的重量，并累加到 totalBoxWt 中
                scanf("%d", &BoxWeight[i]);
                totalBoxWt += BoxWeight[i];
            }
            restBoxWt = totalBoxWt;//初始化 restBoxWt 为 totalBoxWt，表示尚未考虑的集装箱总重量
            curC1Wt = 0;//当前装入船1的重量赋值为0
            globalMaxWt = 0;//装入船1的最优装载量赋值为0
            loadingBacktrack(0);//调用 loadingBacktrack 函数，从第一个集装箱开始尝试装载（从零开始）
            //判断第二艘船能否容纳剩下的集装箱。如果可以，输出第一艘船的最大装载量；否则输出 "No"。（关键判断）
            if (C2 >= totalBoxWt - globalMaxWt) //当C2容量大于剩余集装箱的重量，集装箱可以装入C2
                printf("Case %d:\n%d\n",t, globalMaxWt); //此时说明船1最大装载量有效
            else
                printf("Case %d:\nNo\n",t);//否则说明船1最大装载量无效
        }
    return 0;
}


//疑惑点分析： if(curC1Wt + restBoxWt > globalMaxWt){
//假设当前已经装了 curC1Wt = 500 的重量。
//剩下的未处理集装箱总重量为 restBoxWt = 300。
//当前找到的最优解是 globalMaxWt = 700。
//此时：
//curC1Wt + restBoxWt = 500 + 300 = 800 > globalMaxWt = 700
//说明当前路径理论上还能装出一个更好的解（最多可达 800），因此值得继续探索。
//但如果：
//curC1Wt + restBoxWt = 500 + 100 = 600 < globalMaxWt = 700
//说明即使把剩下的所有集装箱都装进第一艘船，也无法超过当前最优解。那这条路径就不可能产生更好的结果，应该剪掉，节省时间。
//类比理解：
//想象你在爬山，想找最高的山顶。你站在当前位置（curC1Wt），知道前方还有若干山头（restBoxWt）。
//如果你估算从当前位置最多只能爬到 curC1Wt + restBoxWt 的高度，而你之前已经到达过更高的地方（globalMaxWt），
//那你就可以判断：这条路走不通，没必要浪费体力了。
//这行代码的核心思想是：
//在递归过程中，如果当前路径理论上都无法超越已有最优解，那就没有必要继续探索下去了，直接剪枝。
//通过这种方式，我们可以高效地缩小搜索范围，快速找到最优解。
//这两个 if 条件共同完成了对“装入”和“不装入”两种情况的探索，构成了完整的回溯逻辑。
//为什么在这个判断后不是将 X[t] = 1;？
//因为：
//X[t] = 1 的操作已经在前面的 if (curC1Wt + BoxWeight[t] <= C1) 中执行过了；
//这个 if(curC1Wt + restBoxWt > globalMaxWt) 是为了判断是否继续探索“不装入当前集装箱”的情况；
//所以在这里，我们设置 X[t] = 0 表示不装入当前集装箱，然后继续递归探索后续集装箱的组合。










//#include <stdio.h>
//#include <stdlib.h>
//
//// 全局变量定义
//int n, c1, c2, total_weight;
//int weights[20];         // 存储集装箱重量
//int best_load;           // 记录第一艘船的最优载重量
//int found;               // 标记是否找到可行解
//
//// 比较函数：从大到小排序
//int compare(const void *a, const void *b) {
//    return *(int *)b - *(int *)a;
//}
//// 深度优先搜索函数
//void dfs(int index, int current_load) {
//    // 剪枝：当前装载已超过c1，直接返回
//    if (current_load > c1) {
//        return;
//    }
//    // 剪枝：即使剩余集装箱全装上也无法超过当前最优解
//    if (found && current_load + total_weight <= best_load) {
//        return;
//    }
//    // 所有集装箱处理完毕
//    if (index == n) {
//        // 检查第二艘船是否满足条件
//        if (total_weight - current_load <= c2) {
//            // 更新最优解
//            if (current_load > best_load) {
//                best_load = current_load;
//            }
//            found = 1; // 标记已找到可行解
//        }
//        return;
//    }
//    // 剩余重量减少（用于后续剪枝）
//    total_weight -= weights[index];
//
//    // 选择1：将当前集装箱装入第一艘船
//    dfs(index + 1, current_load + weights[index]);
//
//    // 选择2：不将当前集装箱装入第一艘船
//    dfs(index + 1, current_load);
//
//    // 回溯：恢复剩余重量
//    total_weight += weights[index];
//}
//
//int main() {
//    int T;
//    scanf("%d", &T); // 测试用例数量
//
//    for (int t = 1; t <= T; t++) {
//        scanf("%d", &n); // 集装箱数量
//        scanf("%d %d", &c1, &c2); // 两艘船的载重量
//
//        total_weight = 0;
//        for (int i = 0; i < n; i++) {
//            scanf("%d", &weights[i]);
//            total_weight += weights[i]; // 计算总重量
//        }
//        // 检查总重量是否超过两船容量之和
//        if (total_weight > c1 + c2) {
//            printf("Case %d:\n", t);
//            printf("No\n");
//            continue;
//        }
//        // 初始化
//        best_load = 0;
//        found = 0;
//
//        // 优化：按重量从大到小排序
//        qsort(weights, n, sizeof(int), compare);
//
//        // 执行深度优先搜索
//        dfs(0, 0);
//
//        // 输出结果
//        printf("Case %d:\n", t);
//        if (found) {
//            printf("%d\n", best_load);
//        } else {
//            printf("No\n");
//        }
//    }
//    return 0;
//}



