#include <iostream>

using namespace std;

class node				//定义节点类
{
public:
	int data;
	node* next;
};

class List
{
public:
	List()
	{
		head = Init();			//初始化头结点
		head->next = head;
	}

	//初始化节点
	node* Init(void)
	{
		node* p = new node;
		p->data = 0;
		p->next = NULL;
		return p;
	}

	//添加数据，头插
	void add_head(int data)
	{
		node* p = Init();			//初始化一个新节点
		p->data = data;				//新节点添加数据

		p->next = head->next;		//新节点指向头结点的指向
		head->next = p;				//头结点指向新节点
		show();
	}

	//添加数据，尾插
	void add_tail(int data)
	{
		node* p = Init();			//初始化一个新节点
		p->data = data;				//新节点添加数据
		p->next = head;

		node* pos = head;			//找到尾结点
		while (pos->next != head)
		{
			pos = pos->next;
		}
		pos->next = p;				//尾结点指向新节点
		show();
	}

	//删除数据
	void del(int data)
	{
		if (head->next == head)
		{
			cout << "链表为空！" << endl;
			return;
		}

		node* prev = head;
		for (node* pos = head->next; pos != head; pos = pos->next)
		{
			if (pos->data != data)
			{
				prev = pos;
			}
			if (pos->data == data)
			{
				prev->next = pos->next;
				delete pos;
				show();
				return;
			}
		}
		cout << "没有找到该数据！" << endl;
	}

	//遍历链表
	void show(void)
	{
		if (head->next == head)
		{
			cout << "链表为空！" << endl;
			return;
		}

		for (node* pos = head->next; pos != head; pos = pos->next)
		{
			cout << pos->data << " ";
		}
		cout << endl;
	}

private:
	node* head;			//定义头指针
};


int main(void)
{
	List list;

	int data;
	while (1)
	{
		cout << "请输入一个整数：";
		cin >> data;
		if (data > 0)
			list.add_tail(data);
		else if (data < 0)
			list.del(-data);
		else
			list.show();
	}

	return 0;
}