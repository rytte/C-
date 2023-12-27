#include <iostream>

using namespace std;

class node				//定义节点类
{
public:
	int data;
	node* next;
	node* prev;
};

class List
{
public:
	List()
	{
		head = Init();			//初始化头结点
	}

	//初始化节点
	node* Init(void)
	{
		node* p = new node;
		p->data = 0;
		p->next = p;
		p->prev = p;
		return p;
	}

	//添加数据，头插
	void add_head(int data)
	{
		node* p = Init();			//初始化一个新节点
		p->data = data;				//新节点添加数据

		p->next = head->next;		//新节点next指向头结点的指向
		p->prev = head;				//新节点prev指向头结点
		head->next->prev = p;		//头结点后一节点的prev指向新节点
		head->next = p;				//头结点next指向新节点
	}

	//添加数据，尾插
	void add_tail(int data)
	{
		node* p = Init();			//初始化一个新节点
		p->data = data;				//新节点添加数据

		p->next = head;
		p->prev = head->prev;
		head->prev->next = p;
		head->prev = p;
	}

	//删除数据
	void del(int data)
	{
		if (head->next == head)
		{
			cout << "链表为空！" << endl;
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
		cout << "没有找到该数据！" << endl;
	}

	//正向遍历链表
	void show_next(void)
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

	//反向遍历链表
	void show_prev(void)
	{
		if (head->next == head)
		{
			cout << "链表为空！" << endl;
			return;
		}

		for (node* pos = head->prev; pos != head; pos = pos->prev)
		{
			cout << pos->data << " ";
		}
		cout << endl;
	}

	//链表转置：正向遍历将各节点地进行头插，反向同理。其它思路：正向遍历地将各节点头插到尾结点之后
	void reverse(void)
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
			list.reverse();

		list.show_next();
	}

	return 0;
}



