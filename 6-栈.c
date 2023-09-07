#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}node;


void stack_push(node** top, int data);
void stack_pop(node** top, int* data);
void stack_show(node* top);


int main(void)
{
	node* top = NULL;

	//data大于0则入栈，小于0则出栈，等于0则遍历。
	int data;
	while (1)
	{
		printf("请输入一个整数：");
		scanf_s("%d", &data); while (getchar() != '\n');

		if (data > 0)
			stack_push(&top, data);
		else if (data < 0)
		{
			stack_pop(&top, &data);		//传入data的地址以便可以在释放栈顶节点时传出该栈顶值。
			if (data > 0)
				printf("出栈：%d\n", data);
		}
		else
		{
			stack_show(top);
			continue;
		}
		stack_show(top);
	}

	return 0;
}


//入栈										//传入实参为&top，即传入top指针的地址
void stack_push(node** top, int data)		//形参为**top是二级指针而非两次解引用，形参top是实参top指针的地址，*top，是对top解引用，得到的是实参top指向的地址
{
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL)
	{
		printf("申请堆空间失败！\n");
		return 0;
	}

	p->data = data;
	p->next = *top;			//新节点指向栈顶指针的指向，即新节点指向旧节点。
	*top = p;				//栈顶指针指向新节点
}


//出栈
void stack_pop(node** top, int* data)
{
	if (*top == NULL)
	{
		printf("栈为空！\n");
		return;
	}

	node* temp = *top;				//定义指针temp指向栈顶
	*top = temp->next;				//top指针指向栈顶节点的指向
	*data = temp->data;				//获取栈顶值。因为传入的是地址，因此获取的值直接写入主函数中data实参变量的地址。
	free(temp);						//释放栈顶节点
}


//遍历栈
void stack_show(node* top)
{
	if (top == NULL)
	{
		printf("栈为空！\n");
		return;
	}

	for (node* pos = top; pos != NULL; pos = pos->next)
	{
		printf("%d ", pos->data);
	}
	printf("\n");
}










