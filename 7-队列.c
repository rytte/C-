#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}node;


node* front = NULL;			//定义队头指针
node* rear = NULL;			//定义队尾指针


node* queue_init(void);
void queue_enter(int data);
void queue_exit(void);
void queue_show(void);


int main(void)
{
	node* head = queue_init();			//初始化一个头节点
	front = rear = head;				//头指针和尾指针指向头节点

	int data;
	while (1)
	{
		printf("请输入一个整数：");
		scanf_s("%d", &data); while (getchar() != '\n');

		if (data > 0)
			queue_enter(data);
		else if (data < 0)
			queue_exit();
		else
		{
			queue_show();
			continue;
		}

		queue_show();
	}

	return 0;
}

//初始化一个空节点
node* queue_init(void)
{
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL)
	{
		printf("申请堆空间失败！\n");
		return;
	}

	p->data = 0;
	p->next = NULL;
	return p;
}

//进队
void queue_enter(int data)		//队列方向：从头节点指向尾节点，尾节点指向NULL
{
	node* p = queue_init();

	p->data = data;
	p->next = NULL;				//新节点指向NULL
	rear->next = p;				//尾节点指向新节点
	rear = p;					//尾指针指向新节点
}

//出队
void queue_exit(void)
{
	if (front->next == NULL)
	{
		printf("队列为空\n");
		return;
	}

	node* temp = front->next;
	printf("出队：%d\n", temp->data);
	front->next = front->next->next;
	free(temp);
}


void queue_show(void)
{
	if (front->next == NULL)
	{
		printf("队列为空\n");
		return;
	}

	for (node* pos = front->next; pos != NULL; pos = pos->next)
	{
		printf("%d ", pos->data);
	}
	printf("\n");
}


