#include "sort.h"

void BubbleSort(int arr[], int nCount)
{
	for (int i = 0; i < nCount-1; ++i)
	{
		//int line_big = arr[i];
		for (int j = 0; j <nCount - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void QuickSort(int arr[], int low, int high)
{
	if (low >= high)
		return;
	int v_i = low;
	int v_j = high;
	int v_value = arr[low];
	while (v_i < v_j)
	{
		if ((v_i < v_j) && (arr[v_j] > v_value))
		{
			--v_j;
		}
		arr[v_i] = arr[v_j];

		if ((v_i < v_j) && (arr[v_i] < v_value))
		{
			++v_i;
		}
		arr[v_j] = arr[v_i];
	}
	arr[v_i] = v_value;
	QuickSort(arr,low,v_i - 1);
	QuickSort(arr,v_i + 1,high);
}