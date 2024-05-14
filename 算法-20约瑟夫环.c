#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 声明一个结构体模板（设计数据节点）【数据域，指针域】
typedef struct node {
	int data;// 数据域
	struct node* next; // 指针域
}l_node;

// 函数声明
// 添加数据头插法
void link_list_add(int new_data, l_node* head);
// 初始化一个空节点
l_node* link_list_init(void);
// 遍历链表
void link_list_show(l_node* head);
// 添加数据尾插法
void link_list_add_tail(int new_data, l_node* head);
// 节点删除
void link_list_del(int del_data, l_node* head);
// 数3出局
void link_list_cycle_game(l_node* head, int n);

int main()
{
	// 1.初始化一个空链表（分配一个头节点堆空间）
	l_node* head = link_list_init();

	// 2.输入总人数n，并将1~n插入到链表
	int n;
	printf("请输入总人数！\n");
	scanf("%d", &n); while (getchar() != '\n');

	for (int i = 1; i <= n; i++)
		link_list_add_tail(i, head); // 尾插
	link_list_show(head); // 遍历链表
	// 3.开始数3出局
	link_list_cycle_game(head, n);


	return 0;
}

// 数3出局
void link_list_cycle_game(l_node* head, int n)
{
	l_node* pos = head->next;
	l_node* temp = NULL;
	int flag = 1;
	while (1)
	{
		// 1.如果当前总人数num<=1,游戏结束，打印幸存者
		if (n <= 1)
			break;
		// 2.数3
		for (int i = 0; i < 2; i++)
		{
			pos = pos->next;
			if (pos == head)
				pos = pos->next;
		}
		// 3.删除数到3的节点（出局），总人数num--
		printf("第%d次删除的为：%d\n", flag++, pos->data);
		temp = pos->next;
		link_list_del(pos->data, head);
		pos = temp; // pos已经被free，不能再次访问（非法内存操作）
		if (pos == head)
			pos = pos->next;
		n--;

	}
	// 4.打印幸存者
	link_list_show(head);
}


// 节点删除
void link_list_del(int del_data, l_node* head)
{
	// 0.判断链表是否为空链表（只有一个头节点）
	if (head->next == head)
	{
		printf("链表是空链表！\n");
		return;
	}
	// 1.逐个对比，如果不同，2个指针一起移动，如相同，则跳出
	l_node* pos_prev = head;
	l_node* pos_del;
	for (pos_del = head->next; pos_del != head; pos_del = pos_del->next)
	{
		if (pos_del->data == del_data)
			break;
		pos_prev = pos_del;
	}
	// 1.2 如果循环正常结束，说明没有数据
	if (pos_del == head)
	{
		printf("没有找到！\n");
		return;
	}
	// 2.如果找到，操作指向域，使欲删除节点的前节点指向欲删除节点的后节点
	pos_prev->next = pos_del->next;
	// 3.释放欲删除节点的堆空间
	free(pos_del);
}


// 遍历链表
void link_list_show(l_node* head)
{
	l_node* pos = head;
	for (pos = head->next; pos != head; pos = pos->next)
		printf("%d ", pos->data);
	printf("\n");
}

// 添加数据尾插法
void link_list_add_tail(int new_data, l_node* head)
{
	// 1.找到尾节点（特点：指针域指向head）
	l_node* pos_tail = head;
	while (pos_tail->next != head)
		pos_tail = pos_tail->next;
	// 2.将新节点放在尾节点之后
	link_list_add(new_data, pos_tail);
}

// 添加数据头插法
void link_list_add(int new_data, l_node* head)
{
	// 1.给新节点申请堆空间，并将数据写入
	l_node* new = link_list_init();
	new->data = new_data;
	// 2.修改指针指向(注意前后顺序)
	// 2.1先将头节点的指针域，给新节点
	new->next = head->next;
	// 2.2头节点指向新节点
	head->next = new;
}

// 初始化一个空节点
l_node* link_list_init(void)
{
	// 1.申请堆空间
	l_node* p = malloc(sizeof(l_node));
	if (NULL == p)
	{
		printf("申请堆空间失败!\n");
		return NULL;
	}
	// 2.清空节点
	p->data = 0;
	p->next = p;
	// 3.成功则将堆空间的地址返回
	return p;
}