#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
	struct node* prev;
}node;


node* Init(void);
void add_head(node* head, int data);
void add_tail(node* head, int data);
void del(node* head, int data);
void show_next(node* head);
void show_prev(node* head);
void reverse(node* head);


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
			reverse(head);

		show_next(head);
	}

	return 0;
}

//初始化一个空节点
node* Init(void)
{
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL)
	{
		printf("申请堆空间失败！\n");
		return NULL;
	}
	p->data = 0;
	p->next = p;				//指向自己可以省去头结点初始化后指向自己的步骤
	p->prev = p;

	return p;
}

//添加数据，头插
void add_head(node* head, int data)
{
	node* p = Init();			//初始化一个新节点
	p->data = data;				//新节点添加数据

	p->next = head->next;		//新节点next指向头结点的指向
	p->prev = head;				//新节点prev指向头结点
	head->next->prev = p;		//头结点后一节点的prev指向新节点
	head->next = p;				//头结点next指向新节点
}

//添加数据，尾插
void add_tail(node* head, int data)
{
	node* p = Init();			//初始化一个新节点
	p->data = data;				//新节点添加数据

	p->next = head;
	p->prev = head->prev;
	head->prev->next = p;
	head->prev = p;
}

//删除数据
void del(node* head, int data)
{
	if (head->next == head)
	{
		printf("链表为空！\n");
		return;
	}

	for (node* pos = head->next; pos != head; pos = pos->next)	//循环遍历，如果找到则剔除该节点
	{
		if (pos->data == data)									//找到节点并剔除
		{
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;

			free(pos);
			return;
		}
	}
	printf("没有找到该数据！\n");
}

//正向遍历链表
void show_next(node* head)
{
	if (head->next == head)
	{
		printf("链表为空！\n");
		return;
	}

	for (node* pos = head->next; pos != head; pos = pos->next)
	{
		printf("%d ", pos->data);
	}
	printf("\n");
}

//反向遍历链表
void show_prev(node* head)
{
	if (head->next == head)
	{
		printf("链表为空！\n");
		return;
	}

	for (node* pos = head->prev; pos != head; pos = pos->prev)
	{
		printf("%d ", pos->data);
	}
	printf("\n");
}

//链表转置：正向遍历将各节点地进行头插，反向同理。其它思路：正向遍历地将各节点头插到尾结点之后
void reverse(node* head)
{
	node* temp = head->next;					//需要一个指针辅助记录
	for (node* pos = head->next; temp != head; pos = temp)
	{
		temp = pos->next;
		pos->prev->next = pos->next;			//先剔除
		pos->next->prev = pos->prev;

		pos->next = head->next;					//再头插
		pos->prev = head;
		head->next->prev = pos;
		head->next = pos;
	}
}

