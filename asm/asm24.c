#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * 完全背包问题解决方案
 * 该实现使用动态规划方法解决超市购物问题
 */

/**
 * 商品信息结构体
 */
typedef struct {
    int value;      // 商品价值
    int volume;     // 商品体积
    double density; // 价值密度（价值/体积）
} GoodsItem;

/**
 * 购物环境结构体
 */
typedef struct {
    int boxCapacity;       // 箱子容量
    int goodsVarieties;    // 商品种类数
    GoodsItem* inventory;  // 商品清单
    int* maxValueCache;    // DP缓存表
} ShoppingContext;

/**
 * 初始化购物环境
 * 
 * @param context 购物环境指针
 * @param capacity 箱子容量
 * @param varieties 商品种类数
 * @return 初始化是否成功
 */
bool setupShoppingContext(ShoppingContext* context, int capacity, int varieties) {
    // 参数校验
    if (capacity <= 0 || varieties <= 0) {
        return false;
    }
    
    // 初始化基本属性
    context->boxCapacity = capacity;
    context->goodsVarieties = varieties;
    
    // 分配商品清单内存
    context->inventory = (GoodsItem*)malloc(varieties * sizeof(GoodsItem));
    if (!context->inventory) {
        return false;
    }
    
    // 分配DP缓存表内存
    context->maxValueCache = (int*)malloc((capacity + 1) * sizeof(int));
    if (!context->maxValueCache) {
        free(context->inventory);
        return false;
    }
    
    // 初始化DP缓存表
    memset(context->maxValueCache, 0, (capacity + 1) * sizeof(int));
    
    return true;
}

/**
 * 清理购物环境资源
 * 
 * @param context 购物环境指针
 */
void cleanupShoppingContext(ShoppingContext* context) {
    if (context->inventory) {
        free(context->inventory);
        context->inventory = NULL;
    }
    
    if (context->maxValueCache) {
        free(context->maxValueCache);
        context->maxValueCache = NULL;
    }
}

/**
 * 加载商品数据
 * 
 * @param context 购物环境指针
 * @return 加载是否成功
 */
bool loadGoodsData(ShoppingContext* context) {
    for (int i = 0; i < context->goodsVarieties; i++) {
        if (scanf("%d %d", &context->inventory[i].value, &context->inventory[i].volume) != 2) {
            return false;
        }
        
        // 计算价值密度
        if (context->inventory[i].volume > 0) {
            context->inventory[i].density = 
                (double)context->inventory[i].value / context->inventory[i].volume;
        } else {
            // 处理异常情况
            context->inventory[i].density = 0;
        }
    }
    return true;
}

/**
 * 使用动态规划算法计算最大价值
 * 
 * @param context 购物环境指针
 * @return 最大价值
 */
int calculateMaximumValue(ShoppingContext* context) {
    // 特殊情况处理
    if (context->boxCapacity == 0 || context->goodsVarieties == 0) {
        return 0;
    }
    
    // 对每种商品进行处理
    for (int i = 0; i < context->goodsVarieties; i++) {
        GoodsItem* currentItem = &context->inventory[i];
        
        // 跳过无效商品
        if (currentItem->volume <= 0 || currentItem->value <= 0) {
            continue;
        }
        
        // 完全背包算法核心：正向遍历容量
        for (int vol = currentItem->volume; vol <= context->boxCapacity; vol++) {
            // 计算选择当前商品后的价值
            int potentialValue = context->maxValueCache[vol - currentItem->volume] + currentItem->value;
            
            // 更新最大价值
            if (potentialValue > context->maxValueCache[vol]) {
                context->maxValueCache[vol] = potentialValue;
            }
        }
    }
    
    return context->maxValueCache[context->boxCapacity];
}

/**
 * 处理单个测试用例
 * 
 * @return 处理是否成功
 */
bool handleTestCase() {
    int capacity, varieties;
    
    // 读取箱子容量和商品种类数
    if (scanf("%d %d", &capacity, &varieties) != 2) {
        return false;
    }
    
    // 初始化购物环境
    ShoppingContext context;
    if (!setupShoppingContext(&context, capacity, varieties)) {
        fprintf(stderr, "环境初始化失败\n");
        return false;
    }
    
    // 加载商品数据
    if (!loadGoodsData(&context)) {
        fprintf(stderr, "商品数据加载失败\n");
        cleanupShoppingContext(&context);
        return false;
    }
    
    // 计算并输出结果
    int result = calculateMaximumValue(&context);
    printf("%d\n", result);
    
    // 清理资源
    cleanupShoppingContext(&context);
    
    return true;
}

/**
 * 程序入口
 */
int main() {
    // 持续处理测试用例，直到输入结束
    while (handleTestCase()) {
        // 继续处理下一个测试用例
    }
    
    return 0;
}
