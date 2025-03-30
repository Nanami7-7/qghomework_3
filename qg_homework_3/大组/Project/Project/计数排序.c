#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n) {
    if (n <= 0) return;

    // 1. �ҳ������е����ֵ����Сֵ
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    // 2. ������ֵ��Χ��������������
    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));//�����������鲢��ʼ��
    if (!count) {
        fprintf(stderr, "�ڴ����ʧ��\n");
        exit(EXIT_FAILURE);
    }

    // 3. ͳ��ÿ��Ԫ�صĳ��ִ�����ƫ�ƴ���
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;       //7 9 5 4 2 7
    }                                //1 0 1 1 0 2 0 1
                                     
    // 4. �����ۼӼ�����ȷ��Ԫ������λ�ã�
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];    //1 1 2 3 3 5 5 6 
                                     //count[i] ��ʾ��С�ڵ��� i+min ��Ԫ�ظ�������Ϊ����ƫ�ƴ���
    }                                // count[2]=2,˵����2��Ԫ��С�ڵ���4��4-2=2��

    // 5. ����������鲢������䣨��֤�ȶ��ԣ�
    int* output = (int*)malloc(n * sizeof(int));
    if (!output) {
        fprintf(stderr, "�ڴ����ʧ��\n");
        free(count);
        exit(EXIT_FAILURE);
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // 6. �����������ƻ�ԭ����
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // 7. �ͷ���ʱ�ڴ�
    free(count);
    free(output);
}

/*ʾ���÷�
int main() {
    int arr[] = { 4, 2, 2, 8, 3, 3, 1, -5, 0 };
    int n = sizeof(arr) / sizeof(arr[0]);

    counting_sort(arr, n);

    printf("������: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    // ���: -5 0 1 2 2 3 3 4 8

    return 0;
}
*/