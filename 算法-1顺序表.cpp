#include <iostream>

using namespace std;

#define MAX 10

class Seqnode
{
public:
	int data;
};


class Seqlist
{
public:
	Seqlist()
	{
		seqlist[MAX] = { 0 };
		count = 0;
	}

	//添加数据
	void add(int data)
	{
		if (count >= MAX)
		{
			cout << "顺序表已满！" << endl;
			return;
		}

		seqlist[count].data = data;
		count++;
		show();
	}

	//删除数据
	void del(int data)
	{
		if (count == 0)
		{
			cout << "顺序表为空！" << endl;
			return;
		}

		for (int i = 0; i < count; i++)
		{
			if (seqlist[i].data == data)			//找到则循环向前覆盖，并将最后一位值0
			{
				for (int n = i; n < count - 1; n++)
				{
					seqlist[n].data = seqlist[n + 1].data;
				}
				seqlist[count - 1].data = 0;
				count--;
				show();
				return;
			}
		}
	}

	//遍历顺序表
	void show(void)
	{
		if (count == 0)
		{
			cout << "顺序表为空" << endl;
			return;
		}

		for (int i = 0; i < count; i++)
		{
			cout << seqlist[i].data << " ";
		}
		cout << endl;
	}

	//有序添加数据（从小到大）
	void order_add(int data)
	{
		if (count >= MAX)
		{
			cout << "顺序表已满！" << endl;
			return;
		}

		int i;								//找到位置，后面的后移，然后新数据插入
		for (i = 0; i < count; i++)
		{
			if (data < seqlist[i].data)
				break;
		}
		for (int n = count; n > i; n--)
		{
			seqlist[n].data = seqlist[n - 1].data;
		}
		seqlist[i].data = data;
		count++;
		show();
	}

private:
	class Seqnode seqlist[MAX];
	int count;						//定义数组数量，数组末位下标为[count-1]
};


int main(void)
{
	Seqlist Seq;

	int data;
	while (1)
	{
		cout << "请输入一个整数：";
		cin >> data;
		if (data > 0)
			Seq.order_add(data);
		else if (data < 0)
			Seq.del(-data);
		else
			Seq.show();
	}

	return 0;
}



