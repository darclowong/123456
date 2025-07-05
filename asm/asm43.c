#include <stdio.h>
#include <stdlib.h>

/**
 * 降序比较函数
 * @param a: 整型指针
 * @param b: 整型指针
 * @return 比较结果（-1/0/1）
 */
int compare_desc(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    if (x > y) return -1;
    if (x < y) return 1;
    return 0;
}

/**
 * 查找最小负载机器索引
 * @param loads: 机器负载数组
 * @param size: 数组长度
 * @return 最小值索引
 */
int find_min_index(int *loads, int size) {
    if (size == 0) return -1;

    int min_index = 0;
    for (int i = 1; i < size; i++) {
        if (loads[i] < loads[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

/**
 * 处理单个测试用例
 * @param case_num: 测试用例编号
 */
void process_test_case(int case_num) {
    int n, m;
    scanf("%d %d", &n, &m);

    // 动态创建作业时间数组
    int times[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &times[i]);
    }

    // 按处理时间降序排序
    qsort(times, n, sizeof(int), compare_desc);

    // 初始化机器负载
    int machine_loads[m];
    for (int i = 0; i < m; ++i) {
        machine_loads[i] = 0;
    }

    // 分配作业到机器
    for (int i = 0; i < n; ++i) {
        int min_index = find_min_index(machine_loads, m);
        machine_loads[min_index] += times[i];
    }

    // 找出最大完成时间
    int max_time = machine_loads[0];
    for (int i = 1; i < m; ++i) {
        if (machine_loads[i] > max_time) {
            max_time = machine_loads[i];
        }
    }

    // 输出结果
    printf("Case %d: %d\n", case_num, max_time);
}

/**
 * 主程序入口
 */
int main() {
    int test_cases;
    scanf("%d", &test_cases);

    // 逐个处理测试用例
    for (int i = 1; i <= test_cases; ++i) {
        process_test_case(i);
    }

    return 0;
}
