#include <stdio.h>

#define LEN 8


void Bubble_sort(int* arr, int len);
void Insert_sort(int* arr, int len);
void Select_sort(int* arr, int len);
void Shell_sort(int* arr, int len);
void Quick_sort(int* arr, int left, int right);


void show(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int main(void)
{
	int arr[LEN] = { 3, 2, 5, 1, 4 ,8, 7, 6 };
	Quick_sort(arr, 0, 7);

	show(arr, LEN);

	return 0;
}

//冒泡排序：将节点i逐个交换到后面最大位置
void Bubble_sort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int n = 0; n < len - i - 1; n++)
		{
			if (arr[n] > arr[n + 1])
			{
				int temp = arr[n];
				arr[n] = arr[n + 1];
				arr[n + 1] = temp;
			}
		}
	}
}

//插入排序：将节点i插入到前面最小的位置
void Insert_sort(int* arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		int temp = arr[i];			//保存节点i的值
		int n;
		for (n = i; n >= 0; n--)
		{
			if (temp < arr[n - 1])	//比较若更小则交换该位置与前面的值
				arr[n] = arr[n - 1];
			else
				break;
		}
		arr[n] = temp;
	}
}

//选择排序：将节点i与后面最小值交换
void Select_sort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int min = i;				//先保存当前值的下标
		for (int n = i + 1; n < len; n++)
		{
			if (arr[min] > arr[n])	//如果大于后面的数         
				min = n;			//保存最小值的下标
		}
		int temp = arr[i];			//原值与最小值交换
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

//希尔排序：分别以4,2,1的间隔对数据进行比较交换
void Shell_sort(int* arr, int len)
{
	for (int gap = len / 2; gap > 0; gap /= 2)			//比较间距不断缩小为一半
	{
		for (int i = gap; i < len; i++)
		{
			int temp = arr[i];
			int n;
			for (n = i - gap; n >= 0 && arr[n] > temp; n -= gap)
			{
				arr[n + gap] = arr[n];
			}
			arr[n + gap] = temp; 
		}
	}
}

//快速排序：
void Quick_sort(int* arr, int left, int right)	//left:首元素下标，right:尾元素下标
{
	int l = left;
	int r = right;
	int key = arr[l];

	if (left >= right)		//如果左右下标相同则退出
		return;                                  

	while (l < r)
	{
		while (arr[r] > key && l < r)			//若右值大于中点key，则略过，右下标减一
		{
			r--;
		}
		arr[l] = arr[r];                        //左值等于右值                                                                                                               
		while (arr[l] < key && l < r)			//若左值小于中点key，则略过，左下标加一
		{
			l++;
		}
		arr[r] = arr[l];						//右值等于左值
	}
	arr[l] = key;								//左值等于key

	Quick_sort(arr, left, l - 1);
	Quick_sort(arr, l + 1, right);
}


