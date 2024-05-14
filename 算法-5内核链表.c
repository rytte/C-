#include <stdio.h>
#include <stdlib.h>
#include "kernel_list.h"

// struct list_head{
// 	struct list_head *next;
// 	struct list_head *prev;
// };

// 内核链表的节点结构体（大结构体）
typedef struct node {
	int data; //数据域
	struct list_head list; //小结构体（前后逻辑）
}node;

// 添加数据尾插
void kl_add_tail(int new_data, node* head);
// 添加数据头插
void kl_add(int new_data, node* head);
// 初始化一个空链表
node* kl_init(void);
// 遍历内核链表
void kl_show(node* head);
// 删除节点
void kl_del(int del_data, node* head);

int main()
{
	// 1.初始化一个空链表（只有一个头节点）
	node* head = kl_init();
	// 2.数据操作
	int cmd;
	while (1)
	{
		printf("Pls Input: ");
		scanf("%d", &cmd); while (getchar() != '\n');
		if (cmd > 0)
			// kl_add(cmd, head); // 添加数据
			kl_add_tail(cmd, head); // 添加数据尾插
		else if (cmd < 0)
			kl_del(-cmd, head); // 删除节点
		kl_show(head);
	}

	return 0;
}

// 删除节点
void kl_del(int del_data, node* head)
{
	/*// 1.判断是否为空链表
	if(list_empty(&head->list))
	{
		printf("ERROR: empty!\n");
		return ;
	}
	// 2.遍历链表，找到指向的节点，找到后break；
		// 如果在遍历中删除，移动节点，必须使用安全模式（暂存节点）
		// 如果只是遍历，不修改节点，使用安全模式/非安全模式都可以
	node *get_node;
	struct list_head *pos,*n;
	list_for_each_safe(pos, n, &head->list)
	{
		get_node = list_entry(pos, node, list);
		if(get_node->data == del_data)
			break;
	}
	// 3.如果找不到（循环正常结束）
	if(pos == &head->list)
	{
		printf("ERROR: not found!\n");
		return ;
	}
	// 4.找到就删除节点,释放大结构体堆空间
	list_del(pos);
	free(get_node);*/

	/**********************************************/
	// 1.判断是否为空链表
	if (head->list.next == &head->list)
	{
		printf("ERROR: empty!\n");
		return;
	}
	// 2.遍历链表，找到指向的节点，找到后break；
		// 如果在遍历中删除，移动节点，必须使用安全模式（暂存节点）
		// 如果只是遍历，不修改节点，使用安全模式/非安全模式都可以
	node* get_node;
	struct list_head* pos, * n;
	for (pos = head->list.next; pos != &head->list; pos = n)
	{
		n = pos->next;
		get_node = list_entry(pos, node, list);
		if (get_node->data == del_data)
			break;
	}
	// 3.如果找不到（循环正常结束）
	if (pos == &head->list)
	{
		printf("ERROR: not found!\n");
		return;
	}
	// 4.找到就删除节点,释放大结构体堆空间
	pos->next->prev = pos->prev;
	pos->prev->next = pos->next;
	// free(pos); // 不能重复释放同一块堆空间
	free(get_node);
}

// 添加数据尾插
void kl_add_tail(int new_data, node* head)
{
	// 1.给新节点分配堆空间，并将数据写入
	node* new = kl_init();
	new->data = new_data;
	// 2.操作指针
	// list_add_tail(&new->list, &head->list); // 把new放到head的prev之后
	new->list.next = &head->list; // 新节点指向头节点的指针域
	new->list.prev = head->list.prev; // 新节点指向尾节点的指针域
	head->list.prev->next = &new->list; // 尾节点指向新节点的指针域
	head->list.prev = &new->list; // 头节点指向新节点的指针域
}

// 添加数据头插
void kl_add(int new_data, node* head)
{
	// 1.给新节点分配堆空间，并将数据写入
	node* new = kl_init();
	new->data = new_data;
	// 2.操作指针
	list_add(&new->list, &head->list);

	/*new->list.next = head->list.next; // 新节点指向头节点的后继节点指针域
	new->list.prev = &head->list; // 新节点指向头节点的指针域
	head->list.next->prev = &new->list; // 后继节点指向新节点的指针域
	head->list.next = &new->list;*/ // 头节点的指针域指向新节点的指针域
}

// 遍历内核链表
void kl_show(node* head)
{
	node* get_node;
	struct list_head* pos;
	list_for_each(pos, &head->list)
	{
		// 由小结构体的地址，获取大结构体的地址
		get_node = list_entry(pos, node, list);
		printf("%d ", get_node->data);
	}
	printf("\n");
}

// 初始化一个空链表
node* kl_init(void)
{
	// 1.分配一个节点堆空间，清空数据并初始化，两个指针指向自身
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL)
	{
		perror("malloc failed!\n");
		return NULL;
	}
	p->data = 0;
	// p->list.next = p;
	// p->list.prev = p;
	// struct list_head * = node *
	// 小结构体指针 = 大结构体指针

	// p->list.next = &p->list;
	// p->list.prev = &p->list;
	INIT_LIST_HEAD(&p->list);
	// 2.返回堆空间地址
	return p;
}