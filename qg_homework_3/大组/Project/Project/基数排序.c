#include <stdio.h>
#include <stdlib.h>

// 获取数组中的最大值
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 计数排序（用于基数排序的每一位）
void countingSort1(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };// 计数器（0-9）

    // 统计当前位数字的出现次数
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
      
    }

    // 计算累积次数（确定元素在输出数组中的位置）
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 从后往前遍历原数组，保证稳定性
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    free(output);
}

// 基数排序主函数
void radixSort(int arr[], int n) {
    int max = getMax(arr, n); // 获取最大值

    // 从个位开始，逐位排序（LSD）
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort1(arr, n, exp);
    }
}
