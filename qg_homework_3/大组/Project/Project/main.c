#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"



// 工具函数：生成随机数组
void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }
}

int main() {
    int mode;
    printf("选择测试模式:\n");
    printf("1. 不同数据量排序测试\n");
    printf("2. 小数据量多次排序测试\n");
    printf("3. 生成测试数据到文件\n");
    printf("4. 读取文件并排序\n");
    scanf("%d", &mode);

    srand(time(NULL));

    switch (mode) {
    case 1: { // 大数据量测试
        int sizes[] = { 10000, 50000, 200000 };
        int max_value = 100000; // 随机数范围
        srand(time(NULL));

        for (int i = 0; i < 3; i++) {
            int n = sizes[i];
            int* original = malloc(n * sizeof(int));

            // 生成随机数据
            int max_val = 0;
            for (int j = 0; j < n; j++) {
                original[j] = rand() % (max_value + 1);
                if (original[j] > max_val) max_val = original[j];
            }

            printf("\n=== 数据量: %d ===\n", n);
            printf("%-12s %12s\n", "算法", "耗时(ms)");
            printf("------------------------\n");

            // 测试插入排序
            int* arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            clock_t start = clock();
            insertSort(arr, n);
            printf("%-12s %12.2f\n", "插入排序",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // 测试基数排序
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            radixSort(arr, n);
            printf("%-12s %12.2f\n", "基数排序",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // 测试计数排序
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            countingSort(arr, n);
            printf("%-12s %12.2f\n", "计数排序",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // 测试快速排序
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            quickSort(arr, 0, n - 1);
            printf("%-12s %12.2f\n", "快速排序",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // 测试归并排序
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            mergeSort(arr, 0, n - 1);
            printf("%-12s %12.2f\n", "归并排序",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            free(original);
        }
        break;
    }

    case 2: { // 小数据量多次测试
        const int n = 100;
        const int iterations = 100000;
        int** all_data = malloc(iterations * sizeof(int*));

        // 预先生成所有数据
        for (int i = 0; i < iterations; i++) {
            all_data[i] = malloc(n * sizeof(int));
            generate_random_array(all_data[i], n);
        }

        printf("\n=== 小数据量多次排序测试 ===\n");
        printf("数据量: %d, 重复次数: %d\n", n, iterations);
        printf("%-12s %12s\n", "算法", "总耗时(ms)");
        printf("------------------------\n");

        // 测试各算法
        clock_t start;
        double total_time;

        // 插入排序
        start = clock();
        for (int i = 0; i < iterations; i++) {
            insertSort(all_data[i], n);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "插入排序", total_time);

        // 基数排序
        start = clock();
        for (int i = 0; i < iterations; i++) {
            radixSort(all_data[i], n);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "基数排序", total_time);

        // 计数排序
        start = clock();
        for (int i = 0; i < iterations; i++) {
            countingSort(all_data[i], n);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "计数排序", total_time);

        // 快速排序
        start = clock();
        for (int i = 0; i < iterations; i++) {
            quickSort(all_data[i], 0, n - 1);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "快速排序", total_time);

        // 归并排序
        start = clock();
        for (int i = 0; i < iterations; i++) {
            mergeSort(all_data[i], 0, n - 1);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "归并排序", total_time);

        // 释放内存
        for (int i = 0; i < iterations; i++) {
            free(all_data[i]);
        }
        free(all_data);
        break;
    }

    case 3: { // 生成数据到文件
        const char* filename = "test_data.txt";
        const int total_numbers = 100000;
        FILE* file = fopen(filename, "w");

        printf("\n生成 %d 个随机数到 %s...\n", total_numbers, filename);
        for (int i = 0; i < total_numbers; i++) {
            fprintf(file, "%d\n", rand() % 100000);
        }
        fclose(file);
        printf("数据生成完成。\n");
        break;
    }

    case 4: { // 读取文件并排序
        const char* filename = "test_data.txt";
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("无法打开文件！\n");
            break;
        }

        int* original = NULL;
        int capacity = 1000;
        int size = 0;
        original = malloc(capacity * sizeof(int));
        if (original == NULL) {
            printf("内存分配失败！\n");
            fclose(file);
            break;
        }

        int num;
        while (fscanf(file, "%d", &num) == 1) {
            if (size >= capacity) {
                capacity *= 2;
                int* new_ptr = realloc(original, capacity * sizeof(int));
                if (new_ptr == NULL) {
                    printf("内存扩展失败！\n");
                    free(original);
                    fclose(file);
                    exit(1);
                }
                original = new_ptr;
            }
            original[size++] = num;
        }
        fclose(file);

        printf("\n=== 文件数据排序测试 ===\n");
        printf("数据量: %d\n", size);
        printf("%-12s %12s\n", "算法", "耗时(ms)");
        printf("------------------------\n");

        // 测试各算法并保存结果
        int* temp;
        clock_t start;
        double time_taken;
        FILE* result_file;

        // 插入排序
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        insertSort(temp, size);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "插入排序", time_taken);

        // 保存结果
        result_file = fopen("insert_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("警告：无法创建插入排序结果文件！\n");
        }
        free(temp);

        // 基数排序
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        radixSort(temp, size);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "基数排序", time_taken);

        // 保存结果
        result_file = fopen("radix_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("警告：无法创建基数排序结果文件！\n");
        }
        free(temp);

        // 计数排序
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        countingSort(temp, size);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "计数排序", time_taken);

        // 保存结果
        result_file = fopen("counting_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("警告：无法创建计数排序结果文件！\n");
        }
        free(temp);

        // 快速排序
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        quickSort(temp, 0, size - 1);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "快速排序", time_taken);

        // 保存结果
        result_file = fopen("quick_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("警告：无法创建快速排序结果文件！\n");
        }
        free(temp);

        // 归并排序
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        mergeSort(temp, 0, size - 1);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "归并排序", time_taken);

        // 保存结果
        result_file = fopen("merge_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("警告：无法创建归并排序结果文件！\n");
        }
        free(temp);

        free(original);
        printf("\n排序结果已保存到对应算法名称的_sorted.txt文件中\n");
        break;
    }
    
    default:
        printf("无效模式选择\n");
    }
    return 0;
}

