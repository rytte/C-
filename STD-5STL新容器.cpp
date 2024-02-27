/********************/C++11容器/************************************************************/
std::array：固定大小的数组，支持随机访问迭代器。它比C风格的数组更安全，因为它会进行边界检查，并且它支持更多的功能，如成员函数fill()和swap()。
std::forward_list：单向链表，只支持前向迭代器。它提供了比传统链表更高效的插入和删除操作。
std::unordered_map 和 std::unordered_multimap：哈希表实现的关联容器，支持键值对的快速查找、插入和删除。与std::map相比，它们通常具有更快的查找速度，但不保证元素的排序。
std::unordered_set 和 std::unordered_multiset：哈希表实现的集合容器，支持快速查找、插入和删除元素。与std::set相比，它们通常具有更快的查找速度，但不保证元素的排序。



/********************/数组容器 array/************************************************************/
std::array是具有固定大小的数组。因此，它并不支持添加或删除元素等改变大小的操作。也就是说，当定义一个array时，除了指定元素类型，还要指定容器大小。
std::array除了有内置数组支持随机访问、效率高、存储大小固定等特点外，还支持迭代器访问、获取容量、获得原始指针等高级功能。
# include <array>




begin()				返回指向容器中第一个元素的随机访问迭代器。
end()				返回指向容器最后一个元素之后一个位置的随机访问迭代器，通常和 begin() 结合使用。
rbegin()				返回指向最后一个元素的随机访问迭代器。
rend()				返回指向第一个元素之前一个位置的随机访问迭代器。
cbegin()				和 begin() 功能相同，只不过在其基础上增加了 const 属性，不能用于修改元素。
cend()				和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crbegin()				和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
crend()				和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
size()				返回容器中当前元素的数量，其值始终等于初始化 array 类的第二个模板参数 N。
max_size()			返回容器可容纳元素的最大数量，其值始终等于初始化 array 类的第二个模板参数 N。
empty()				判断容器是否为空，和通过 size() == 0 的判断条件功能相同，但其效率可能更快。
at(n)					返回容器中 n 位置处元素的引用，该函数自动检查 n 是否在有效的范围内，如果不是则抛出 out_of_range 异常。
front()				返回容器中第一个元素的直接引用，该函数不适用于空的 array 容器。
back()				返回容器中最后一个元素的直接应用，该函数同样不适用于空的 array 容器。
data()				返回一个指向容器首个元素的指针。利用该指针，可实现复制容器中所有元素等类似功能。
fill(val)				将 val 这个值赋值给容器中的每个元素。
array1.swap(array2)		交换 array1 和 array2 容器中的所有元素，但前提是它们具有相同的长度和类型。



/********************/单向链表 forward_list/************************************************************/

before_begin()			返回一个前向迭代器，其指向容器中第一个元素之前的位置。
begin()				返回一个前向迭代器，其指向容器中第一个元素的位置。
end()				返回一个前向迭代器，其指向容器中最后一个元素之后的位置。
cbefore_begin()		和 before_begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
cbegin()				和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
cend()				和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
empty()				判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。
max_size()			返回容器所能包含元素个数的最大值。这通常是一个很大的值，一般是 232 - 1，所以我们很少会用到这个函数。
front()				返回第一个元素的引用。
assign()				用新元素替换容器中原有内容。
push_front()			在容器头部插入一个元素。
emplace_front()		在容器头部生成一个元素。该函数和 push_front() 的功能相同，但效率更高。
pop_front()			删除容器头部的一个元素。
emplace_after()		在指定位置之后插入一个新元素，并返回一个指向新元素的迭代器。和 insert_after() 的功能相同，但效率更高。
insert_after()			在指定位置之后插入一个新元素，并返回一个指向新元素的迭代器。
erase_after()			删除容器中某个指定位置或区域内的所有元素。
swap()				交换两个容器中的元素，必须保证这两个容器中存储的元素类型是相同的。
resize()				调整容器的大小。
clear()				删除容器存储的所有元素。
splice_after()			将某个 forward_list 容器中指定位置或区域内的元素插入到另一个容器的指定位置之后。
remove(val)			删除容器中所有等于 val 的元素。
remove_if()			删除容器中满足条件的元素。
unique()				删除容器中相邻的重复元素，只保留一个。
merge()				合并两个事先已排好序的 forward_list 容器，并且合并之后的 forward_list 容器依然是有序的。
sort()				通过更改容器中元素的位置，将它们进行排序。
reverse()				反转容器中元素的顺序。



/********************/unordered_map / unordered_multimap/************************************************************/

begin()				返回指向容器中第一个键值对的正向迭代器。
end() 				返回指向容器中最后一个键值对之后位置的正向迭代器。
cbegin()				和 begin() 功能相同，只不过在其基础上增加了 const 属性，即该方法返回的迭代器不能用于修改容器内存储的键值对。
cend()				和 end() 功能相同，只不过在其基础上，增加了 const 属性，即该方法返回的迭代器不能用于修改容器内存储的键值对。
empty()				若容器为空，则返回 true；否则 false。
size()				返回当前容器中存有键值对的个数。
max_size()			返回容器所能容纳键值对的最大个数，不同的操作系统，其返回值亦不相同。
operator[key]			该模板类中重载了[] 运算符，其功能是可以向访问数组中元素那样，只要给定某个键值对的键 key，就可以获取该键对应的值。注意，如果当前容器中没有以 key 为键的键值对，则其会使用该键向当前容器中插入一个新键值对。
at(key)				返回容器中存储的键 key 对应的值，如果 key 不存在，则会抛出 out_of_range 异常。
find(key)				查找以 key 为键的键值对，如果找到，则返回一个指向该键值对的正向迭代器；反之，则返回一个指向容器中最后一个键值对之后位置的迭代器（如果 end() 方法返回的迭代器）。
count(key)			在容器中查找以 key 键的键值对的个数。
equal_range(key)		返回一个 pair 对象，其包含 2 个迭代器，用于表明当前容器中键为 key 的键值对所在的范围。
emplace()				向容器中添加新键值对，效率比 insert() 方法高。
emplace_hint()			向容器中添加新键值对，效率比 insert() 方法高。
insert() 				向容器中添加新键值对。
erase()				删除指定键值对。
clear() 				清空容器，即删除容器中存储的所有键值对。
swap()				交换 2 个 unordered_map 容器存储的键值对，前提是必须保证这 2 个容器的类型完全相等。
bucket_count()			返回当前容器底层存储键值对时，使用桶（一个线性链表代表一个桶）的数量。
max_bucket_count()	返回当前系统中，unordered_map 容器底层最多可以使用多少桶。
bucket_size(n)			返回第 n 个桶中存储键值对的数量。
bucket(key)			返回以 key 为键的键值对所在桶的编号。
load_factor()			返回 unordered_map 容器中当前的负载因子。负载因子，指的是的当前容器中存储键值对的数量（size()）和使用桶数（bucket_count()）的比值，即 load_factor() = size() / bucket_count()。
max_load_factor()		返回或者设置当前 unordered_map 容器的负载因子。
rehash(n)				将当前容器底层使用桶的数量设置为 n。
reserve()				将存储桶的数量（也就是 bucket_count() 方法的返回值）设置为至少容纳count个元（不超过最大负载因子）所需的数量，并重新整理容器。
hash_function()		返回当前容器使用的哈希函数对象。



/********************/unordered_set / unordered_multiset/************************************************************/

begin()				返回指向容器中第一个元素的正向迭代器。
end();				返回指向容器中最后一个元素之后位置的正向迭代器。
cbegin()				和 begin() 功能相同，只不过其返回的是 const 类型的正向迭代器。
cend()				和 end() 功能相同，只不过其返回的是 const 类型的正向迭代器。
empty()				若容器为空，则返回 true；否则 false。
size()				返回当前容器中存有元素的个数。
max_size()			返回容器所能容纳元素的最大个数，不同的操作系统，其返回值亦不相同。
find(key)				查找以值为 key 的元素，如果找到，则返回一个指向该元素的正向迭代器；反之，则返回一个指向容器中最后一个元素之后位置的迭代器（如果 end() 方法返回的迭代器）。
count(key)			在容器中查找值为 key 的元素的个数。
equal_range(key)		返回一个 pair 对象，其包含 2 个迭代器，用于表明当前容器中值为 key 的元素所在的范围。
emplace()				向容器中添加新元素，效率比 insert() 方法高。
emplace_hint()			向容器中添加新元素，效率比 insert() 方法高。
insert()				向容器中添加新元素。
erase()				删除指定元素。
clear()				清空容器，即删除容器中存储的所有元素。
swap()				交换 2 个 unordered_set 容器存储的元素，前提是必须保证这 2 个容器的类型完全相等。
bucket_count()			返回当前容器底层存储元素时，使用桶（一个线性链表代表一个桶）的数量。
max_bucket_count()	返回当前系统中，unordered_set 容器底层最多可以使用多少桶。
bucket_size(n)			返回第 n 个桶中存储元素的数量。
bucket(key)			返回值为 key 的元素所在桶的编号。
load_factor()			返回 unordered_set 容器中当前的负载因子。负载因子，指的是的当前容器中存储元素的数量（size()）和使用桶数（bucket_count()）的比值，即 load_factor() = size() / bucket_count()。
max_load_factor()		返回或者设置当前 unordered_set 容器的负载因子。
rehash(n)				将当前容器底层使用桶的数量设置为 n。
reserve()				将存储桶的数量（也就是 bucket_count() 方法的返回值）设置为至少容纳 count 个元（不超过最大负载因子）所需的数量，并重新整理容器。
hash_function()		返回当前容器使用的哈希函数对象。



/********************/元组 tuple/************************************************************/

tup1.swap(tup2)
swap(tup1, tup2)			tup1 和 tup2 表示类型相同的两个 tuple 对象，tuple 模板类中定义有一个 swap() 成员函数，<tuple> 头文件还提供了一个同名的 swap() 全局函数。
swap()					函数的功能是交换两个 tuple 对象存储的内容。
get<num>(tup)			tup 表示某个 tuple 对象，num 是一个整数，get() 是 <tuple> 头文件提供的全局函数，功能是返回 tup 对象中第 num + 1 个元素。
tuple_size<type>::value		tuple_size 是定义在 <tuple> 头文件的类模板，它只有一个成员变量 value，功能是获取某个 tuple 对象中元素的个数，type 为该tuple 对象的类型。
tuple_element<I, type>::type	tuple_element 是定义在 <tuple> 头文件的类模板，它只有一个成员变量 type，功能是获取某个 tuple 对象第 I + 1 个元素的类型。
forward_as_tuple<args...>	args... 表示 tuple 对象存储的多个元素，该函数的功能是创建一个 tuple 对象，内部存储的 args... 元素都是右值引用形式的。
tie(args...) = tup			tup 表示某个 tuple 对象，tie() 是 <tuple> 头文件提供的，功能是将 tup 内存储的元素逐一赋值给 args... 指定的左值变量。
tuple_cat(args...)			args... 表示多个 tuple 对象，该函数是 <tuple> 头文件提供的，功能是创建一个 tuple 对象，此对象包含 args... 指定的所有 tuple 对象内的元素。



//结构化绑定（C++17）
1、返回多个值（元组）
auto return_multiple_values()
{
	return std::make_tuple(11, 7);
}

int main()
{
	auto [x, y] = return_multiple_values();
	std::cout << "x=" << x << "y=" << y << std::endl;
}

2、绑定到结构体
3、绑定到元组和类元组对象



/********************/其它/************************************************************/
C++17新的容器类（如string_view和optional）、新的算法（如transform_reduce和clamp）、文件系统库等。
C++20新的容器类（如span和bitset）、新的算法（如std::ranges中的算法）、日期和时间库等。



/********************/std::initializer_list/************************************************************/
https://zhuanlan.zhihu.com/p/354588791