#include <iostream>

using namespace std;


class node
{
public:
	int data;
	node* next;
};


class Queue
{
public:
	Queue()
	{
		head = this->init();
		front = head;
		rear = head;
	}

	//初始化一个节点
	node* init(void)
	{
		node* p = new node;
		p->data = 0;
		p->next = NULL;
		return p;
	}

	//进队
	void enter(int data)
	{
		node* p = this->init();

		p->data = data;
		p->next = NULL;
		rear->next = p;
		rear = p;
	}

	//出队
	void exit(void)
	{
		if (front->next == NULL)
		{
			cout << "队列为空！" << endl;
			return;
		}

		node* temp = front->next;
		cout << "出队：" << temp->data << endl;
		front->next = front->next->next;
		delete temp;

	}

	//遍历队列
	void show(void)
	{
		if (front->next == NULL)
		{
			cout << "队列为空！" << endl;
			return;
		}

		for (node* pos = front->next; pos != NULL; pos = pos->next)
		{
			cout << pos->data << " ";
		}
		cout << endl;
	}

private:
	node* head;
	node* front;
	node* rear;
};


int main(void)
{
	Queue queue;

	int data;
	while (1)
	{
		cout << "请输入一个整数：";
		cin >> data;
		if (data > 0)
			queue.enter(data);
		else if (data < 0)
			queue.exit();
		else
		{
			queue.show();
			continue;
		}
		queue.show();
	}

	return 0;
}


