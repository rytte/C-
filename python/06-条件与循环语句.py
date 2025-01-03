('''********************'''if 语句'''************************************************************'''
 if 语句为条件判断语句，使用缩进来划分语句块，相同缩进数的语句在一起组成一个语句块，相当于C语言中同一个{}里的内容。
 一般形式如下所示：

if 条件1:
    #执行语句
elif 条件2:
    #执行语句
else:
    #执行语句
    
特别用法：执行语句 if 条件 else 执行语句


嵌套实例：

num=int(input("输入一个数字："))
if num%2==0:
    if num%3==0:
        print ("你输入的数字可以整除 2 和 3")
    else:
        print ("你输入的数字可以整除 2，但不能整除 3")
else:
    if num%3==0:
        print ("你输入的数字可以整除 3，但不能整除 2")
    else:
        print  ("你输入的数字不能整除 2 和 3")


条件表达式：
执行语句 if 条件1 else
执行语句 if 条件2 else
...


在 Python 中没有 switch...case 语句，但在 Python3.10 版本添加了 match...case，功能类似。
语法格式如下：

match subject:
    case <pattern_1>:
        <action_1>
    case <pattern_2>:
        <action_2>
    case <pattern_3>:
        <action_3>
    case _:
        <action_wildcard>

case _: 类似于 C 和 Java 中的 default:，当其他 case 都无法匹配时，匹配这条，保证永远会匹配成功。



'''********************'''while 语句'''************************************************************'''
 同样需要注意冒号和缩进。另外，在 Python 中没有 do..while 循环。

以下实例使用了 while 来计算 1 到 100 的总和：

sum = 0
counter = 1
while counter <= 100:
    sum = sum + counter
    counter += 1
 
print("1 到 100 之和为: %d" % (n,sum))
执行结果：1 到 100 之和为: 5050


while 可以配合 else 使用，如果 while 后面的条件语句为 false 时，则执行 else 的语句块。执行 else 语句意味着已经结束了循环，else 只会执行一次。

count = 0
while count < 3:
   print (count, " 小于 3")
   count = count + 1
else:
   print (count, " 大于或等于 3")
执行以上脚本，输出结果如下：

0  小于 5
1  小于 5
2  小于 5
3  大于或等于 3

类似 if 语句的语法，如果你的 while 循环体中只有一条语句，你可以将该语句与 while 写在同一行中
while 1:print("Hello,World!")



'''********************'''for 语句'''************************************************************'''
Python for 循环可以遍历任何可迭代对象，如一个列表或者一个字符串。每次执行后指向下一个元素。
如果在循环过程中遇到了 break 语句，则会中断循环，此时不会执行 else 子句。

for 元素 in 可迭代对象:                    #元素以变量形式表现
    #循环主体
else:
    #循环结束后执行的代码.

实例：
sites = ["Baidu", "Google","Runoob","Taobao"]
for site in sites:
    print(site)
以上代码执行输出结果为：

Baidu
Google
Runoob
Taobao


range() 函数
如
range(5)            生成0到4的数字序列
range(5,9)          生成5到8的数字序列
range(0, 10, 3)     生成0,3,6,9的数字序列。以指定数字开始并指定不同的增量（可以是负数，有时这也叫做'步长'）

len() 函数
返回变量的长度


您可以结合 range() 和 len() 函数以遍历一个序列的索引,如下所示:
>>>a = ['Google', 'Baidu', 'Runoob', 'Taobao', 'QQ']
for i in range(len(a)):
    print(i, a[i])

0 Google
1 Baidu
2 Runoob
3 Taobao
4 QQ

还可以使用 range() 函数来创建一个列表：
>>>list(range(5))
[0, 1, 2, 3, 4]



'''********************'''break,continue,pass 语句'''************************************************************'''
break 语句可以跳出 for 和 while 的循环体。如果你从 for 或 while 循环中终止，任何对应的循环 else 块将不执行。
continue 语句会跳过当前循环块中的剩余语句，然后进行下一轮循环。

pass 语句是空语句，是为了保持程序结构的完整性。
pass 不做任何事情，一般用做占位语句，如下实例

>>>while True:
    pass  # 等待键盘中断 (Ctrl+C)


