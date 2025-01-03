('''********************'''类属性和方法'''************************************************************'''
 
#私有变量和私有方法
定义私有变量：变量名前加两条下划线，如：__x
私有变量原理：私有变量无法在类外直接访问，其原理是定义后偷偷改了名字：_类名__x，可以在类外使用新名字访问该变量。
私有方法同理。

>>>class B:
   __x = 520
   def setx(self, x):
       self.__x = x 
   def getx(self):
       print(self.__x)

>>>b = B()
>>>b.__x            #私有变量，不论是类还是其对象都无法直接访问，需要通过调用方法来访问
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'B' object has no attribute '__x'
>>>B.__x
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: type object 'B' has no attribute '__x'
>>>b.setx(120)      #通过调用方法定义一个私有变量
>>>b.getx()         #通过调用方法访问私有变量
120
#其它访问方式
>>>b.__dict__
{'_B__x': 120}
>>>b._B__x
120
#后期动态添加的私有变量不属于私有变量
>>>b.__y = 200
>>>b.__y                        #可以直接访问到
200
>>>b.__dict__       
{'_B__x': 120, '__y': 100}      #没有被改名

单下划线开头的变量：_z        约定俗成的仅供内部使用的变量
单下划线结尾的变量：z_        定义变量名时防止冲突，如：使用 class 作为变量名，又不想使关键字 class 冲突，就定义为 class_


'''************************************************************'''
#__slots__属性
Python的类和对象存放属性的方式就是字典。字典的高效是以空间为代价的。
可以使用__slots__对不使用字典方式的类其属性进行声明，但声明以后无法再动态添加属性了。
子类会继承父类的__slots__属性，但不会在子类中生效，也就是说子类仍然具有字典属性，可以动态添加自己的属性。
>>>class S:
   __slots__ = ["x", "y"]

>>>s = S()
>>>s.x = 100            #声明的变量可以正常赋值、调用以及删除
>>>s.x
100
>>>s.z = 300            #无法添加其它未声明变量
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'S' object has no attribute 'z'
#无字典属性，无法调用__dict__方法，但可以调用dir()函数
>>>s.__dict__           
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'S' object has no attribute '__dict__'
>>>dir(s)
['__class__', '__delattr__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__slots__', '__str__', '__subclasshook__', 'y']
#派生类仍具有字典属性
>>>class T(S):
   pass

>>>T.__dict__
mappingproxy({'__module__': '__main__', '__dict__': <attribute '__dict__' of 'T' objects>, '__weakref__': <attribute '__weakref__' of 'T' objects>, '__doc__': None})
>>>T.__slots__
['x', 'y']


'''************************************************************'''
#__new__()方法
创建对象时，先调用 __new__(cls[, ...])方法创建类的实例对象，传入的参数 cls 就是类，然后传出 self ，传递给 __init__()方法。

需要重写 __new__()方法的两种情况：
1、在元类中定制类
2、继承不可变的数据类型的时候，可以将不可变的数据作为接收的参数进行修改。


'''************************************************************'''
#类的专有方法
可以在类内重写这些方法，进行重载

__repr__ : 打印，转换
__setitem__ : 按照索引赋值
__getitem__: 按照索引获取值
__len__: 获得长度
__cmp__: 比较运算
__call__: 函数调用、
__index__:使用对象作为索引值访问时触发

__add__: 加运算
__sub__: 减运算
__mul__: 乘运算
__truediv__: 除运算
__mod__: 求余运算
__pow__: 乘方

r版(如：__radd__)，当运算符左侧对象的运算符方法无法正常实现时，则会调用右侧对象的r版运算符。
i版(如：__iadd__)，该方法是运算兼赋值的操作，即x += y。

>>>class S(str)
   def _add_(self, other):              #重写__add__方法，重写的是"+"左边的对象的方法
       return len(self) + len(other)

>>>s1 = S("FishC")
>>>s2 = S("Python")
>>>s1 + s2
11



'''********************'''类方法和静态方法'''************************************************************'''
#类方法
一般来说，不通过类对象直接使用类中的方法需要为 self 参数传入类名。
一般方法默认传入调用方法的类对象，而使用@classmethod 装饰的类方法，默认传入类名
>>>class D:
   def funA(self):
       print(self)
   @classmethod
   def funB(cls):           #和self参数一样，cls参数只是一个形参，不是关键字，可以改成其它名字
       print(cls)

>>>d = D()
>>>d.funA()
<__main__.D object at 0x0000023B2D11BC50>
>>>d.funB()
<class '__main__.D'>


#静态方法
创建静态方法需要使用@staticmethod 装饰器
静态方法就是类对象和类名都不默认传入的方法，因此静态方法没有参数。
>>>class G:
   x = 100
      @staticmethod
      def get_x():
          print(f"该类属性x={G.x}。")

>>>g = G()
>>>g.get_x()
该类属性x=3。



'''********************'''类装饰器'''************************************************************'''
类装饰器的作用是在类被实例化之前对其进行拦截和干预。

类使用函数作为装饰器后，在类实例化对象的时候会自动调用该函数。
函数使用类作为装饰器后，在

#函数作为类装饰器
>>>def report(cls):
   def oncall(*args, **kwargs):
       print("开始实例化对象...")
       _ = cls(*args, **kwargs)         #在此处调用被装饰的类
       print("实例化完成~")
       return _
   return oncall

>>>@report
...class C:
   def __init__(self, x, y, z):
       self.x = x
       self.y = y
       self.z = z
       print("构造函数被调用~")

>>>c = C(1, 2, 3)
开始实例化对象...
构造函数被调用~
实例化完成~

#类作为函数装饰器
>>>class Counter:
   def __init__(self,  func):
       self.count = 0
       self.func = func
   def __call__(self, *args, **kwargs):         #__call__()方法在对象被当做函数一样使用()调用时被调用
       self.count += 1
       print(f"已经被调用了{self.count}次~")
       return self.func(*args, **kwargs)

>>>@Counter         #相当于 say_hi = Counter(say_hi) 实例化Counter对象
...def say_hi():
   print("嗨~")

>>>say_hi
<__main__.Counter object at 0x0000023B2D125550>
>>>say_hi()
已经被调用了1次~
嗨~
>>>say_hi()
已经被调用了2次~
嗨~


