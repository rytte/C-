/********************/表达式求值顺序确定/************************************************************/
C++17之前部分表达式求值顺序是不确定的。

void f2()
{
	std::string s = "but I have heard it works even if you don't believe in it";
	s.replace(0, 4, "")
		.replace(s.find("even"), 4, "only")
		.replace(s.find("don't"), 6, "");

	assert(s == "I have heard it works only if you believe in it");		// OK
}

> 理想的顺序<
	replace(0, 4, "")
	tmp1 = find("even")
	replace(tmp1, 4, "only")
	tmp2 = find(" don't")
	replace(tmp2, 6, "")

>实际顺序 <
	tmp1 = find("even")
	tmp2 = find(" don't")
	replace(0, 4, "")
	replace(tmp1, 4, "only")
	replace(tmp2, 6, "")


//C++17标准规定

1、函数表达式一定会在函数的参数之前求值
foo(a, b, c);

2、后缀表达式和移动运算符求值总是从左往右的
E1[E2]
E1.E2
E1.*E2
E1->*E2
E1<<E2
E1>>E2

3、赋值表达式总是从右往左的
E1=E2
E1+=E2
E1-=E2
E1*=E2
E1/=E2
...

4、 new 表达式的内存分配总是会优先于构造函数中参数的求值

5、重载运算符的表达式的求值顺序应由与之相应内置运算符的求值顺序确定



