/********************/三向比较/************************************************************/
bool b = 7 <= > 11 < 0;					//b == true
bool b = 7 <= > 11 < 100;				//编译失败，<=>的返回值只能与0和自身类型比较

//返回三种结果
strong_ordering：表示两个操作数（类型等）相同，可以相互替换
weak_ordering：表示两个操作数（类型等）不同，无法相互替换
partial_ordering

std::strong_ordering::less：如果 a 小于 b，则返回该值；
std::strong_ordering::equal：如果 a 等于 b，则返回该值；
std::strong_ordering::greater：如果 a 大于 b，则返回该值。

std::weak_ordering::less
std::weak_ordering::equal
std::weak_ordering:::greater

std::partial_ordering::less
std::partial_ordering::equal
std::partial_ordering::greater
std::partial_ordering::unordered：表示两个操作数没有任何关系


int main()
{
	int a = 1;
	int b = 2;

	std::strong_ordering result = a <= > b;

	if (result == std::strong_ordering::less)
	{
		std::cout << "a < b" << std::endl;
	}
	else if (result == std::strong_ordering::equal)
	{
		std::cout << "a == b" << std::endl;
	}
	else if (result == std::strong_ordering::greater)
	{
		std::cout << "a > b" << std::endl;
	}
}


