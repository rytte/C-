#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}node;


node* Init(void);
void add_head(node* head, int data);
void add_tail(node* head, int data);
void del(node* head, int data);
void show(node* head);


int main(void)
{
	node* head = Init();				//初始化一个头结点

	//增删数据，输入数字大于0则加入表，小于零则删除对应绝对值的数据，等于零则遍历表。
	int data;
	while (1)
	{
		printf("请输入一个整数：");
		scanf_s("%d", &data); while (getchar() != '\n');
		if (data > 0)
			add_tail(head, data);		//尾插
		else if (data < 0)
			del(head, -data);
		else
			show(head);
	}

	return 0;
}

//初始化一个空节点
node* Init(void)
{
	node* p = (node*)malloc(sizeof(node));
	p->data = 0;
	p->next = NULL;

	return p;
}

//添加数据，头插
void add_head(node* head, int data)
{
	node* p = Init();			//初始化一个新节点
	p->data = data;				//新节点添加数据

	p->next = head->next;		//新节点指向头结点的指向
	head->next = p;				//头结点指向新节点
	show(head);
}

//添加数据，尾插
void add_tail(node* head, int data)
{
	node* p = Init();			//初始化一个新节点
	p->data = data;				//新节点添加数据

	node* pos = head;
	while (pos->next != NULL)		//找到尾结点pos
	{
		pos = pos->next;
	}
	pos->next = p;				//尾结点指向新节点
	show(head);
}

//删除数据
void del(node* head, int data)
{
	if (head->next == NULL)
	{
		printf("链表为空！\n");
		return;
	}

	node* prev = head;
	for (node* pos = head; pos != NULL; pos = pos->next)	//循环遍历，如果找到则剔除该节点
	{
		if (pos->data != data)								//记录好前一节点prev	
		{
			prev = pos;
		}
		if (pos->data == data)								//剔除节点
		{
			prev->next = pos->next;
			free(pos);
			show(head);
			return;
		}
	}
	printf("没有找到该数据！\n");
}

//遍历链表
void show(node* head)
{
	if (head->next == NULL)
	{
		printf("链表为空！\n");
		return;
	}

	for (node* pos = head->next; pos != NULL; pos = pos->next)
	{
		printf("%d ", pos->data);
	}
	printf("\n");
}


