/********************/数组/************************************************************/
数组（array）：存储多个相同类型的数据，[]
数组是一块连续的内存，存储着具体长度的相同类型的数据，关键点：连续内存，具体长度，相同类型

//数组的初始化



//数组传参
#include <stdio.h>
// int arr[10]; // 函数外部定义的变量，全局变量，作用于所有的函数
// void show_array(int a[10]) //数组原型
// void show_array(int len, int a[]) //柔性数组，没有规定数组的具体长度
// void show_array(int len, int a[len]) //变长数组
void show_array(int len, int* a) // 指针类型，编译器所使用的，
{
	for (int i = 0; i < len; i++)
		printf("arr[%d]: %d\n", i, a[i]);
}

int main()
{
	int arr[10] = { [0 ... 4] = 666,[9] = 123 };
	show_array(10, arr);
	return 0;
}



/********************/变长数组和柔性数组/************************************************************/
#include <stdio.h>

void show_array(int len, int* a) // 指针类型，编译器所使用的，
{
	for (int i = 0; i < len; i++)
		printf("arr[%d]: %d\n", i, a[i]);
}

int main()
{
	// int arr[] = {1,2,3};
	// int arr[] = {}; // 初始化的时候，没有赋值，
	// 初始化和不初始化不一样
	// printf("size: %ld\n", sizeof(arr));

	int len = 1; // int len
	// int arr[len] = {1};// 不能初始化，一旦初始化，数组的长度就是一个定值
	int arr[len];
	arr[0] = 11;
	// arr[1] = 12; // 非法内存操作
	// arr[2] = 13;
	// arr[3] = 14;
	printf("size: %ld\n", sizeof(arr));
	show_array(4, arr);

	return 0;
}



/********************/二维数组/************************************************************/