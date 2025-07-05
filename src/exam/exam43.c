//
// Created by 王智杰 on 2025/6/14.
//
//43.多机调度问题（贪心算法）
//
//Description
//设有n个独立的作业{1，2，…，n}，由m台相同的机器进行加工处理。作业i所需的处理时间为ti。
//现约定，每个作业均可在任何一台机器上加工处理，但未完工前不允许中断处理。作业不能拆分成更小的子作业。
//现要求给出一种作业调度方案，使所给的n个作业在尽可能短的时间内由m台机器加工处理完成。
//Input
//输入的第一个为测试样例的个数T，接下来有T个测试样例。
//每个测试样例的第一行是两个整数n和m（ n < 1000, m < 1000 ），接下来有n行，每行一个整数表示第i个作业所需的处理时间
//Output
//对应每个测试样例输出一行，格式为"Case #: t"，其中'#'表示第几个测试样例（从1开始计），t表示加工完所有任务所需的最短时间。
//Sample Input
//1
//7 3
//2
//14
//4
//16
//6
//5
//3
//
//Sample Output
//Case 1: 17

//#include<stdio.h>
//#include<stdlib.h>
//
//int compare(const void *a,const void *b){
//    return (*(int *)b - *(int *)a);
//}
//
//int main(){
//    int T;
//    scanf("%d",&T);
//    for(int t = 1; t <= T;t++){
//        int n,m;
//        scanf("%d %d",&n,&m);
//        int *jobs = (int *)malloc(n * sizeof(int));
//        for(int i = 0; i < n; i++){
//            scanf("%d",&jobs[i]);
//        }
//
//        if(n <= m ){
//            int max_time = 0;
//            for(int i = 0; i < n;i++){
//                if(jobs[i] > max_time){
//                    max_time = jobs[i];
//                }
//            }
//            printf("Case %d: %d\n",t,max_time);
//            free(jobs);
//            continue;
//        }
//
//        qsort(jobs,n,sizeof(int),compare);
//
//        //*************这里使用的是calloc分配内存空间，不是malloc
//        int *machines = (int *)calloc(m , sizeof(int));
//
//            for(int i = 0; i < n; i++){
//                int min_machine = 0;
//                for(int j = 1; j < m;j++){ //遍历找出当前负载最小的机器，然后交给当前作业
//                    if(machines[min_machine] > machines[j]){
//                           min_machine = j;
//                    }
//                }
//                machines[min_machine] += jobs[i]; //是+=，叠加作业时长给机器，不是简单的赋值
//            }
//
//            //遍历找出最大装载的机器并输出
//            int max_load = 0;
//            for(int i = 0; i < m; i++){
//                if(max_load < machines[i]){
//                    max_load = machines[i];
//                }
//            }
//            printf("Case %d: %d",t,max_load);
//            free(jobs);
//            free(machines);
//        }
//    return 0;
//    }

//
//疑惑点解析
//在 C 语言中，`calloc` 和 `malloc` 都是动态内存分配函数，但它们在以下关键方面有所不同，这使得在此场景中使用 `calloc` 更合适：
//
//### 主要区别：
//| 特性         | `calloc`                     | `malloc`                  |
//|--------------|------------------------------|---------------------------|
//| **初始化**   | 自动初始化为全零             | 不初始化（内容随机）       |
//| **参数**     | 两个参数：元素数量和元素大小 | 一个参数：总字节大小       |
//| **内部实现** | 可能更高效（批量清零）       | 简单分配                  |

//### 为什么在多机调度中使用 `calloc`：
//```c
//int *machines = (int *)calloc(m, sizeof(int));
//```
//
//1. **自动零初始化**：
//- 机器负载数组需要初始化为全零（所有机器初始空闲）
//- `calloc` 保证分配的内存块被置为全零位模式（相当于整数0）
//- 等同于手动初始化：`for(i=0; i<m; i++) machines[i] = 0;`
//
//2. **代码简洁性**：
//- 一行代码完成分配和初始化
//- 避免额外的初始化循环，减少代码量和潜在错误
//
//3. **安全性**：
//- 防止未初始化内存导致的随机值
//- 在负载计算时保证从0开始累加
//
//### 如果使用 `malloc` 会怎样：
//```c
//// 需要额外初始化步骤
//int *machines = (int *)malloc(m * sizeof(int));
//// 内容随机，可能是垃圾值
//for(int i=0; i<m; i++) machines[i] = 0; // 必须手动初始化
//```
//
//### 性能考虑：
//- **小规模数据**（m < 1000）：`calloc` 和 `malloc+循环` 性能差异可忽略
//- **大规模数据**：`calloc` 可能更高效，因为：
//- 某些系统实现中，操作系统可直接提供预清零的页
//- 使用专门的批量清零指令（如 x86 的 `rep stos`）
//
//### 在具体场景中的重要性：
//多机调度算法中：
//```c
//// 找到当前负载最小的机器
//int min_machine = 0;
//for (int j = 1; j < m; j++) {
//if (machines[j] < machines[min_machine]) { // 依赖正确初始化
//min_machine = j;
//}
//}
//```
//- 若使用 `malloc` 未初始化：
//- 随机值可能远大于实际负载
//- 导致 `min_machine` 选择错误
//- 最终结果错误
//
//### 结论：
//使用 `calloc` 是为了：
//1. **确保正确性**：机器负载从0开始累加
//2. **代码简洁**：避免额外的初始化循环
//3. **安全可靠**：防止未初始化内存导致的未定义行为
//这是良好的编程实践，特别适合需要初始化为零的数值数组场景。在多机调度问题中，这种选择保证了算法的正确性和可靠性。





#include<stdio.h>
#include<stdlib.h>

int compare(const void *a, const void *b){ //比较函数，从大到小进行排序
    return (*(int *)b - *(int *)a);
}

int main(){
    int T;
    scanf("%d",&T);//输入测试用例个数
    for(int t = 1; t <= T;t++){  //测试用例记得加等号！！！
        int n,m;
        scanf("%d %d",&n,&m);//输入作业个数n和机器个数m
        int *jobs = (int *)malloc(n * sizeof(int));//动态分配作业数组jobs
        for(int i = 0; i < n; i++){
            scanf("%d",&jobs[i]);//输入作业加工时间
        }

        if(n <= m){//如果作业个数小于等于机器个数，此时最短加工时间即加工时间最长的作业
            int max_time = 0;//定义最大加工时间
            for(int i = 0; i < n; i++){//获取加工时间最长的作业
                if(max_time < jobs[i]){
                    max_time = jobs[i];//将最长加工时间的作业赋值给max_time
                }
            }
            printf("Case %d: %d",t,max_time);//打印输出结果
            free(jobs);//释放动态分配的内存空间
            continue;//进入下一个测试用例
        }
        //使用内置排序函数qsort将jobs数组整体从大到小排序
        qsort(jobs,n,sizeof(int),compare);
    int *machines = (int *)calloc(m,sizeof(int)); //使用calloc动态分配机器负载数组，自带初始化为0

        for(int i = 0; i < n; i++){ //从零开始遍历 作业
            int min_machine = 0;//定义最小负载的机器变量（数组下标）
            for(int j = 1; j < m ;j++){ //遍历找出最小负载的机器
                if(machines[j] < machines[min_machine]){
                    min_machine = j;//将数组下标赋值给最小负载机器变量
                }  //遍历找出最小负载机器
            }
            machines[min_machine] += jobs[i];//添加当前作业 到 最小负载机器
        }

        int max_load = 0;//定义机器最大负载量
        for(int i = 0; i < m; i++) {  //遍历找出最大负载的机器并打印输出
            if (max_load < machines[i]) {
                max_load = machines[i]; //如果机器负载大于max_load，将机器负载赋值给max_load
            }
        }
            printf("Case %d: %d\n",t,max_load);//打印输出当前测试用例的最大负载，即为加工完所有作业的最短时间
            free(jobs);//释放动态分配的内存空间
            free(machines);//释放动态分配的内存空间
        }
    return 0;
}




















//#include <stdio.h>
//#include <stdlib.h>
//
//// 比较函数：从大到小排序
//int compare(const void *a, const void *b) {
//    return *(int *)b - *(int *)a;
//}
//
//int main() {
//    int T;
//    scanf("%d", &T); // 测试样例个数
//
//    for (int t = 1; t <= T; t++) {
//        int n, m;
//        scanf("%d %d", &n, &m); // 作业数和机器数
//
//        int *jobs = (int *)malloc(n * sizeof(int)); // 作业处理时间数组
//        for (int i = 0; i < n; i++) {
//            scanf("%d", &jobs[i]); // 读取每个作业的处理时间
//        }
//
//        // 如果作业数不超过机器数，则最长处理时间即为结果
//        if (n <= m) {
//            int max_time = 0;
//            for (int i = 0; i < n; i++) {  //遍历查找jobs数组中的最大值
//                if (jobs[i] > max_time) {
//                    max_time = jobs[i];
//                }
//            }
//            printf("Case %d: %d\n", t, max_time);//打印输出最大花费时间
//            free(jobs);  //释放分配内存空间
//            continue; //跳过当前循环进入下一个测试用例
//        }
//
//        // 将作业按处理时间从大到小排序（贪心关键）
//        qsort(jobs, n, sizeof(int), compare);
//
//        // 初始化机器负载数组
//        int *machines = (int *)malloc(m, sizeof(int));
//
//        // 贪心分配作业
//        for (int i = 0; i < n; i++) {
//            // 找到当前负载最小的机器
//            int min_machine = 0;
//            for (int j = 1; j < m; j++) {  //遍历查找machines数组中的最小值
//                if (machines[j] < machines[min_machine]) {
//                    min_machine = j;
//                }
//            }
//            // 将当前作业分配给负载最小的机器,从局部最优推出全局最优
//            machines[min_machine] += jobs[i];
//        }
//
//        // 找到最大负载（即总处理时间）,因为有些机器可能需要处理两个或更多作业，而不仅仅是一个作业，所以遍历找出machines数组中的最大值然后输出
//        int max_load = 0;
//        for (int i = 0; i < m; i++) {
//            if (machines[i] > max_load) {
//                max_load = machines[i];
//            }
//        }
//
//        // 输出结果
//        printf("Case %d: %d\n", t, max_load);
//
//        // 释放内存
//        free(jobs);
//        free(machines);
//    }
//    return 0;
//}