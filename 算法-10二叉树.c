#include <stdio.h>
#include <stdlib.h>

//节点设计
typedef struct node
{
	int data;		//数据域
	struct node* lchild;	//左子树指针
	struct node* rchild;	//右子树指针
}node;


node* add(node* root, int data);
node* del(node* root, int data);
void pre_travel(node* root);
void in_travel(node* root);
void post_travel(node* root);
int search(node* root, int data);


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
		else if (data >= 10000)
		{
			if (search(root, data % 10000) == -1)
				printf("无此数据\n");
		}
		else if (data == 0)
		{
			printf("先序遍历：");
			pre_travel(root);
			printf("\n");

			printf("中序遍历：");
			in_travel(root);
			printf("\n");

			printf("后序遍历：");
			post_travel(root);
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

//先序遍历：根-左-右
void pre_travel(node* root)
{
	if (root == NULL)		//如果根节点为NULL，则直接返回
		return;

	printf("%d ", root->data);		//打印本节点
	pre_travel(root->lchild);		//访问左子树
	pre_travel(root->rchild);		//访问右子树
}

//中序遍历：左-根-右
void in_travel(node* root)
{
	if (root == NULL)		//如果根节点为NULL，则直接返回
		return;

	in_travel(root->lchild);		//访问左子树
	printf("%d ", root->data);		//打印本节点
	in_travel(root->rchild);		//访问右子树
}

//后序遍历：左-右-根
void post_travel(node* root)
{
	if (root == NULL)		//如果根节点为NULL，则直接返回
		return;

	post_travel(root->lchild);		//访问左子树
	post_travel(root->rchild);		//访问右子树
	printf("%d ", root->data);		//打印本节点
}

//搜索
int search(node* root, int data)
{
	if (root == NULL)			//遇到空节点
		return -1;

	if (root->data == data)		//找到指定数据
	{
		printf("已找到该数据\n");
		return 0;
	}
	else if (data < root->data)
		search(root->lchild, data);
	else if (data > root->data)
		search(root->rchild, data);
}