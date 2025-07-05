#include <stdio.h>
#include <stdlib.h>

// 定义动态规划数据结构
typedef struct {
    int* lengths;     // 存储各位置LIS长度
    int* prevIndices; // 存储前驱节点索引
} DPContext;

/**
 * 初始化动态规划表
 * @param length 序列长度
 * @return 动态规划上下文
 */
DPContext createDPTables(int length) {
    DPContext ctx;
    ctx.lengths = (int*)malloc(length * sizeof(int));
    ctx.prevIndices = (int*)malloc(length * sizeof(int));

    for (int i = 0; i < length; i++) {
        ctx.lengths[i] = 1;      // 初始长度为1
        ctx.prevIndices[i] = -1; // 初始无前驱
    }

    return ctx;
}

/**
 * 计算最长递增子序列长度
 * @param nums 输入序列
 * @param length 序列长度
 * @param ctx 动态规划上下文
 * @param maxLenIndex 输出参数：最长序列结束位置
 */
void calculateLIS(int* nums, int length, DPContext ctx, int* maxLenIndex) {
    int maxLength = 1;
    *maxLenIndex = 0;

    int i = 0;
    while (++i < length) {
        int j = -1;
        while (++j < i) {
            if (nums[j] < nums[i] && ctx.lengths[j] + 1 > ctx.lengths[i]) {
                ctx.lengths[i] = ctx.lengths[j] + 1;
                ctx.prevIndices[i] = j;
            }
        }

        // 当长度相等时，选择最后一个出现的位置
        if (ctx.lengths[i] > maxLength ||
            (ctx.lengths[i] == maxLength && nums[i] < nums[*maxLenIndex])) {
            maxLength = ctx.lengths[i];
            *maxLenIndex = i;
        }
    }
}

/**
 * 构建最长上升子序列
 * @param ctx 动态规划上下文
 * @param nums 输入序列
 * @param maxLenIndex 最长序列结束位置
 * @param maxLength 最大长度
 * @return 构建好的LIS序列
 */
int* generateLIS(DPContext ctx, int* nums, int maxLenIndex, int maxLength) {
    int* lis = (int*)malloc(maxLength * sizeof(int));
    int current = maxLenIndex;
    int pos = maxLength - 1;

    while (current != -1) {
        lis[pos--] = nums[current];
        current = ctx.prevIndices[current];
    }

    return lis;
}

int main() {
    int n;
    scanf("%d", &n);

    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    // 初始化动态规划表
    DPContext ctx = createDPTables(n);

    // 计算LIS
    int maxIndex;
    calculateLIS(nums, n, ctx, &maxIndex);

    // 获取结果
    int lisLength = ctx.lengths[maxIndex];
    int* lisSequence = generateLIS(ctx, nums, maxIndex, lisLength);

    // 输出结果
    printf("%d\n", lisLength);
    for (int i = 0; i < lisLength; i++) {
        printf("%d ", lisSequence[i]);
    }
    printf("\n");

    // 清理资源
    free(ctx.lengths);
    free(ctx.prevIndices);
    free(lisSequence);
    free(nums);

    return 0;
}
