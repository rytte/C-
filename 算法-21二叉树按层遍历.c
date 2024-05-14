#include <stdio.h>
#include <stdlib.h>
#include "drawtree.h"

// 节点设计
typedef struct node {
	int data;	// 数据域
	struct node* lchild; // 左子树指针
	struct node* rchild; // 右子树指针
}node;

// 队列的节点
struct queue_node {
	node* ptr; // 队列数据域 二叉树
	struct queue_node* next;
};

// 队列统筹结构体
typedef struct queue_link
{
	int size; // 队列长度
	struct queue_node* first; // 队头指针
	struct queue_node* last; // 队尾指针
}slink, * plink;


// 二叉树插入
node* bst_insert(node* root, int new_data);
// 前序遍历：根节点-左子树-右子树
void prev_travel(node* root);
// 后序遍历：左子树-右子树-根节点
void last_travel(node* root);
// 中序遍历：左子树-根节点-右子树
void midd_travel(node* root);
// 按层遍历 二叉树
void lay_travel(node* root);
// 创建队列的统筹节点（初始化一个空队列）
plink creat_queue(void);
// 入队
void queue_push(plink queue, node* dest);
// 创建队列的普通节点
struct queue_node* create_queue_node(node* dest);
// 出队
node* queue_pop(plink queue);

int main()
{
	// 1.初始化空二叉树
	node* root = NULL;
	root = bst_insert(root, 70);
	root = bst_insert(root, 66);
	root = bst_insert(root, 65);
	root = bst_insert(root, 68);
	root = bst_insert(root, 67);
	root = bst_insert(root, 69);
	root = bst_insert(root, 71);
	root = bst_insert(root, 73);
	root = bst_insert(root, 72);
	// 2.数据操作
	int cmd;
	while (1)
	{
		printf("Pls Input: ");
		scanf("%d", &cmd); while (getchar() != '\n');
		if (cmd != 0)
			root = bst_insert(root, cmd); // 二叉树插入
		else if (cmd == 0)
		{
			printf("前序遍历：");
			prev_travel(root); // 前序遍历
			printf("\n");

			printf("中序遍历：");
			midd_travel(root); // 中序遍历
			printf("\n");

			printf("后序遍历：");
			last_travel(root); // 后序遍历
			printf("\n");

			printf("按层遍历：");
			lay_travel(root); // 按层遍历
			printf("\n");

		}

		draw((_treenode*)root);
	}

	return 0;
}

// 出队
node* queue_pop(plink queue)
{
	// 判断队列是否为空
	if (queue->size == 0)
	{
		printf("队列为空\n");
		return NULL;
	}
	// 获取队头的位置
	struct queue_node* p = queue->first;
	node* dest = p->ptr; // 将获取的节点赋值给dest

	// 更新队头位置
	queue->first = p->next;
	// 更新队列的长度
	queue->size--;
	printf("%c ", dest->data);
	// 释放出队的数据节点
	free(p);

	return dest;
}

// 创建队列的普通节点
struct queue_node* create_queue_node(node* dest)
{
	// 申请新节点
	struct queue_node* new = malloc(sizeof(struct queue_node));
	if (new == NULL)
	{
		perror("malloc failed!\n");
		return NULL;
	}
	// 初始化新节点
	new->ptr = dest; // 数据域
	new->next = NULL;
	return new;
}

// 入队
void queue_push(plink queue, node* dest)
{
	// 定义新节点，初始化二叉树节点
	struct queue_node* new = create_queue_node(dest);
	// 入队操作
	if (queue->size == 0) // 队列为空
	{
		queue->first = new;
		queue->last = new;
		queue->size++;
	}
	else
	{
		queue->last->next = new;
		queue->last = new;
		queue->size++;
	}

}

// 创建队列的统筹节点（初始化一个空队列）
plink creat_queue(void)
{
	// 1.申请堆空间
	plink queue = malloc(sizeof(slink));
	if (queue == NULL)
	{
		perror("queue error\n");
		return NULL;
	}
	// 2.空队列初始化
	queue->size = 0;
	queue->first = NULL;
	queue->last = NULL;
	// 3.返回队列
	return queue;
}

// 按层遍历 二叉树
void lay_travel(node* root)
{
	// 1.定义指针指向队列
	plink queue = creat_queue();
	// 2.将二叉树节点入队
	queue_push(queue, root);

	// 3.出队，获取节点的左右子树地址，如果不为空，则继续入队，
	// 3.1队列长度为0的时候，说明队列中没有数据，遍历结束
	node* temp = NULL;
	while (queue->size != 0)
	{
		// 获取出队的结果
		temp = queue_pop(queue);
		if (temp->lchild != NULL)
			queue_push(queue, temp->lchild);
		if (temp->rchild != NULL)
			queue_push(queue, temp->rchild);
	}
	printf("\n");
	free(queue);
}

// 后序遍历：左子树-右子树-根节点
void last_travel(node* root)
{
	if (root == NULL) // 如果根节点为NULL，直接返回
		return;

	last_travel(root->lchild); // 访问左子树
	last_travel(root->rchild); // 访问右子树
	// 如果根节点不为NULL，有数据先打印
	printf("%c ", root->data);

}

// 中序遍历：左子树-根节点-右子树
void midd_travel(node* root)
{
	if (root == NULL) // 如果根节点为NULL，直接返回
		return;

	midd_travel(root->lchild); // 访问左子树
	// 如果根节点不为NULL，有数据先打印
	printf("%c ", root->data);

	midd_travel(root->rchild); // 访问右子树
}

// 前序遍历：根节点-左子树-右子树
void prev_travel(node* root)
{
	if (root == NULL) // 如果根节点为NULL，直接返回
		return;
	// 如果根节点不为NULL，有数据先打印
	printf("%c ", root->data);

	prev_travel(root->lchild); // 访问左子树
	prev_travel(root->rchild); // 访问左子树
}

// 二叉树插入
node* bst_insert(node* root, int new_data)
{
	if (root == NULL)
	{
		// 1.给新节点申请堆空间，并将数据写入
		node* new = (node*)malloc(sizeof(node));
		new->data = new_data;

		new->lchild = NULL;
		new->rchild = NULL;
		return new;
	}
	else if (root->data > new_data)
		root->lchild = bst_insert(root->lchild, new_data);
	else if (root->data < new_data)
		root->rchild = bst_insert(root->rchild, new_data);
	else // 如果相等，数据已存在，不能插入
		printf("已经存在！\n");

	return root;
}