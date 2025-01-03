('''********************'''字典（dict）'''************************************************************'''
字典（dict）是另一种可变容器模型，且可存储任意类型对象。

字典是一种映射类型，它的每个键值 key=>value 对用冒号 : 分割，每个对之间用逗号(,)分割，整个字典包括在花括号 {} 中 ,格式如下所示：
d = {key1:value1, key2:value2, key3:value3 }

#增加键值对
d[key4]=value4
#修改键值对
d[key2]=value5
#删除键值对
del d[key3]
#查询键值对
d[key1]

#字典嵌套
>>>d = {'花木兰':{'语文':90, '数学':100}, '李白':{'语文':120, '数学':70}}
>>>d[花木兰][语文]
90


列表是有序的对象集合，字典是无序的对象集合。两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
另外，字典类型也有一些内置的函数，例如 clear()、keys()、values() 等。

注意：
1、字典是一种映射类型，它的元素是键值对。
2、在同一个字典中，键(key)必须是唯一的，且是不可变类型，如数字、字符串、元组。
3、一个键(key)只能对应一个值(value)，如果对一个键多次赋值，则会覆盖，只保留最后一次赋值结果。
4、创建空字典使用 { }。
5、字典可以嵌套，即某个键的值可以是另一个字典。
6、字典推导式，与列表推导式基本相同，只是将[]改为{}。

创建字典
dict1 = { "one":1, "two":2 }                #使用{}创建字典
dict2 = dict(one=1, two=2)                  #使用dict()函数创建字典,注意键key不能加引号
dict3 = dict([("one",1), ("two", 2)])       #使用列表作为参数，列表中的每个元素都是组成键值对的元组。
dict4 = dict({ "one":1, "two":2 })          #将{}创建的字典形式作为dict()函数的参数
dict5 = dict({ "one":1},two=2)              #方法2和方法4的结合
dict6 = dict(zip(["one","two"], [1,2]))     #以zip()返回的迭代器作为参数


序号	内置方法

1	    dict.clear()                删除字典内所有元素

2	    dict.copy()                 返回一个字典的浅复制

3	    dict.fromkeys(seq, val)     创建一个新字典，以序列seq中元素作为键，val作为所有键对应的初始值。适用于快速创建一个所有键的值都相同的字典。
>>>d = dict.fromkeys("Fish", 250)
>>>d
{'F':250, 'i':250, 's':250, 'h':250}

4	    key in dict                 如果键在字典dict里返回true，否则返回false

5	    dict.get(key, default=None)         返回指定键的值，如果键不在字典中返回 default 设置的默认值

6	    dict.setdefault(key, default=None)  和get()类似, 但如果键不存在于字典中，将会添加键并将值设为default

#视图对象即字典的动态视图，当字典内容发生变化时，视图对象的内容也会相应改变。
7	    dict.items()                以列表返回一个视图对象     键值对

8	    dict.keys()                 返回一个视图对象            键

9	    dict.values()               返回一个视图对象            值
>>>d = { "one":1, "two":2 }
>>>i = d.items()
>>>k = d.keys()
>>>v = d.values()
>>>i
dict_items([('one', 1), ('two', 2)])
>>>k
dict_keys(['one', 'two'])
>>>v
dict_values([1, 2])
#修改字典，视图对象内容也发生改变
>>>d["one"]=5
>>>i
>>>dict_items([('one', 5), ('two', 2)])

10	    dict.update(dict2)          把字典dict2的键值对更新（即添加或修改）到dict里

11	    dict.pop(key[,default])     返回并删除字典 key（键）所对应的值。default:找不到指定键时返回的参数。

12	    dict.popitem()              返回并删除字典中的最后一对键和值。

13      len(dict)                   返回键值对数量

14      reversed(dict)              返回反转后的迭代器，Python3.8之后字典是有序的，因此仅适用于3.8之后的版本。



'''********************'''集合（set）'''************************************************************'''
集合（set）是一个无序的不重复元素序列，构成集合的事物或对象称作元素或是成员。


与数学中的集合相同，集合具有以下三个基本性质

（1）确定性：即哪些元素是属于这个集合的，那些元素不属于这个集合是明确的。
（2）无序性：元素之间是没有顺序的
（3）互异性：集合中的元素互不相同


注意：
1、创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
2、集合推导式，与字典推导式基本相同。
3、集合运算符两边必须都是集合，而方法的参数可以是任何可迭代对象


#集合的创建
set1 = {元素1, 元素2, 元素3}
set2 = set(元素1, 元素2, 元素3)
set3 = frozenset(元素1, 元素2, 元素3)      #创建不可变集合

#集合运算符
>>>s = set("FishC")
>>>s <= set("FishC")        #判断子集
True
>>>s < set("FishC")         #判断真子集(是子集但不能相等)
False
>>>s >= set("FishC")        #判断超集
True
>>>s > set("FishC")         #判断真超集
False

>>>s | {1, 2, 3}            #并集
{'F', 1, 2, 'h', 3, 'i', 's', 'C'}
>>>s & set("Python")        #交集
{'h'}
>>>s - set("Python")        #差集
{'s', 'F', 'C', 'i'}
>>>s ^ set("Python")
{'t', 'o', 'y', 'C', 'P', 'F', 'i', 's', 'n'}   #对称差集（两个集合中不重复的元素集合）

#查重去重
使用 len() 和 set() 函数查重
>>>s = [1, 1, 2, 3, 5]
>>>len(s) == len(set(s))
False

使用 set() 函数去重
>>>set(s)
{1, 2, 3, 5}


序号    内置方法                        #elem支持单参数，others支持多参数，set2支持多参数

1       set.add(elem)	                给集合添加元素，将整个参数作为一个元素添加，不支持多参数
2       set.update(others)	            给集合添加元素，将参数中的每一个元素逐个添加，支持多参数

3       set.copy()	                    浅拷贝一个集合

4       set.clear()	                    移除所有元素
5       set.discard(elem)	            移除指定元素，若不存在则静默处理
6       set.remove(elem)	            移除指定元素，若不存在则抛出异常
7       set.pop()	                    随机返回并移除元素（实际上是弹出随机存放后的顺序的首个元素）

8       set.isdisjoint(set2)	        判断两个集合(set与set2)是否不包含相同的元素，是则返回 True，否则返回 False。
9       set.issubset(set2)	            判断指定集合set是否为参数集合set2的子集。
10      set.issuperset(set2)	        判断指定集合set是否为参数集合set2的超集。

11      set.difference(set2)	        返回差集，即set中存在而set2中不存在的元素
12      set.difference_update(set2)	    set更新为两个集合的差集

13      set.intersection(set2)	        返回交集
14      set.intersection_update(set2)	set更新为两个集合的交集

15      set.symmetric_difference(set2)	        返回对称差集，即两个集合(set和set2)中不重复的元素集合。
16      set.symmetric_difference_update(set2)	set更新为两个集合的对称差集

17      set.union(set2)	                返回并集        #set更新为两个集合并集的方法就是 set.update(*others)

