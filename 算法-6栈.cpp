#include <iostream>

using namespace std;


class node
{
public:
	int data;
	node* next;
};


class Stack
{
public:
	Stack()
	{
		top = NULL;
	}

	//入栈
	void push(int data)
	{
		node* p = new node;

		p->data = data;
		p->next = top;
		top = p;
	}

	//出栈
	int pop(void)
	{
		if (top == NULL)
		{
			cout << "栈为空！" << endl;
			return;
		}

		node* temp = top;
		top = temp->next;
		int ret = temp->data;
		delete temp;
		return  ret;
	}

	//遍历栈
	void show(void)
	{
		if (top == NULL)
		{
			cout << "栈为空！" << endl;
			return;
		}

		for (node* pos = top; pos != NULL; pos = pos->next)
		{
			cout << pos->data << " ";
		}
		cout << endl;
	}

private:
	node* top;
};


int main(void)
{
	Stack stack;

	int data;
	while (1)
	{
		cout << "请输入一个整数：";
		cin >> data;
		if (data > 0)
			stack.push(data);
		else if (data < 0)
			cout << stack.pop() << endl;
		else
		{
			stack.show();
			continue;
		}

		stack.show();
	}

	return 0;
}



