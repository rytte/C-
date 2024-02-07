/********************/模块/************************************************************/
主要用途是将大型工程中的代码拆分成独立的逻辑单元，以方便大型工程的代码管理。

//helloworld.ixx
export module helloworld;
import std.core;
export void hello()
{
	cout << "Hello World!" << endl;
}

//modules_test.cpp
import helloworld;
int main()
{
	hello();
}




