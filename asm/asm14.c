#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * 计算集装箱总重量
 * @param weights 集装箱重量数组
 * @param n 集装箱数量
 * @return 总重量
 */
long long calculateTotalWeight(int weights[], int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += weights[i];
    }
    return total;
}

/**
 * 检查是否存在有效装载方案
 * @param weights 集装箱重量数组
 * @param n 集装箱数量
 * @param c1 第一艘船容量
 * @param c2 第二艘船容量
 * @return 最大装载重量或-1表示无解
 */
long long checkLoadingSolution(int weights[], int n, int c1, int c2) {
    long long total = calculateTotalWeight(weights, n);

    // 总重量超过两船总容量
    if (total > (long long)c1 + c2) {
        return -1;
    }

    // 计算目标范围
    int minRequired = total > c2 ? total - c2 : 0;
    int maxPossible = total < c1 ? total : c1;

    // 特殊情况：第一艘船容量为0
    if (c1 == 0) return total;

    // 动态规划数组
    bool canReach[c1 + 1];
    memset(canReach, 0, sizeof(canReach));
    canReach[0] = true;

    // 填充动态规划数组
    for (int i = 0; i < n; i++) {
        int weight = weights[i];
        for (int j = c1; j >= weight; j--) {
            if (canReach[j - weight]) {
                canReach[j] = true;
            }
        }
    }

    // 寻找符合条件的最大装载量
    for (int i = maxPossible; i >= minRequired; i--) {
        if (canReach[i]) {
            return i;
        }
    }

    return -1; // 无解
}

int main() {
    int T;
    scanf("%d", &T);

    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int n;
        scanf("%d", &n);

        int c1, c2;
        scanf("%d %d", &c1, &c2);

        int weights[20];
        for (int i = 0; i < n; i++) {
            scanf("%d", &weights[i]);
        }

        long long result = checkLoadingSolution(weights, n, c1, c2);

        printf("Case %d:\n", caseNum);
        if (result == -1) {
            printf("No\n");
        } else {
            printf("%lld\n", result);
        }
    }

    return 0;
}
