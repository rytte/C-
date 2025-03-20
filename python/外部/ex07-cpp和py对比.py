					py							cpp
输出变量		print(x,y)				printf("%s,%s",x,y);
原生字符串	r"abc"					R"(abc)"
条件语句		elif						else if
条件语句		无括号有冒号		加括号无冒号
逻辑运算符	and、or、not		&&、||、！
短路求值		输出原值				输出1（true）或0（false）
元组				元素值不可变		元素值可变，但数量和类型不可变
继承				class A(B, C):		class A : public B, public C {}  
访问权限		默认公有				默认私有
菱形继承		使用 super()			使用 virtual

py语法糖
交换变量值		x, y = y, x	（原理：创建匿名元组并解包）
字符串乘法		"abc"*10	
自动类型推断	a = 1
地板除				a = 3//2
循环语句			可以搭配 else
格式化字符串	format()、f字符串

