#include <stdio.h>

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] >= pivot)
        {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot)
        {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;//��high��low����ʱ����ʱ�����䶼��pivotС�������䶼��pivot��
    return low;//���ػ�׼ֵλ��
}
void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pivotPosition = partition(arr, low, high);
        quickSort(arr, low, pivotPosition - 1);
        quickSort(arr, pivotPosition + 1, high);
    }
}

void printArr(int arr[], int size) 
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

