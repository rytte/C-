/********************/函数/************************************************************/
//格式
返回值 函数名（形参类型 形参名）
{
	//内容
}

void function(int a, char b)
{
	//content
}


函数声明可以不写形参名
void function(int, char);
void function(int a, char b);


//关键字
return	退出函数，不结束程序



/********************/递归函数/************************************************************/
递归就是一个函数在它的函数体内调用它自身。执行递归函数将反复调用其自身，每调用一次就进入新的一层。递归函数必须有结束条件。


//斐波那契
#include <stdio.h>

int func_fb(int n)
{
	if (n == 2 || n == 1)
		return 1;
	return func_fb(n - 1) + func_fb(n - 2);
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("ret: %d\n", func_fb(n));

	return 0;
}
