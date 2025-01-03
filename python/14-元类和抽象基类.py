('''********************'''元类'''************************************************************'''
元类是创造类的模版，type 类就是一个元类，但所有元类都继承自 type 。
元类只是创建类的模板，不属于其父类，没有指定父类的类，其父类默认为object。

元类与类的关系相当于类与对象的关系，怎样使用类定义对象，就怎样使用元类去定义类。
元类中的__new__()和__init__()方法会在派生类被定义完成时被调用。

>>>class MetaC(type):               #创建一个名为 MetaC 的元类
...    def __new__(mcls, name, bases, attrs):
...        print("__new__() in MetaC~")
...        return type.__new__(mcls, name, bases, attrs)
...    def __init__(cls, name, bases, attrs):
...        print("__init__() in MetaC~")
...        return type.__new__(cls, name, bases, attrs)
...
>>>class C(metaclass = MetaC)       #使用元类 MetaC 创造一个类，metaclass 是必要的关键字。
...    def __new__(cls):
...        print("__new__() in C~")
...        return super().__new__(cls)      #此处返回给其父类object
...    def __init__(self):
...        print("__init__() in C~")
...
__new__() in MetaC~
__init__() in MetaC~
>>>c = C()
__new__() in C~
__init__() in C~
>>>type(c)
<class '__main__.C'> 
>>>type(C)
<class '__main__.MetaC'>
>>>type(MetaC)
<class 'type'>

#单例模式
>>> class SimmpleInstance(type)
...    def __init__(cls, *args, **kwargs):
...        cls.__instance = None
...        type.__init__(cls, *args, **kwargs)
...    def __call__(cls, *args, **kwargs):
...        if cls.__instance = None:
...            cls.__instance = type.__call__(cls, *args, **kwargs)
...            return cls.__instance
...        else:
...            return cls.__instance
...
>>>class C(metaclass=SimmpleInstance)
>>>c1 = C()
>>>c2 = C()
>>>c1 is c2
True



'''********************'''抽象基类'''************************************************************'''
1、抽象基类不能被实力化
2、子类必须实现抽象基类中定义的方法，否则也不能被实例化

定义抽象基类：import abc      #abc模块AbstractBaseClasses

将一个定义为抽象基类，只需指定它的元类为ABCMeta
被@abstractmethod装饰器装饰的方法为抽象方法

>>>from abc import ABCMeta, abstractmethod 
>>>class Fruit(metaclass=ABCMeta):
...    def __init__(self, name):
...        self.name = name
...    @abstractmethod
...    def good_for_health(self):
...        pass
...
>>>fruit = Fruit("水果")                  #抽象基类无法被实例化
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: Can't instantiate abstract class Fruit with abstract method good_for_headlth
>>>class Banana(Fruit):                   #子类继承并重写抽象方法后才可实例化
...    class Banana(Fruit):
...        def good_for_health(self):
...            print("只要吃香蕉，人就会变得开心~")
...
>>>banana = Banana("香蕉")
>>>banana.good_for_health()
只要吃香蕉，人就会变得开心~



