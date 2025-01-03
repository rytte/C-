('''********************'''内置函数'''************************************************************'''
内置函数（Built-in Functions）

abs()	        dict()	        help()  	    min()   	    setattr()
all()	        dir()	        hex()	        next()	        slice()
any()	        divmod()	    id()	        object()	    sorted()
ascii()	        enumerate()	    input()	        oct()	        staticmethod()
bin()	        eval()	        int()	        open()	        str()
bool()	        exec()	        isinstance()    ord()	        sum()
bytearray()	    filter()	    issubclass()    pow()	        super()
bytes()	        float()	        iter()	        print()	        tuple()
callable()      format()	    len()	        property()	    type()
chr()	        frozenset()	    list()	        range()	        vars()
classmethod()   getattr()	    locals()	    repr()	        zip()
compile()	    globals()	    map()	        reversed()	    __import__()
complex()	    hasattr()	    max()	        round()	        reload()
delattr()	    hash()	        memoryview()	set()


对象属性相关
hasattr(对象名，属性名)            判断对象是否有该属性，返回True或False
getattr(对象名，属性名)            返回对象该属性的值
setattr(对象名，属性名，设置值)    设置对象属性值
delattr(对象名，属性名)            删除对象属性值



'''********************'''索引、切片、迭代'''************************************************************'''
对象被索引或获取时，会调用 __getitem__(self, index)方法。
class A:
    def __getitem__(self, index):
        print(index)

>>>a = A()
>>>a[3]
3

对象进行切片时，会调用 slice()内置方法。
>>>s = "FishC"
>>>s[slice(2, 4)]
'shC'
>>>s[slice(2, None)]
'shC'
>>>s[slice(None, None, 2)]
"FsC"

为对象索引或切片赋值时，会调用 __setitem__(self, index, value)方法。

定义了 __iter__(self)的对象就是可迭代对象，定义了 __next__(self)的可迭代对象就是迭代器。
#for 循环原理
>>>x = [1, 1, 2, 3, 5]
>>>temp = iter(x)
>>>while True:
   try:
       i = temp.__next__()
   except StopIteration:
       break
   print(i, end='')

1 1 2 3 5


'''********************'''代偿'''************************************************************'''
in 和 not in判断时，调用 __contains__(self, item)方法，如果该方法无法实现，则会调用 __iter__(self)和 __next__(self)方法代偿，再没有就调用 __getitem__(self, index)方法...

bool() 函数会调用 __bool__(self)方法，如果该方法无法实现，则会调用 __len__(self)方法。

#运算符调用的方法
<       __lt__(self, other)
<=      __le__(self, other)
>       __gt__(self, other)
>=      __ge__(self, other)
==      __eq__(self, other)
!=      __ne__(self, other)

#若想使某个方法不生效，可以使其=None，如：__le__ = None


定义了 __call__(self[, args...])方法的类对象可以调用其它类对象。

str() 函数会调用 __str__(self)方法，如果该方法无法实现，则会调用 __repr__(self)方法。
repr()函数会调用 __repr__(self)方法。

eval()函数：将参数去引号后执行
>>>eval("1 + 2")
3

'''********************'''property() 函数'''************************************************************'''
class property(fget=None, fset=None, fdel=None, doc=None)

该函数用于返回一个 property 属性对象，该函数可以很便捷地设置对象属性的获取、设置、删除、注释。
>>>class E:
...    def __init__(self):
...        self._x = 520
...    def getx(self):
...        return self._x
...    def setx(self, value):
...        self._x = value
...    def delx(self):
...        del self._x
...    x = property(getx, setx, delx)
...
>>>e = E()
>>>e.x
520
>>>e.x = 330
>>>e.__dict__
{'_x': 330}
>>>del e
>>>e.__dict__
{}

#装饰器方式使用property函数
>>>class F:
...   def __init__(self):
...       self._x = 520
...   @property 
...   def x(self):
...       return self._x
...   @x.setter            #setter()和deleter()方法是property返回的
...   def x(self, value):
...       self._x = value
...   @x.deleter
...   def x(self):
...       del self._x
...
>>>f = F()
>>>f.x
520
>>>f.x = 330
>>>f.__dict__
{'_x': 330}
>>>del f
>>>f.__dict__
{}


#描述符
定义了 __get__(self, instance, owner)、__set__(self, instance, value)、__delete__(self, instance)方法(任意一个)的类对象称为描述符。
参数instance代表描述符所拦截的属性所在的实力对象。
可以通过描述符对象改写其它对象。
property() 函数、普通方法、静态方法、类方法、__slots__属性 都是基于描述符协议实现的。

>>>class D:
...    def __get__(self, instance, owner):
...        print("get~")
...
>>>class C:
...    x = D()
...
>>>c =C()
>>>c.x
get~

#两类描述符
描述符分为两类：
数据描述符：实现了 __set__() 和 __delete__()方法任意一个的描述符
非数据描述符：只实现了 __get__()方法的描述符

发生属性访问时，访问优先级顺序 数据描述符 > 实例对象属性 > 非数据描述符 > 类属性
>>>c.x = "FishC"        #此处发生实例对象属性的修改，由于优先级高于非数据描述符__get__方法，下面就不会打印get~了。
>>>c.x
'FishC'

#__set_name__(slef, owner, name)
Python3.6 为描述符新增了一个方法 __set_name__(slef, owner, name)
该方法可以省去创建对象时传入属性名。



'''********************'''type() 函数'''************************************************************'''
type(obj) 函数传入对象会返回对象所属类

>>>type(123)
<class 'int'>
>>>int
<class 'int'>
>>>type(220)("330")   #相当于int("330")，将字符串330转换成整数
330
>>>type(())([1, 1, 2, 3, 5])
(1, 1, 2, 3, 5)       #相当于tuple([1, 1, 2, 3, 5])
#适用于类
>>>class C:
...    def __init__(self, x):
...        self.x = x
...
>>>c = C(10)
>>>c
<__main__.C object at 0x0000023B2D1258D0>
>>>d = type(c)(520)         #相当于d = C(520)
>>>d
<__main__.C object at 0x0000023B2D1256D0>
>>>d.__class__              #__class__方法也可以查看对象的所属类
<class '__main__.C'>


#type 类是所有类对象的所属类
>>>type(int)
<class 'type'>
>>>type(C)
<class 'type'>
>>>type(type)
<class 'type'>


#type()函数第二种用法，可以创造一个类，作为返回值返回
type(name, bases, dict, **kwds)
参数：
name:       指定要创建的类的名字
bases:      指定要创造的类的基类
dict:       指定要创造的类的属性和方法
kwds:       （可选）收集参数，当且仅当需要时，该收集参数将被传递给适当的元类机制（通常为__init_subclass()）
            #__init_subclass(): Python3.6新增方法，增强父类对子类的管理

>>>class E:
...    pass
...
>>>E = type('E', (), {})    #使用变量名E接收type创建返回的名为E类，该类E与上面定义的空类E等价

#下面创建的两个类F等价
>>>class F(E)
...    x = 120
...    def say_hi(self, name="FishC"):
...        print(f"Hello {name}")
...

>>>def func(self, name="FishC"):
...    print(f"Hello {name}")
...
>>>F = type('F', (E,), dict(say_hi=func, x=120))


#__init_subclass(cls, *args): Python3.6新增方法，继承时触发，同时使子类中的同名属性和方法失效
实例：
>>>class C:
...    def __init_subclass__(cls):
...        print("不许修改~")
...        cls.x = 520
...
>>>class D(C):
...    x = 360
...
不许修改~
>>>D.x
520

