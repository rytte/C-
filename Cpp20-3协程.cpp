/********************/协程/************************************************************/;
co_await 与 co_return 实例

#include <iostream>
using namespace std;

future<int> foo()
{
	cout << "4" << endl;
	this_thread::sleep_for(3s);
	co_return 10;
}

future<future<int>> bar()
{
	cout << "2" << endl;
	auto n = co_await async(foo);		//挂起点，等待返回值
	cout << "5 << endl;
	co_return n;
}

int main()
{
	cout << "1" << endl;
	auto i = bar();
	cout << "3" << endl;
	i.wait();						//等待返回值
	cout << "result = " << i.get().get();
}



co_yield 实例:

experimental::generator<int> foo()
{
	cout << "begin" << endl;
	for (int i = 0; i < 10; i++)
	{
		co_yield i;					//挂起点，返回 i 值到main函数。
	}
	cout << "end" << endl;
}

int main()
{
	for (auto i : foo())
		cout << i << endl;
}




co_await 运算符
内置三个函数
await_ready：用于判定可等待体是否以及准备好
await_suspend：调度协程的执行流程
await_resume：一个接收异步执行结构






