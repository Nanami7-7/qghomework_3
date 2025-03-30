#include <stdio.h>
#include <stdlib.h>
/* �ϲ������������������ */
void merge(int* nums, int left, int mid, int right) {
    // ������������Ϊ [left, mid], ������������Ϊ [mid+1, right]
    // ����һ����ʱ���� tmp �����ڴ�źϲ���Ľ��
    int tmpSize = right - left + 1;
    int* tmp = (int*)malloc(tmpSize * sizeof(int));
    // ��ʼ����������������������ʼ����
    int i = left, j = mid + 1, k = 0;
    // �����������鶼����Ԫ��ʱ�����бȽϲ�����С��Ԫ�ظ��Ƶ���ʱ������
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            tmp[k++] = nums[i++];
        }
        else {
            tmp[k++] = nums[j++];
        }
    }
    // ��������������������ʣ��Ԫ�ظ��Ƶ���ʱ������
    while (i <= mid) {
        tmp[k++] = nums[i++];
    }
    while (j <= right) {
        tmp[k++] = nums[j++];
    }
    // ����ʱ���� tmp �е�Ԫ�ظ��ƻ�ԭ���� nums �Ķ�Ӧ����
    for (k = 0; k < tmpSize; ++k) {
        nums[left + k] = tmp[k];
    }
    // �ͷ��ڴ�
    free(tmp);
}

/* �鲢���� */
void mergeSort(int* nums, int left, int right) {
    // ��ֹ����
    if (left >= right)
        return; // �������鳤��Ϊ 1 ʱ��ֹ�ݹ�
    // ���ֽ׶�
    int mid = left + (right - left) / 2;    // �����е�
    mergeSort(nums, left, mid);      // �ݹ���������
    mergeSort(nums, mid + 1, right); // �ݹ���������
    // �ϲ��׶�
    merge(nums, left, mid, right);
}