#include <stdio.h>

#define MAX 10				//定义最大长度
int count = 0;				//定义数组数量，数组末位下标为[count-1]

typedef struct seqnode		//定义数据节点
{
	int data;
}seqnode;


void add(seqnode* seqlist, int data);
void del(seqnode* seqlist, int data);
void show(seqnode* seqlist);
void order_add(seqnode* seqlist, int data);


int main(void)
{
	seqnode seqlist[MAX] = { 0 };		//初始化一个空顺序表

	//增删数据，输入数字大于0则加入表，小于零则删除对应绝对值的数据，等于零则遍历表。
	int data;
	while (1)
	{
		printf("请输入一个整数：");
		scanf_s("%d", &data); while (getchar() != '\n');
		if (data > 0)
			order_add(seqlist, data);
		else if (data < 0)
			del(seqlist, -data);
		else
			show(seqlist);
	}

	return 0;
}


//添加数据
void add(seqnode* seqlist, int data)
{
	//判断表是否已满
	if (count >= MAX)
	{
		printf("顺序表已满！\n");
		return;
	}
	seqlist[count].data = data;
	count++;
	show(seqlist);
}


//删除数据
void del(seqnode* seqlist, int data)
{
	if (count == 0)							//判断是否为空
	{
		printf("顺序表为空！\n");
		return;
	}

	for (int i = 0; i < count; i++)						//遍历查找
	{
		if (seqlist[i].data == data)					//找到则循环覆盖
		{
			for (int n = i; n < count - 1; n++)
			{
				seqlist[n].data = seqlist[n + 1].data;	//覆盖
			}
			seqlist[count - 1].data = 0;					//最后一个数据清零
			count--;
			show(seqlist);
			return;										//处理完后退出函数
		}
	}
	printf("没有找到数据！\n");
}


//遍历顺序表
void show(seqnode* seqlist)
{
	if (count == 0)							//判断是否为空
	{
		printf("顺序表为空！\n");
		return;
	}
		
	for (int i = 0; i < count; i++)			//循环打印
		printf("%d ", seqlist[i].data);

	printf("\n");
}


//有序增加数据（从小到大）
void order_add(seqnode* seqlist, int data)
{
	if (count == MAX)
	{
		printf("顺序表已满！\n");
		return;
	}

	int i;
	for (i = 0; i < count; i++)
	{
		if (data < seqlist[i].data)					//如果新数据更大，则继续向后找。新数据更小则跳出，记住了下标i。
			break;
	}

	for (int n = count; n > i; n--)					//该位置i原数据及后面数据向后移位（覆盖），然后插入该位置
	{
		seqlist[n].data = seqlist[n - 1].data;
	}
	seqlist[i].data = data;
	count++;
	show(seqlist);
}






