#include <stdio.h>
#include <stdlib.h>

// ��ȡ�����е����ֵ
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// �����������ڻ��������ÿһλ��
void countingSort1(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };// ��������0-9��

    // ͳ�Ƶ�ǰλ���ֵĳ��ִ���
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
      
    }

    // �����ۻ�������ȷ��Ԫ������������е�λ�ã�
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // �Ӻ���ǰ����ԭ���飬��֤�ȶ���
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // �����������ƻ�ԭ����
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    free(output);
}

// ��������������
void radixSort(int arr[], int n) {
    int max = getMax(arr, n); // ��ȡ���ֵ

    // �Ӹ�λ��ʼ����λ����LSD��
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort1(arr, n, exp);
    }
}
