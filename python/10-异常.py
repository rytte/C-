('''********************'''错误和异常'''************************************************************'''
Python 有两种错误很容易辨认：语法错误和异常。

语法错误：语法分析器指出了出错的一行，并且在最先找到的错误的位置标记了一个小小的箭头。
异常：即便 Python 程序的语法是正确的，在运行它的时候，也有可能发生错误。运行期检测到的错误被称为异常。



'''********************'''assert 语句'''************************************************************'''
Python assert（断言）用于判断一个表达式，在表达式条件为 False 的时候触发 AssertionError 异常。

assert 表达式 [, 返回的内容]

assert 语句可以用于检测错误。
>>>s = "FishC"
>>>assert s == "FishC"              #表达式正确，无事发生
>>>assert s == "Sheep"              #表达式错误，抛出 AssertionError 异常
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AssertionError



'''********************'''异常处理'''************************************************************'''
异常捕捉可以使用 try/except 语句。

语法格式：
try:
    检测语句
except [expression [as reason]]     #expression:异常名称     identifier:自定义变量，用于提取异常的原因
    异常处理代码

>>>try:
...    1 / 0
...except ZeroDivisionError as e:
...    print(e)
...
division by zero

try 语句按照如下方式工作：
1、首先，执行 try 子句，如果没有异常发生，则 try 子句执行后跳过 except 子句结束。
2、如果在执行 try 子句的过程中发生了异常，那么 try 子句余下的部分将被忽略，进行 except 的异常匹配。
3、如果异常的类型和 except 之后的名称相符，那么对应的 except 子句将被执行。
4、如果一个异常没有与任何的 except 匹配，那么这个异常将会传递给上层的 try 中。

一个 try 语句可能包含多个 except 子句，分别来处理不同的特定的异常，但只有一个分支会被执行。
一个 except 子句可以同时处理多个异常，这些异常将被放在一个括号里成为一个元组，例如:
except (RuntimeError, TypeError, NameError):
    pass

也可以使用多个 except 语句对不同的异常进行不同的处理。
except 若不指定异常的名称，它将可以接收所有的异常。你可以使用这种方法打印一个错误信息，然后再次把异常抛出。


异常处理并不仅仅处理那些直接发生在 try 子句中的异常，而且还能处理子句中调用的函数（甚至间接调用的函数）里抛出的异常。
def this_fails():
    x = 1/0
   
try:
    this_fails()
except ZeroDivisionError as err:
    print('Handling run-time error:', err)

Handling run-time error: int division or modulo by zero


'''************************************************************'''
可选子句
else 子句放在所有的 except 子句之后，将在 try 子句没有发生任何异常的时候执行。
finally 子句放在所有的子句后面，无论是否发生异常都将执行最后的代码。

#如果正常打开文件并写入则执行 else 部分的语句，否则打印出错，不管是否成功写入都关闭文件
try:
    f = open("FishC.txt", 'w')
    f.write("Hello World!")
except:
    print("出错了！")
else:
    print("写入完成！")
finally:
    f.close()


try-finally 语句
只有 try 和 finally 语句的结构，它定义了无论在任何情况下都会执行的清理行为。
如果一个异常被抛出，而又没有任何的 except 把它截住，那么这个异常会在 finally 子句执行后抛出。

>>>try:
...    raise KeyboardInterrupt
...finally:
...    print("Hello!")
...
Hello!
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
KeyboardInterrupt



'''************************************************************'''
异常嵌套
>>>try:
...    try:
...        520 + "FishC"
...    except:
...        print("内部异常！")
...    1 / 0
...except:
...    print("外部异常！")
...finally:
...    print("收尾工作~")
...
内部异常！
外部异常！
收尾工作~


'''********************'''抛出异常'''************************************************************'''
Python 使用 raise 语句抛出一个指定的异常，该异常必须是一个异常的实例或者是异常的类（也就是 Exception 的子类）。

raise [异常名(返回内容)][from 异常名]

>>>x = 10
>>>if x > 5:
...    raise Exception('x 不能大于 5')
...
Traceback (most recent call last):
  File "test.py", line 3, in <module>
    raise Exception('x 不能大于 5。x 的值为: {}'.format(x))
Exception: x 不能大于 5


如果你只想知道这是否抛出了一个异常，并不想去处理它，那么一个简单的 raise 语句就可以再次把它抛出。
>>>try:
...    raise NameError('HiThere')  # 模拟一个异常。
...except NameError:
...    print('An exception flew by!')
...    raise
...   
An exception flew by!
Traceback (most recent call last):
  File "<stdin>", line 2, in ?
NameError: HiThere


try/except 语句和 raise 语句结合可以达到Python中所没有的 goto 语句的效果。
>>>try:
...    while True:
...        for i in range(10):
...            if(i > 3):
...                raise
...            print(i)
...        print("被跳过")
...    print("被跳过")
...except:
...    print("goto 目的地")
...
0
1
2
3
goto 目的地



'''********************'''用户自定义异常'''************************************************************'''
你可以通过创建一个新的异常类来拥有自己的异常。异常类继承自 Exception 类，可以直接继承，或者间接继承，例如:

class MyError(Exception):
        def __init__(self, value):
            self.value = value
        def __str__(self):
            return repr(self.value)
   
try:
        raise MyError(2*2)
    except MyError as e:
        print('My exception occurred, value:', e.value)
   
My exception occurred, value: 4
raise MyError('oops!')
Traceback (most recent call last):
  File "<stdin>", line 1, in ?
__main__.MyError: 'oops!'
在这个例子中，类 Exception 默认的 __init__() 被覆盖。

当创建一个模块有可能抛出多种不同的异常时，一种通常的做法是为这个包建立一个基础异常类，然后基于这个基础类为不同的错误情况创建不同的子类:

class Error(Exception):
    """Base class for exceptions in this module."""
    pass

class InputError(Error):
    """Exception raised for errors in the input.

    Attributes:
        expression -- input expression in which the error occurred
        message -- explanation of the error
    """

    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

class TransitionError(Error):
    """Raised when an operation attempts a state transition that's not
    allowed.

    Attributes:
        previous -- state at beginning of transition
        next -- attempted new state
        message -- explanation of why the specific transition is not allowed
    """

    def __init__(self, previous, next, message):
        self.previous = previous
        self.next = next
        self.message = message
大多数的异常的名字都以"Error"结尾，就跟标准的异常命名一样。





