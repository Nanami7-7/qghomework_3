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
    arr[low] = pivot;//当high和low相遇时，此时左区间都比pivot小，右区间都比pivot大
    return low;//返回基准值位置
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

