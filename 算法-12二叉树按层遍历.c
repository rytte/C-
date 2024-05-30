#include <stdio.h>
#include <stdlib.h>

//节点设计
typedef struct node
{
	int data;		//数据域
	struct node* lchild;	//左子树指针
	struct node* rchild;	//右子树指针
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


node* add(node* root, int data);
node* del(node* root, int data);

void lay_travel(node* root);		// 按层遍历 二叉树
plink creat_queue(void);			// 初始化一个空队列
void queue_push(plink queue, node* dest);				// 入队
struct queue_node* add_queue_node(node* dest);		// 创建队列的普通节点
node* queue_pop(plink queue);						// 出队


int main(void)
{
	node* root = NULL;		//初始化根节点

	int data;
	while (1)
	{
		printf("请输入一个整数：");
		scanf_s("%d", &data); while (getchar() != '\n');

		if (data > 0 && data < 10000)
			root = add(root, data);
		else if (data == 0)
		{
			printf("按层遍历：");
			lay_travel(root); // 按层遍历
			printf("\n");
		}
		else if (data < 0)
			del(root, -data);
	}

	return 0;
}

//插入数据
node* add(node* root, int data)
{
	if (root == NULL)		//若传入的根节点为空指针，则为其初始化一个节点
	{
		node* p = (node*)malloc(sizeof(node));
		p->data = data;

		p->lchild = NULL;
		p->rchild = NULL;
		return p;
	}
	else if (data < root->data)			//新数据小于节点数据，则左递归
		root->lchild = add(root->lchild, data);
	else if (data > root->data)			//新数据大于节点数据，则右递归
		root->rchild = add(root->rchild, data);
	else
		printf("数据已存在！\n");

	return root;
}

//删除数据
node* del(node* root, int data)
{
	if (data < root->data)			//删除数据小于节点数据，则左递归
	{
		if (root->lchild == NULL)
			printf("没有数据\n");
		else
			root->lchild = del(root->lchild, data);
	}
	else if (data > root->data)		//删除数据大于节点数据，则右递归
	{
		if (root->rchild == NULL)
			printf("没有数据\n");
		else
			root->rchild = del(root->rchild, data);
	}
	else if (data == root->data)	//找到需删除数据
	{
		node* temp = NULL;
		if (root->lchild != NULL)	//若有左子树，则找到左子树的最右子树，这是最接近原节点的数，可以替代原节点
		{
			temp = root->lchild;		//temp指向左子树
			while (temp->rchild != NULL)		//若左子树有右子树
				temp = temp->rchild;			//temp指向该右子树，循环
			root->data = temp->data;			//替换
			root->lchild = del(root->lchild, temp->data);	//左节点递归
		}
		else if (root->rchild != NULL)
		{
			temp = root->rchild;
			while (temp->lchild != NULL)
				temp = temp->lchild;
			root->data = temp->data;
			root->rchild = del(root->rchild, temp->data);
		}
		else // 叶子节点
		{
			free(root);
			return NULL;
		}
	}
	return root;
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
	printf("%d ", dest->data);
	// 释放出队的数据节点
	free(p);

	return dest;
}

// 创建队列的普通节点
struct queue_node* add_queue_node(node* dest)
{
	// 申请新节点
	struct queue_node* p = (struct queue_node*)malloc(sizeof(struct queue_node));
	if (p == NULL)
	{
		perror("malloc failed!\n");
		return NULL;
	}
	// 初始化新节点
	p->ptr = dest; // 数据域
	p->next = NULL;
	return p;
}

// 入队
void queue_push(plink queue, node* dest)
{
	// 定义新节点，初始化二叉树节点
	struct queue_node* p = add_queue_node(dest);
	// 入队操作
	if (queue->size == 0)			// 队列为空则新节点作为首节点
		queue->first = p;
	else							//否则插到尾结点的后面
		queue->last->next = p;

	queue->last = p;				//尾指针指向新节点
	queue->size++;

}

// 初始化一个空队列
plink creat_queue(void)
{
	// 1.申请堆空间
	plink queue = (plink)malloc(sizeof(slink));
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

	// 3.出队。然后获取节点的左右子树节点，如果不为空，则继续入队，
	// 3.1队列长度为0的时候，说明队列中没有数据，遍历结束
	node* temp = NULL;
	while (queue->size != 0)
	{
		// 获取出队的结果
		temp = queue_pop(queue);				//temp将在每次循环更新为队头的节点
		if (temp->lchild != NULL)
			queue_push(queue, temp->lchild);
		if (temp->rchild != NULL)
			queue_push(queue, temp->rchild);
	}
	printf("\n");
	free(queue);
}
