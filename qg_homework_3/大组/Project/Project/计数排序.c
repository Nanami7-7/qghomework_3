#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n) {
    if (n <= 0) return;

    // 1. 找出数组中的最大值和最小值
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    // 2. 计算数值范围并创建计数数组
    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));//创建计数数组并初始化
    if (!count) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }

    // 3. 统计每个元素的出现次数（偏移处理）
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;       //7 9 5 4 2 7
    }                                //1 0 1 1 0 2 0 1
                                     
    // 4. 计算累加计数（确定元素最终位置）
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];    //1 1 2 3 3 5 5 6 
                                     //count[i] 表示：小于等于 i+min 的元素个数（因为做了偏移处理）
    }                                // count[2]=2,说明有2个元素小于等于4（4-2=2）

    // 5. 创建输出数组并反向填充（保证稳定性）
    int* output = (int*)malloc(n * sizeof(int));
    if (!output) {
        fprintf(stderr, "内存分配失败\n");
        free(count);
        exit(EXIT_FAILURE);
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // 6. 将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // 7. 释放临时内存
    free(count);
    free(output);
}

/*示例用法
int main() {
    int arr[] = { 4, 2, 2, 8, 3, 3, 1, -5, 0 };
    int n = sizeof(arr) / sizeof(arr[0]);

    counting_sort(arr, n);

    printf("排序结果: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    // 输出: -5 0 1 2 2 3 3 4 8

    return 0;
}
*/