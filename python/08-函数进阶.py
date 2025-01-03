('''********************'''闭包'''************************************************************'''
外层函数返回内层函数的应用

步骤
（1）利用嵌套函数的外层作用域具有记忆能力的特性，让数据保存在外层函数的参数或者变量中
（2）将内层函数作为返回值返回，就可以从外部间接调用到内层的函数

推导
#通过函数A返回内层函数，将整个函数返回
>>>def funA():
   x = 880
   def funB():
       print(x)
   return funB()        #返回的函数带括号

>>>funA()
880

#通过函数A返回内层函数，将整个函数返回
>>>def funA():
  x = 880
  def funB():
      print(x)
  return funB              #返回的函数不带括号

>>>funA()
<function funA.<locals>.funB at 0x00000187420225C0>
>>>funA()()
880
#使用新变量将返回的函数名继承
>>>func = funA()
>>>func()
880

#由以上原理，可以使用同样的代码来创建多个匿名函数，类似于纯虚函数。
>>>def power(exp):
   def exp_of(base):
       return base ** exp
   return exp_of

>>>square = power(2)
>>>cube = power(3)
>>>square(3)
8
>>>cube(4)
64

#进一步应用，配合nonlocal关键字，实现近似类的结构功能
>>>def outer():
   x = 0
   y = 0
   def inner(x1, y1):
       nonlocal x, y
       x += x1
       y += y1
       print(f"现在，x = {x}，y = {y}")
   return inner

>>>move = outer()
>>>move(1, 2)
现在，x = 1，y = 2
>>>move(3, 5)
现在，x = 4，y = 7



'''********************'''装饰器'''************************************************************'''
将函数作为参数传入其它函数调用结合闭包的应用

>>>def run(func):
   def call_func():
       print("开始运行程序...")
       func()
       print("结束程序运行...")
   return call_func

>>>def myfunc():
   print("I Love Python.")

>>>myfunc = run(myfunc)
>>>myfunc()
开始运行程序...
I Love Python.
结束程序运行...

#语法糖
>>>def run(func):
  def call_func():
      print("开始运行程序...")
      func()
      print("结束程序运行...")
  return call_func

>>>@run
...def myfunc():
  print("I Love Python.")

>>>myfunc()
开始运行程序...
I Love Python.
结束程序运行...

#同时使用多个装饰器
>>>def add(func):
   def inner():
       x = func()
       return x + 1
   return inner

>>>def cube(func):
   def inner():
       x = func()
       return x * x * x
   return inner

>>>def square(func):
   def inner():
       x = func()
       return x * x
   return inner

>>>@add
...@cube
...@square
...def test()           #自下而上调用，相当于test = square(test) -> test = cube(test) -> test = add(test)
   return 2

>>>test()
65

#带有参数的装饰器
>>>def logger(msg)
   def run(func):
       def call_func():
           func()
           print(f"[{msg}]调用完成...")
       return call_func
   return run

>>>@logger(msg="A")                     #相当于 funA = longger(msg="A")(funA)
...def funA():
   print("正在调用funA...")

>>>@logger(msg="B")                     #相当于 funB = longger(msg="B")(funB)
...def funB():
   print("正在调用funB...")

>>>funA()
正在调用funA...
[A]调用完成...
>>>funB()
正在调用funB...
[B]调用完成...



'''********************'''lambda表达式（匿名函数）'''************************************************************'''
Python 使用 lambda 关键字来创建匿名函数。
所谓匿名，意即不再使用 def 语句这样标准的形式定义一个函数。
意在使用简单的代码实现一些较为简单的功能。

lambda 参数列表:表达式

>>>x = lambda a,b : a + b
>>>x(5, 10)
15


lambda 的主体是一个表达式，而不是一个代码块，因此仅仅能在 lambda 表达式中封装有限的逻辑进去，完成较为简单的需求。
同时，由于 lambda 是一个表达式，也就意味着可以存在于列表等普通函数无法存在的地方。
>>>y = [lambda x : x * x, 2, 3]
>>>y[0](y[1])
4


注意：
1、lambda 函数拥有自己的命名空间，且不能访问自己参数列表之外或全局命名空间里的参数。
2、虽然 lambda 函数看起来只能写一行，却不等同于 C 或 C++ 的内联函数，后者的目的是调用小函数时不占用栈内存从而增加运行效率。


#闭包
我们可以将匿名函数封装在一个函数内，这样可以使用同样的代码来创建多个匿名函数，类似于纯虚函数。

>>>def func(n):
   return lambda a : a * n

>>>func2 = func(2)
>>>func3 = func(3)
>>>func2(11)
22
>>>func3(11)
33



'''********************'''递归'''************************************************************'''
递归的缺点
1、递归通常会出现许多重复计算，导致时间复杂度高。
2、调用栈可能会溢出，每一次函数调用会在内存栈中分配空间，当调用的层次太多时，就会超导致栈溢出。

#计算阶层
>>>def factRecur(n):
   if n == 1:
       return 1
   else:
       return n * factRecur(n-1)

>>>factRecur(5)
120
>>>factRecur(10)
3628800

#斐波那契数列
>>>def fibRecur(n):
   if n == 1 or n == 2:
       return 1
   else:
       return fibRecur(n-1) + fibRecur(n-2)

>>>fibRecur(12)
144

#汉诺塔
def hanoi(n, x, y, z):
    if n == 1:
        print(x, '-->', z)
    else:
        hanoi(n-1, x, z, y)
        print(x, '-->', z)
        hanoi(n-1, y, x, z)

n = int(input('请输入汉诺塔的层数：'))
hanoi(n, 'A', 'B', 'C')



'''********************'''高阶函数'''************************************************************'''
拥有函数类型参数的函数是高阶函数，如装饰器、map()函数、filter()函数等。

偏函数：偏函数是指对指定的函数进行二次包装，本质是闭包。
>>>import functools
>>>square = functools.partial(pow, exp=2)
>>>square(3)
9
>>>cube = functools.partial(pow, exp=3)
>>>cube(3)
27

@functool.wraps(函数名)
在装饰器中调用运行函数的函数上加上此声明，将使函数主体变为运行函数，否则主体将是调用函数，影响__name__、__doc__等函数方法的使用。

