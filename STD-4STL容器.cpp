/********************/容器 Container/************************************************************/
容器本质上是一个模板类，可以存放任意数据类型。


//容器嵌套
类似于结构体嵌套结构体，类嵌套类，容器也可以嵌套容器。
vector <vector<int> > V;		//旧标准：定义容器嵌套容器时，> >运算符间要留有空格


//注意
1、容器类型为对象类型时，会在存入调用拷贝构造，创建新对象。
2、容器类型为对象指针时，会存放地址，不会调用拷贝构造，仍然指向原对象地址。
3、当容器嵌套容器的时候，注意大容器是调用了拷贝构造函数，与原来的小容器是不同的对象，两个容器的数据是不会同步的。


//数据结构查找效率
数据结构					底层实现					查找复杂度				适用场景
std::list				双向链表					O(n)					不适合高效查找
std::vector(未排序)		动态数组					O(n)					适用于少量数据，或者查找不频繁的情况
std::vector（排序后）	动态数组 + 二分查找		O(log n)				仅查找时可行，但插入删除慢
std::map				红黑树					O(log n)				需要 key - value 结构时
std::unordered_map		哈希表					O(1) 平均，O(n) 最坏		哈希查找最优，键值映射
std::set				红黑树					O(log n)				需要排序，查找较快，插入删除稳定
std::unordered_set		哈希表					O(1) 平均，O(n) 最坏		仅需查找，且数据无序时更快



/********************/通用方法/************************************************************/
//iterators（迭代器）
begin			返回指向容器中第一个元素的迭代器。
end				返回指向容器最后一个元素所在位置后一个位置的迭代器
rbegin			返回容器逆序的第一个元素的迭代器
rend			返回容器逆序的最后一个元素的前一个位置的迭代器
cbegin			和begin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
cend			和end()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crbegin			和rbegin()功能相同，在其基础上增加了 const 属性，不能用于修改元素。
crend			和rend()功能相同，在其基础上增加了 const 属性，不能用于修改元素。

//支持情况
容器类型				begin()	end()	rbegin()	rend()	cbegin()	cend()	crbegin()	crend()		返回迭代器类型
std::vector			✅		✅		✅			✅		✅			✅		✅			✅			随机访问迭代器
std::deque			✅		✅		✅			✅		✅			✅		✅			✅			随机访问迭代器
std::array			✅		✅		✅			✅		✅			✅		✅			✅			随机访问迭代器
std::list			✅		✅		✅			✅		✅			✅		✅			✅			双向迭代器
std::set			✅		✅		✅			✅		✅			✅		✅			✅			双向迭代器
std::map			✅		✅		✅			✅		✅			✅		✅			✅			双向迭代器
std::unordered_set	✅		✅		❌			❌		✅			✅		❌			❌			正向迭代器
std::unordered_map	✅		✅		❌			❌		✅			✅		❌			❌			正向迭代器
std::forward_list	✅		✅		❌			❌		✅			✅		❌			❌			正向迭代器
std::stack			❌		❌		❌			❌		❌			❌		❌			❌
std::queue			❌		❌		❌			❌		❌			❌		❌			❌
std::priority_queue	❌		❌		❌			❌		❌			❌		❌			❌
std::tuple			❌		❌		❌			❌		❌			❌		❌			❌

//容量操作
empty()			判断容器是否为空，为空返回 true 否则 false				//all
size()			返回实际元素的个数									//除forward_list
max_size()		返回元素个数的最大值。这个值非常大，一般是2 ^ 32 - 1	//除queue、stack
resize()		改变实际元素的个数，对应于size							//vector、deque、list、forward_list
clear()			清空容器												//除array、stack、queue、priority_queue

//元素访问
front()			返回第一个元素的引用				//vector、deque、array、list、forward_list
back()			返回最后一个元素的引用。			//vector、deque、array、list
data()			返回指向容器中第一个元素的指针		//vector、deque、array
operator[]		可以和数组一样用[]访问元素						//vector、deque、array、map、unordered_map
at()			obj.at(i)等同于obj[i]，访问数组下标的元素		//vector、deque、array、map、unordered_map

//元素操作
push_back()		在序列的尾部添加一个元素。
push_front()	在序列的头部添加一个元素。
pop_back()		移除容器尾部的元素。
pop_front()		移除容器头部的元素。

//支持情况（未提及的容器为都不支持）
容器类型				push_back	push_front	pop_back	pop_front
std::vector			✅			❌			✅			❌
std::deque			✅			✅			✅			✅
std::list			✅			✅			✅			✅
std::forward_list	❌			✅			❌			✅
std::array			❌			❌			❌			❌

//容器操作
swap()			交换两个容器的所有元素，需要容器类型一致		//all
assign()		替换所有元素									//vector、deque、list、forward_list
insert()		在容器指定位置插入元素						//除array、stack、queue、priority_queue
erase()			删除容器某个元素								//除array、stack、queue、priority_queue

//原地构造对象方法（C++11）（相比 insert / push_back 等方式，可以减少拷贝 / 移动构造，提高效率。）
emplace()		在指定位置原地构造一个元素（适用于容器中部或位置指定场合）
emplace_back()	在尾部原地构造元素（类似于 push_back）
emplace_front()	在头部原地构造元素（类似于 push_front）
emplace_hint()	在有 hint 的关联容器中原地构造（适用于 map、set 等）

//支持情况
容器类型					emplace		emplace_back	emplace_front	emplace_hint
std::vector				✅			✅				❌				❌
std::deque				✅			✅				✅				❌
std::list				✅			✅				✅				❌
std::forward_list		✅			❌				✅				❌
std::array				❌			❌				❌				❌
std::set				✅			❌				❌				✅
std::unordered_set		✅			❌				❌				✅
std::map				✅			❌				❌				✅
std::unordered_map		✅			❌				❌				✅
std::stack				❌			✅				❌				❌
std::queue				❌			✅				❌				❌
std::priority_queue		❌			✅				❌				❌



/********************/数组容器 vector/************************************************************/
vector是一个封装了动态大小数组的数组容器（Sequence Container），可以像数组一样使用下标运算符访问其中的元素。

1、内存扩展：push_back 时，如果超过当前容量，vector 通常会分配一个双倍大小的内存块，并将现有元素复制到新位置，然后加入新元素。
2、内存释放：当元素被删除时，vector 并不会立即释放其分配的内存，直到调用 shrink_to_fit()。


#include <vector>
using namespace std;

//构造函数
vector<int>V;						//无参构造
vector<int>V2(V);					//拷贝构造
vector<int>V3(V.begin(), V.end());	//将区间内的元素拷贝给新容器
vector<int>V4(n, elem);				//将n个元素拷贝给新容器

//方法
capacity			返回总共可以容纳的元素个数
reserve				增加容器的容量，控制vector的预留空间
shrink_to_fit		减少capacity到size的大小，即减小到size的大小
get_allocator		返回容器的内存分配器。



/********************/链表容器 list/************************************************************/
list是一个模板类，它的本质是一个可以存储任意数据的双向链表。

//📊 list vs vector 对比
特性						std::vector				std::list
底层结构					动态数组					双向链表
内存布局					连续内存					非连续内存
支持随机访问([], at)		✅ 是，效率高			❌ 不支持
插入删除效率（中间位置）	❌ 慢（需移动元素）		✅ 快（只需改指针）
尾部插入 / 删除			✅ 高效					✅ 高效
前端插入 / 删除			❌ 低效（需移动所有元素）	✅ 高效
遍历效率					✅ 更高，因缓存友好		❌ 稍慢，缓存命中率低
支持 resize()			✅ 支持					❌ 不支持
支持 assign()			✅ 支持					✅ 支持
支持 push_back()			✅ 支持					✅ 支持
支持 push_front()		❌ 不支持				✅ 支持
支持 insert()			✅ 支持（效率低）		✅ 支持（效率高）
支持 emplace() 系列		✅ 支持所有				✅ 支持所有
内存扩展策略				成倍增长，避免频繁拷贝	每次动态申请节点
使用场景					频繁随机访问、尾部操作多	频繁在中间或前端插入删除
内存占用					小（仅数据）				大（每个节点含指针）


#include <list>
using namespace std;

//构造函数
list<int> L;						 //无参构造
list<int> L2(L);				     //拷贝构造
list<int> L3(L.begin(), L.end());	 //将区间内的元素拷贝给新容器
list<int> L4(n, elem);				 //将n个元素拷贝给新容器

//方法
splice			将一个list容器中的元素插入另一个容器的指定位置
remove(val)		删除容器中所有值等于val的元素
remove_if		删除容器中满足某个条件的元素
unique			删除容器中相邻的重复元素，只保留一个
merge			合并两个实现已经排好序的list容器，并且合并后的list容器仍然是有序的
sort			将容器排序，通过更改容器中元素的位置
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
Map														Multimap
每个键都是唯一的。										可以存储重复的键值对，键可能不唯一。
在map上使用count()函数只能返回两个值，即0或1。				在multimap上使用count()函数可以返回任何非负整数。
访问任何键的值很容易，直接可访问。							访问任何键的值并不容易，而且无法直接访问。
使用键删除时，在map中只会删除一个键值对。					使用键删除时，在multimap中将删除具有相同键的所有键值对。
当需要使用键作为查找表的唯一索引快速访问值时可以使用map。	当需要使用键对值进行分组时，可以使用multimap。


#include <map>
using namespace std;


//构造函数
map<int, char> M;						//无参构造
map<int, char> M2(M);					//拷贝构造
vector<pair<int, char>> V;				
map<int, char> M3(V.begin(), V.end());		//将区间内的元素拷贝给新容器

//方法
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

//方法
find(val)			在 set 容器中查找值为 val 的元素，如果成功找到，则返回指向该元素的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
lower_bound(val)	返回一个指向当前 set 容器中第一个大于或等于 val 的元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
upper_bound(val)	返回一个指向当前 set 容器中第一个大于 val 的元素的迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
equal_range(val)	该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的值为 val 的元素（set 容器中各个元素是唯一的，因此该范围最多包含一个元素）。
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


/********************/双端队列容器 deque/************************************************************/
#include <deque>
using namespace std;


//构造函数
deque<int> D;						//无参构造
deque<int> D2(D);					//拷贝构造
deque<int> D3(D.begin(), D.end());	//将区间内的元素拷贝给新容器
deque<int> D4(n, elem);				//将n个元素拷贝给新容器
	
//方法
shrink_to_fit()					将内存减少到等于当前元素实际所使用的大小。



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
