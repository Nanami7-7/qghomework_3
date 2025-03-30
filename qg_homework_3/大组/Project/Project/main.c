#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"



// ���ߺ����������������
void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }
}

int main() {
    int mode;
    printf("ѡ�����ģʽ:\n");
    printf("1. ��ͬ�������������\n");
    printf("2. С����������������\n");
    printf("3. ���ɲ������ݵ��ļ�\n");
    printf("4. ��ȡ�ļ�������\n");
    scanf("%d", &mode);

    srand(time(NULL));

    switch (mode) {
    case 1: { // ������������
        int sizes[] = { 10000, 50000, 200000 };
        int max_value = 100000; // �������Χ
        srand(time(NULL));

        for (int i = 0; i < 3; i++) {
            int n = sizes[i];
            int* original = malloc(n * sizeof(int));

            // �����������
            int max_val = 0;
            for (int j = 0; j < n; j++) {
                original[j] = rand() % (max_value + 1);
                if (original[j] > max_val) max_val = original[j];
            }

            printf("\n=== ������: %d ===\n", n);
            printf("%-12s %12s\n", "�㷨", "��ʱ(ms)");
            printf("------------------------\n");

            // ���Բ�������
            int* arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            clock_t start = clock();
            insertSort(arr, n);
            printf("%-12s %12.2f\n", "��������",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // ���Ի�������
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            radixSort(arr, n);
            printf("%-12s %12.2f\n", "��������",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // ���Լ�������
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            countingSort(arr, n);
            printf("%-12s %12.2f\n", "��������",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // ���Կ�������
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            quickSort(arr, 0, n - 1);
            printf("%-12s %12.2f\n", "��������",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            // ���Թ鲢����
            arr = malloc(n * sizeof(int));
            memcpy(arr, original, n * sizeof(int));
            start = clock();
            mergeSort(arr, 0, n - 1);
            printf("%-12s %12.2f\n", "�鲢����",
                (double)(clock() - start) * 1000 / CLOCKS_PER_SEC);
            free(arr);

            free(original);
        }
        break;
    }

    case 2: { // С��������β���
        const int n = 100;
        const int iterations = 100000;
        int** all_data = malloc(iterations * sizeof(int*));

        // Ԥ��������������
        for (int i = 0; i < iterations; i++) {
            all_data[i] = malloc(n * sizeof(int));
            generate_random_array(all_data[i], n);
        }

        printf("\n=== С���������������� ===\n");
        printf("������: %d, �ظ�����: %d\n", n, iterations);
        printf("%-12s %12s\n", "�㷨", "�ܺ�ʱ(ms)");
        printf("------------------------\n");

        // ���Ը��㷨
        clock_t start;
        double total_time;

        // ��������
        start = clock();
        for (int i = 0; i < iterations; i++) {
            insertSort(all_data[i], n);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", total_time);

        // ��������
        start = clock();
        for (int i = 0; i < iterations; i++) {
            radixSort(all_data[i], n);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", total_time);

        // ��������
        start = clock();
        for (int i = 0; i < iterations; i++) {
            countingSort(all_data[i], n);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", total_time);

        // ��������
        start = clock();
        for (int i = 0; i < iterations; i++) {
            quickSort(all_data[i], 0, n - 1);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", total_time);

        // �鲢����
        start = clock();
        for (int i = 0; i < iterations; i++) {
            mergeSort(all_data[i], 0, n - 1);
        }
        total_time = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "�鲢����", total_time);

        // �ͷ��ڴ�
        for (int i = 0; i < iterations; i++) {
            free(all_data[i]);
        }
        free(all_data);
        break;
    }

    case 3: { // �������ݵ��ļ�
        const char* filename = "test_data.txt";
        const int total_numbers = 100000;
        FILE* file = fopen(filename, "w");

        printf("\n���� %d ��������� %s...\n", total_numbers, filename);
        for (int i = 0; i < total_numbers; i++) {
            fprintf(file, "%d\n", rand() % 100000);
        }
        fclose(file);
        printf("����������ɡ�\n");
        break;
    }

    case 4: { // ��ȡ�ļ�������
        const char* filename = "test_data.txt";
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("�޷����ļ���\n");
            break;
        }

        int* original = NULL;
        int capacity = 1000;
        int size = 0;
        original = malloc(capacity * sizeof(int));
        if (original == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            fclose(file);
            break;
        }

        int num;
        while (fscanf(file, "%d", &num) == 1) {
            if (size >= capacity) {
                capacity *= 2;
                int* new_ptr = realloc(original, capacity * sizeof(int));
                if (new_ptr == NULL) {
                    printf("�ڴ���չʧ�ܣ�\n");
                    free(original);
                    fclose(file);
                    exit(1);
                }
                original = new_ptr;
            }
            original[size++] = num;
        }
        fclose(file);

        printf("\n=== �ļ������������ ===\n");
        printf("������: %d\n", size);
        printf("%-12s %12s\n", "�㷨", "��ʱ(ms)");
        printf("------------------------\n");

        // ���Ը��㷨��������
        int* temp;
        clock_t start;
        double time_taken;
        FILE* result_file;

        // ��������
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        insertSort(temp, size);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", time_taken);

        // ������
        result_file = fopen("insert_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("���棺�޷����������������ļ���\n");
        }
        free(temp);

        // ��������
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        radixSort(temp, size);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", time_taken);

        // ������
        result_file = fopen("radix_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("���棺�޷����������������ļ���\n");
        }
        free(temp);

        // ��������
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        countingSort(temp, size);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", time_taken);

        // ������
        result_file = fopen("counting_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("���棺�޷����������������ļ���\n");
        }
        free(temp);

        // ��������
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        quickSort(temp, 0, size - 1);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "��������", time_taken);

        // ������
        result_file = fopen("quick_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("���棺�޷����������������ļ���\n");
        }
        free(temp);

        // �鲢����
        temp = malloc(size * sizeof(int));
        memcpy(temp, original, size * sizeof(int));
        start = clock();
        mergeSort(temp, 0, size - 1);
        time_taken = (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
        printf("%-12s %12.2f\n", "�鲢����", time_taken);

        // ������
        result_file = fopen("merge_sorted.txt", "w");
        if (result_file) {
            for (int i = 0; i < size; i++) {
                fprintf(result_file, "%d\n", temp[i]);
            }
            fclose(result_file);
        }
        else {
            printf("���棺�޷������鲢�������ļ���\n");
        }
        free(temp);

        free(original);
        printf("\n�������ѱ��浽��Ӧ�㷨���Ƶ�_sorted.txt�ļ���\n");
        break;
    }
    
    default:
        printf("��Чģʽѡ��\n");
    }
    return 0;
}

