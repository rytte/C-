('''********************'''类和对象'''************************************************************'''
 Python中的类提供了面向对象编程的所有基本功能：类的继承机制允许多个基类，派生类可以覆盖基类中的任何方法，方法中可以调用基类中的同名方法。

类定义：class 关键字

class Turtle:                   #类名通常首字母大写
    head = 1                    #类的属性在定义时初始化
    eyes = 2
    legs = 4

    def eat(self):              
        print("开饭开饭！")                 

    def sleep(self):
        print("Zzzz...")


t = Turtle()            #实例化

t.mouth = 1             #对象中可以动态添加属性

dir(t)                  #查看对象的属性和方法，列出内置方法

t.__dict__              #查看对象的属性和方法，属性以字典形式列出，不列出内置方法。

t.__dict__[ears] = 2    #__dict__方法还可以用于动态添加属性


'''************************************************************'''
类与对象的独立性
#不同于C++，Python中的类本身也是占用内存的一个对象，其属性赋了初值。可以直接调用类的属性和方法。
>>>class A:
   x = 520 

>>>A.__dict__
mappingproxy({'__module__': '__main__', 'x': 520, '__dict__': <attribute '__dict__' of 'A' objects>, '__weakref__': <attribute '__weakref__' of 'A' objects>, '__doc__': None})
>>>A.x
520
#在实例化对象时，新对象不具有自己的属性和方法，但可以默认调用所属类的属性和方法
>>>a = A()
>>>a.__dict__
{}
>>>dir(a)
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'x']
>>>a.x              #此时为调用所属类的属性
520
>>>a.__dict__       #本身还是不具有属性
{}
>>>A.x = 150        #修改类的属性，其对象调用此属性时值也会发生变化
>>>a.x
150
>>>a.x = 20         #创建同名属性x，也就是新建了一个同名局部变量，会进行覆盖。将不再调用类中的属性x了。


将类作为字典使用，非常方便
>>>class D:
   pass

>>>d = D()
>>>d.x = 520
>>>d.y = "小甲鱼"
>>>d.z = [1, 2, 3]
>>>d.x 
520



'''********************'''self'''************************************************************'''
#self作用相当于this指针，只是this指针是默认传入的不需要写出来。
#self就是实例化对象本身，而使用方法时都是调用类的方法，因此使用公有的方法修改自己的属性需要传入自己的指针。
#self不是关键字，换成其它自定义的名字也可以。

>>>class E:
   def change(self, n):
       self.x = n

>>>e = E()
>>>e.change(20)     #此处默认传入形参self，也就是对象e本身。相当于e.change(e, 20)
>>>e.__dict__       #e为自己创建了一个变量x，E不受影响。
{'x': 20}
>>>E.change(E, 10)  #当类调用此函数时，需要指定传入的self对象。
>>>E.change(e, 30)


>>>class F:
   x = 100
   def change(self, n):
       x = n                #当方法中的变量不指定对象时(如 使用self修饰)，为x赋值只是创建了一个局部变量x，函数结束后就释放了。

>>>f = F()
>>>f.change(50)     
>>>f.__dict__                   #F与f都不受影响
{}
>>>F.x
100
>>>f.x
100



'''********************'''继承'''************************************************************'''
继承时在类名后添加()，并在()中写入基类名
如果有同名属性或方法，则派生类的会覆盖基类的同名属性或方法

class A:
    x = 520

class B(A):
    pass


b = B()

isinstance(b, B)    #判断对象b是否属于类B或类B的基类，返回True或False
issubclass(B, A)    #判断类B是否为类A的子类，返回True或False


#多重继承
class C(A, B):
    pass

如果父类有同名属性或方法，则优先选用首个继承的类（即类A）的属性或方法


#组合
组合即在类的内部创建实例化对象

class Turtle:
    def say(self):
        print("不积跬步无以至千里!")

class Cat:
    def say(self):
        print("喵喵喵~")

class Dog:
    def say(self):
        print("汪汪汪~")

class Garden:
    t = Turtle()
    c = Cat()
    d = Dog()
    def say(self)
        selt.t.say()
        selt.c.say()
        selt.d.say()

>>>g = Garden()
>>>g.say()
不积跬步无以至千里!
喵喵喵~
汪汪汪~


#构造函数
在类内定义 __init__() 方法

>>>class A:
...   def __init__(self, x, y):
...       self.x = x
...       self.y = y
...   def add(self):
...       return self.x + self.y
...
>>>a = A(2, 3)
>>>a.__dict__           #对象在被实例化时创建了属性x和y并赋了初值
{'x': 2, 'y': 3}
>>>a.add()
5
>>>A.add()              #而类A因为没有x，y参数，调用方法时会报错
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: A.add() missing 1 required positional argument: 'self'


#析构函数
在类内定义 __del__() 方法

>>>class D
...    def __init__(self):
...        print("创建成功！")
...    def __del__(self):
...        print("销毁成功！")
...
>>>d = D()
创建成功！
>>>del d
销毁成功！
#当对象还有被引用时，del只会销毁对象名，只有在没有其它引用时才会调用析构函数真正销毁对象。
>>>d = D()
创建成功！
>>>e = d
>>>del d
>>>del e
销毁成功！
#旁门左道：在析构函数中将self传递出去，可以实现对象的重生.
#通过全局变量
>>>class F1:
...    def __del__(self):
...        global x
...        x = self
...
>>>f1 = F1()
>>>f1
<__main__.F1 object at 0x0000023486625050>
>>>del f1
>>>x
<__main__.F1 object at 0x0000023486625050>
#通过闭包函数
>>>class F2:
...    def __init__(self, func):
...        self.func = func
...    def __del__(self):
...        self.func(self)
...
>>>def outter():
...    x = 0
...    def inner(y=None):
...        nonlocal x
...        if y:
...            x = y
...        else: 
...            return x
...    return inner
...
>>>e = outter()
>>>f2 = F2(e)
>>>f2
<__main__.F2 object at 0x0000023486625290>
>>>del f2
>>>g = e()
>>>g
<__main__.F2 object at 0x0000023486625290>


#重写
Python不支持函数重载。
子类中定义与父类同名的属性或方法会直接覆盖。但仍然可以在方法中调用父类的方法（需要指定类名）。
>>>class B(A):
...   def __init__(self, x, y, z):
...      A.__init__(self, x, y)
...      self.z = z
...  def add(self):
...      return A.add(self) + self.z
...
>>>b = B(4, 5, 6)
>>>b.add()
15


#钻石继承
A派生出B1、B2，而C同时继承自B1、B2。此时C中会有两份一样的来自A的属性和方法。
为避免此情况，在继承时使用 super() 函数代替重复方法的父类名。类似虚继承。

super()方法依赖于MRO顺序，我们可以通过 .mro() 或 .__mro__ 方法查看对应MRO顺序。


#多态
class Cat:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def intro(self):
        print(f"我是小猫咪，我叫{self.name},今年{self.age}岁~")
    def say(self):
        print("miao~")

class Dog:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def intro(self):
        print(f"我是小狗，我叫{self.name},今年{self.age}岁~")
    def say(self):
        print("汪汪！")

>>>c = Cat("web", 4)
>>>d = Dog("布布", 7)
>>>def animal(x):           #接口函数
...    x.intro()
...    x.say()
...
>>>animal(c)
我是小猫咪，我叫web,今年4岁~
miao~
>>>animal(d)
我是小狗，我叫布布,今年7岁~
汪汪！


