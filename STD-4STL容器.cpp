/********************/容器 Container/************************************************************/
容器本质上是一个模板类，可以存放任意数据类型。


//容器嵌套
类似于结构体嵌套结构体，类嵌套类，容器也可以嵌套容器。
vector <vector<int> > V;		//旧标准：定义容器嵌套容器时，> >运算符间要留有空格


//注意
1、容器类型为对象类型时，会在存入调用拷贝构造，创建新对象。
2、容器类型为对象指针时，会存放地址，不会调用拷贝构造，仍然指向原对象地址。
3、当容器嵌套容器的时候，注意大容器是调用了拷贝构造函数，与原来的小容器是不同的对象，两个容器的数据是不会同步的。


//常用方法
begin()					获取首元素的地址
end()					获取尾元素的下一个元素的地址，可以用作迭代器遍历的条件
size()					获取当前容器中元素的个数
clear()					清空容器
empty()					判断容器是否为空，空则返回 true, 否则返回 false


//数据结构查找效率
数据结构					底层实现					查找复杂度				适用场景
std::list				双向链表					O(n)					不适合高效查找
std::vector(未排序)		动态数组					O(n)					适用于少量数据，或者查找不频繁的情况
std::vector（排序后）	动态数组 + 二分查找		O(log n)				仅查找时可行，但插入删除慢
std::map				红黑树					O(log n)				需要 key - value 结构时
std::unordered_map		哈希表					O(1) 平均，O(n) 最坏		哈希查找最优，键值映射
std::set				红黑树					O(log n)				需要排序，查找较快，插入删除稳定
std::unordered_set		哈希表					O(1) 平均，O(n) 最坏		仅需查找，且数据无序时更快



/********************/数组容器 vector/************************************************************/
vector是一个封装了动态大小数组的数组容器（Sequence Container），可以像数组一样使用下标运算符访问其中的元素。


#include <vector>
using namespace std;


//构造函数
vector<int>V;						//无参构造
vector<int>V2(V);					//拷贝构造
vector<int>V3(V.begin(), V.end());	//将区间内的元素拷贝给新容器
vector<int>V4(n, elem);				//将n个元素拷贝给新容器

//iterators（迭代器）
begin			返回指向容器中第一个元素的迭代器。
end				返回指向容器最后一个元素所在位置后一个位置的迭代器
rbegin			返回容器逆序的第一个元素的迭代器
rend				返回容器逆序的最后一个元素的前一个位置的迭代器
cbegin			和begin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
cend				和end()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crbegin			和rbegin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crend			和rend()功能相同，在其基础上增加了 const 属性，不能用于修改元素。

//Capacity（容量）
size				返回实际元素的个数
capacity			返回总共可以容纳的元素个数
max_size			返回元素个数的最大值。这个值非常大，一般是2 ^ 32 - 1
empty			判断vector是否为空，为空返回true否则false
resize			改变实际元素的个数，对应于size
reserve			增加容器的容量，控制vector的预留空间
shrink_to_fit		减少capacity到size的大小，即减小到size的大小

//Element access（元素访问）
operator[]		vector可以和数组一样用[]访问元素
at				vector.at(i)等同于vector[i]，访问数组下表的元素
front				返回第一个元素
back				返回最后一个元素
data				返回指向容器中第一个元素的指针

//Modifiers（修改器）
push_back		在容器的尾部插入元素
pop_back			删除最后一个元素
insert			插入元素
erase			删除元素
clear				清除容器内容，size = 0，存储空间不变
swap			交换两个元素的所有内容
assign			用新元素替换原有内容。
emplace			插入元素，和insert实现原理不同，速度更快
emplace_back		在容器的尾部插入元素，和push_back不同
get_allocator		返回容器的内存分配器。



/********************/链表容器 list/************************************************************/
list是一个模板类，它的本质是一个可以存储任意数据的双向链表。
如果需要大量数据的插入和删除，而对数据的随机访问比较少，使用list是个不错的选择。


//list对比vector
1、vector有size和capacity，一个是当前容器大小，另一个是可以存储容器大小；而list只有size，因为list不需要扩容，所以不需要提前预留空间。
2、vector访问容器可以通过下标[]和at，而list只能直接访问头部和尾部元素，访问某个具体元素需要遍历list。
3、list是双向链表，头尾都可以加入元素，而vector只能尾部插入。
4、list内置了一些算法中的方法，如：sort、reverse，并且可以轻松删除元素：remove、remoce_if；而vector并不具备。


#include <list>
using namespace std;


//构造函数
list<int> L;					 //无参构造
list<int> L2(L);				         //拷贝构造
list<int> L3(L.begin(), L.end());	 //将区间内的元素拷贝给新容器
list<int> L4(n, elem);			 //将n个元素拷贝给新容器

//iterators（迭代器）
begin			返回指向容器中第一个元素的双向迭代器。
end				返回指向容器最后一个元素所在位置后一个位置的双向迭代器
rbegin			返回容器逆序的第一个元素的双向迭代器
rend				返回容器逆序的最后一个元素的前一个位置的双向迭代器
cbegin			和begin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
cend				和end()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crbegin			和rbegin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crend			和rend()功能相同，在其基础上增加了 const 属性，不能用于修改元素。

//Capacity（容量）
size				返回实际元素的个数
max_size			返回元素个数的最大值。这个值非常大，一般是2 ^ 32 - 1
empty			判断vector是否为空，为空返回true否则false
resize			调整容器的大小

//Element access（元素访问）
front				返回第一个元素的引用
back				返回最后一个元素的引用。

//Modifiers（修改器）
push_front		在容器头部插入元素
push_back		在容器尾部插入元素
emplace_front		在容器头部生成元素。同push_front，效率更高
emplace_back		在容器尾部生成元素。同push_back，效率更高
insert			在容器指定位置插入元素
emplace			在容器指定位置擦插入元素。同insert，效率更高
erase			删除容器中一个或某区域内的元素
assign			用新元素替换容器中的原有内容
swap			交换两个容器中的元素。必须保证两个容器存储的是同一数据类型
clear				清除容器内容，size = 0，存储空间不变

//list operations
splice			将一个list容器中的元素插入另一个容器的指定位置
remove(val)		删除容器中所有值等于val的元素
remove_if			删除容器中满足某个条件的元素
unique			删除容器中相邻的重复元素，只保留一个
merge			合并两个实现已经排好序的list容器，并且合并后的list容器仍然是有序的
sort				将容器排序，通过更改容器中元素的位置
reverse			反转容器中元素的位置



/********************/map / multimap/************************************************************/
map不允许插入相同的数据
multimap允许插入相同的数据


//map的本质
map是键值与实值关联的容器，里面存放的元素叫做对组，即pair。
pair本身就是一个模板类，pair有2个成员，分别叫做first和second。
map容器本质上就是成员为pair对象的容器，所以创建map容器时，必须与pair的模板类型保持一致。


//map的底层原理
map底层实现是红黑树，而C++11新增容器unordered_map与map用法基本一致，但底层是：哈希表。
红黑树是一种平衡二叉树，而平衡二叉树在二叉排序树基础上的，所以红黑树也就有排序的特性（unordered_map没有排序）。
可以做到在O(log n)时间内完成查找，插入和删除，在对单次时间敏感的场景下比较建议使用map做为容器。


//Map和Multimap的区别
Map													Multimap
每个键都是唯一的。										可以存储重复的键值对，键可能不唯一。
在map上使用count()函数只能返回两个值，即0或1。			在multimap上使用count()函数可以返回任何非负整数。
访问任何键的值很容易，直接可访问。						访问任何键的值并不容易，而且无法直接访问。
使用键删除时，在map中只会删除一个键值对。					使用键删除时，在multimap中将删除具有相同键的所有键值对。
当需要使用键作为查找表的唯一索引快速访问值时可以使用map。	当需要使用键对值进行分组时，可以使用multimap。


#include <map>
using namespace std;


//构造函数
map<int, char> M;						//无参构造
map<int, char> M2(M);					//拷贝构造
vector<pair<int, char>> V;				
map<int, char> M3(V.begin(), V.end());		//将区间内的元素拷贝给新容器

//iterators（迭代器）
begin			返回指向容器中第一个（经过排序后）键值对的双向迭代器。
end				返回指向容器最后一个元素（排序后）所在位置后一个位置的键值对的双向迭代器
rbegin			返回容器逆序的第一个键值对的双向迭代器
rend			返回容器逆序的最后一个元素的前一个位置的键值对双向迭代器
cbegin			和begin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
cend			和end()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crbegin			和rbegin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crend			和rend()功能相同，在其基础上增加了 const 属性，不能用于修改元素。

//capacity（容量）
size				返回存在键值对的个数
max_size			返回元素个数的最大值。这个值非常大，一般是2 ^ 32 - 1
empty			判断容器是否为空，为空返回true否则false

//Element access（元素访问）
operator[]		map容器重载了[] 运算符，只要知道 map 容器中某个键值对的键的值，就可以向获取数组中元素那样，通过键直接获取对应的值。
at				找到 map 容器中 key 键对应的值，如果找不到，该函数会引发 out_of_range 异常。

//Modifiers（修改器）
insert			向map中插入键值对
erase			删除map容器键值或者键值对
swap			交换2个map容器中的所有键值对
clear				清除map容器中的所有键值对
emplace			在当前 map 容器中的指定位置处构造新键值对。其效果和插入键值对一样，但效率更高。
emplace_hint		在本质上和 emplace() 在 map 容器中构造新键值对的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示键值对生成位置的迭代器，并作为该方法的第一个参数。

//Map operations
find				在 map 容器中查找键为 key 的键值对，如果成功找到，则返回指向该键值对的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
count			在当前 map 容器中，查找键为 key 的键值对的个数并返回。注意，由于 map 容器中各键值对的键的值是唯一的，因此该函数的返回值最大为 1。
lower_bound		返回一个指向当前 map 容器中第一个大于或等于 key 的键值对的双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
upper_bound		返回一个指向当前 map 容器中第一个大于 key 的键值对的迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
equal_range		该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的键为 key 的键值对（map 容器键值对唯一，因此该范围最多包含一个键值对）。
key_comp		返回一个键比较函数对象
value_comp		返回一个值比较函数对象
get_allocator		返回容器的内存分配器。



/********************/set / multiset/************************************************************/
set是集合，不允许重复数据。multiset是允许重复数据的集合。底层逻辑结构是二叉树。set是一个已排序的容器。
默认遍历方式是中序遍历，即从小到大输出。

#include <set>
using namespace std;


begin()			返回指向容器中第一个（注意，是已排好序的第一个）元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
end()			返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
rbegin()			返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。
rend()			返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的反向双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。
cbegin()			和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。
cend()			和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。
crbegin()			和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。
crend()			和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。
find(val)			在 set 容器中查找值为 val 的元素，如果成功找到，则返回指向该元素的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
lower_bound(val)	返回一个指向当前 set 容器中第一个大于或等于 val 的元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
upper_bound(val)	返回一个指向当前 set 容器中第一个大于 val 的元素的迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
equal_range(val)	该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的值为 val 的元素（set 容器中各个元素是唯一的，因此该范围最多包含一个元素）。
empty()			若容器为空，则返回 true；否则 false。
size()			返回当前 set 容器中存有元素的个数。
max_size()		返回 set 容器所能容纳元素的最大个数，不同的操作系统，其返回值亦不相同。
insert()			向 set 容器中插入元素。
erase()			删除 set 容器中存储的元素。
swap()			交换 2 个 set 容器中存储的所有元素。这意味着，操作的 2 个 set 容器的类型必须相同。
clear()			清空 set 容器中所有的元素，即令 set 容器的 size() 为 0。
emplace()			在当前 set 容器中的指定位置直接构造新元素。其效果和 insert() 一样，但效率更高。
emplace_hint()		在本质上和 emplace() 在 set 容器中构造新元素的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示新元素生成位置的迭代器，并作为该方法的第一个参数。
count(val)		在当前 set 容器中，查找值为 val 的元素的个数，并返回。注意，由于 set 容器中各元素的值是唯一的，因此该函数的返回值最大为 1。



/********************/栈容器 stack/************************************************************/
#include <stack>
using namespace std;


//构造函数
stack<int>S;					//无参构造
stack<int>S2(S1);				//拷贝构造

//赋值操作
stack & operator=(const stack & stk);//重载赋值运算符

//数据存取
push(elem);					//入栈，向栈顶添加元素
pop();						//出栈，删除栈顶元素
top();						//返回栈顶元素

//大小操作
empty();						//判断栈是否为空
size();						//返回栈的大小



/********************/队列容器 queue/************************************************************/
#include <queue>
using namespace std;


//构造函数
queue<int> Q;					//queue采用模板类实现，默认构造函数
queue<int> Q2(Q);				//拷贝构造

//赋值操作
queue & operator=(const queue & que);//重载赋值运算符

//数据存取：
push(elem);					//入队——往队尾添加元素
pop();						//出队——从队头删除元素
back();						//返回队尾元素
front();						//返回队头元素

//大小操作：
empty();						//判断队列是否为空
size();						//返回队列大小



/********************/双端队列容器 deque/************************************************************/
#include <deque>
using namespace std;


//构造函数
deque<int> D;						//无参构造
deque<int> D2(D);					//拷贝构造
deque<int> D3(D.begin(), D.end());	//将区间内的元素拷贝给新容器
deque<int> D4(n, elem);				//将n个元素拷贝给新容器
	

begin()						返回指向容器中第一个元素的迭代器。
end()						返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。
rbegin()						返回指向最后一个元素的迭代器。
rend()						返回指向第一个元素所在位置前一个位置的迭代器。
cbegin()						和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
cend()						和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crbegin()						和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crend()						和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
size()						返回实际元素个数。
max_size()					返回容器所能容纳元素个数的最大值。这通常是一个很大的值，一般是 232 - 1，我们很少会用到这个函数。
resize()						改变实际元素的个数。
empty()						判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。
shrink _to_fit()					将内存减少到等于当前元素实际所使用的大小。
at()							使用经过边界检查的索引访问元素。
front()						返回第一个元素的引用。
back()						返回最后一个元素的引用。
assign()						用新元素替换原有内容。
push_back()					在序列的尾部添加一个元素。
push_front()					在序列的头部添加一个元素。
pop_back()					移除容器尾部的元素。
pop_front()					移除容器头部的元素。
insert()						在指定的位置插入一个或多个元素。
erase()						移除一个元素或一段元素。
clear()						移出所有的元素，容器大小变为 0。
swap()						交换两个容器的所有元素。
emplace()						在指定的位置直接生成一个元素。
emplace_front()				在容器头部生成一个元素。和 push_front() 的区别是，该函数直接在容器头部构造元素，省去了复制移动元素的过程。
emplace_back()				在容器尾部生成一个元素。和 push_back() 的区别是，该函数直接在容器尾部构造元素，省去了复制移动元素的过程。



/********************/vector实例/************************************************************/
#include <iostream>
#include <vector> //添加容器头文件

using namespace std;

int main()
{
	//调用无参构造函数定义一个模板类
	vector <int>V;

	//在vector末尾添加元素
	V.push_back(10);
	V.push_back(20);
	V.push_back(30);
	V.push_back(40);

	/* 	//遍历
		for(int i=0;i<4;i++)
		{
			//cout << V[i] << "  ";		//运用下标运算符的重载
			cout << V.at(i) << "  ";	//运用成员函数 at()
		}
		cout << endl;
	*/

	//使用迭代器遍历 
	//V.begin()是容器中的第一个元素
	//V.end()是容器中最后一个元素的下一个单位
	for (vector<int>::iterator it = V.begin(); it != V.end(); it++)
		cout << *it << "  ";
	cout << endl;

	//删除元素--在末尾删除元素
	V.pop_back();

	//删除元素--删除第一个元素
	V.erase(V.begin());

	for (vector<int>::iterator it = V.begin(); it != V.end(); it++)
		cout << *it << "  ";
	cout << endl;

	cout << V.capacity() << endl;		//获取容器的容量
	cout << V.size() << endl;			//获取容器中的元素个数

	cout << "------------" << endl;
	V.push_back(77);
	V.push_back(88);
	V.push_back(99);
	cout << V.capacity() << endl;		//容器的容量，它不是固定不变的
	cout << V.size() << endl;

	int i = 0;
	int* ptr = &V[0];//获取首元素的地址
	for (i = 0; i < 1000; i++)
		V.push_back(i);

	if (ptr == &V[0])
		cout << "首地址没有改变" << endl;
	else
		cout << "容器的首地址发生了改变：当容量满的时候,vector会自动申请新的内存空间" << endl;

	cout << "---------------" << endl;
	V.clear();
	cout << V.capacity() << endl;
	cout << V.size() << endl;

	for (vector<int>::iterator it = V.begin(); it != V.end(); it++)
		cout << *it << "  ";
	cout << endl;

	cout << "---------------" << endl;

	if (V.empty())
		cout << "容器为空" << endl;
	else
		cout << "容器不为空" << endl;
}
