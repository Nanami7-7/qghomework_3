void insertSort(int arr[], int n)
{
	int i, j, temp;                      //10 7 8 9 1 5
	for (i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])//如果该数比前一个数小
		{
			temp = arr[i];//临时变量记录该数
			for (j = i - 1; j >= 0 && arr[j] > temp; j--)//与前面有序区最后一个数依次对比，只要前面的数还比temp大
			{
				arr[j + 1] = arr[j];//依次向前移动
			}
			arr[j + 1] = temp;//当要排序的值比较到了比他小的数，该数不往前移动，将该值排序到该数前；或者第一个数也没有该值小
		}
	}
}