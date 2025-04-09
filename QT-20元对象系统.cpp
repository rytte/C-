/********************/QT元对象系统/************************************************************/
Qt 的元对象系统（Meta - Object System） 是 Qt 框架的核心机制之一，它使得 Qt 在 C++ 原生能力的基础上，支持了许多高级特性，比如：

1、信号与槽（Signal & Slot）
2、运行时类型信息（RTTI）
3、动态属性系统
4、QObject 派发机制


//什么是元对象系统？
Qt 的元对象系统是一套在 C++ 基础上构建的运行时反射机制，它为类添加了额外的元信息（Meta - Information），让对象在运行时可以：
1、知道自己的类型和属性
2、动态调用函数
3、连接信号与槽（事件驱动编程）
4、这种机制是通过一个 Qt 的预处理器 moc（Meta - Object Compiler）来实现的。


//核心组成
元对象系统依赖于继承自 QObject 的类。Q_OBJECT 宏会启用 Qt 的元对象特性。

class MyObject : public QObject {
    Q_OBJECT  // 必须有这个宏！
};

moc（Meta - Object Compiler）
Qt 编译过程中，moc 会读取带有 Q_OBJECT 宏的类，生成一个.moc 文件，这个文件包含：
1、元信息表
2、信号与槽的派发逻辑
3、类型信息注册


//1、信号与槽
略过


//2、反射功能（运行时类型识别）
你可以在运行时获取类名、属性名、方法名等信息：
QObject* obj = new MyObject;
qDebug() << obj->metaObject()->className();  // 输出类名

你甚至可以动态调用函数：
QMetaObject::invokeMethod(obj, "someMethod");


//3、动态属性系统
元对象系统还支持“动态属性”，你可以在运行时给对象添加属性：
obj->setProperty("version", 1.2);
qDebug() << obj->property("version").toDouble();  // 读取属性


//常用宏
宏	            用途
Q_OBJECT	    启用元对象支持，必须放在类定义中
signals:	    声明信号
slots :         声明槽函数
Q_PROPERTY	    声明属性，可用于绑定和序列化
Q_CLASSINFO	    添加类描述信息


//Q_OBJECT宏的作用（注意：类定义需要放在头文件中）
1、信号 / 槽机制
2、QObject::connect() 自动识别槽名
3、运行时类名（className()）
4、反射调用（invokeMethod()）
5、动态属性系统



/********************/QObject/************************************************************/
QObject 是 Qt 框架中最核心的基类之一，几乎所有 Qt 对象类（如 QWidget、QTimer、QThread 等）都是它的子类。

//主要作用
功能	                描述
对象树管理	        管理对象的父子关系，自动销毁子对象
信号与槽	            提供事件通信机制
事件处理系统	        支持事件循环、事件分发
元对象系统	        提供运行时类型信息和反射功能
对象名称 / 属性	    支持动态设置 / 获取属性、名称等
线程关联	            支持对象与线程绑定


//QObject特性
1、QObject如果有对象，必须在同一线程中
2、QObject类的成员变量是否为其子对象问题
3、禁用拷贝构造函数，禁用赋值运算符

* 由于禁用拷贝构造和赋值操作，当我们使用QList<QObject>时，编译器就会报错。
* 如果我们要在容器中存储这中类型的对象，我们就要使用它们的指针。如QList<QObject*>


//QObject具有线程亲和性（Thread Affinity）
就是这个类创建的对象收到信号或者事件的时候，处理信号的槽函数以及处理事件的某某函数也是和这个对象在一个线程中运行。


//常用方法
objectName()	                // 获取对象名称
setObjectName()	                // 设置名称，可用于调试
parent()	                    // 获取父对象
children()	                    // 获取子对象列表
deleteLater()	                // 安全延迟销毁对象（避免立即释放问题）
moveToThread(QThread*)	        // 移动对象到其他线程
installEventFilter(QObject*)	// 安装事件过滤器
setProperty() / property()	    // 设置 / 读取动态属性
metaObject()	                // 获取元对象信息



/********************/QMetaObject/************************************************************/
QMetaObject 是 Qt 元对象系统中的核心类，它保存了一个类的所有元信息，比如：
1、类名
2、父类
3、信号和槽
4、属性（Property）
5、方法（Method）
6、枚举类型（Enum）
7、插槽的动态调用能力

//QObject和QMetaObject的关系
每个 QObject 都 包含一个 QMetaObject 实例（指针）
每个 QObject 子类都有静态的 QMetaObject
QObject 是运行时的对象实例，QMetaObject 是描述这个类元信息的数据结构。

//获取类的QMetaObject
const QMetaObject & meta = MyObject::staticMetaObject;       //静态获取
MyObject obj;
const QMetaObject* meta = obj.metaObject();                 //动态获取（通过对象）

//QMetaObject方法        
className()                                     // 获取类名	        
superClass()                                    // 获取父类信息	    
methodCount()                                   // 获取方法个数	    
method(index)                                   // 获取某个方法，返回 QMetaMethod
propertyCount()                                 // 获取属性个数	    
property(index)                                 // 获取某个属性，返回 QMetaProperty
method(i).methodType() == QMetaMethod::Signal   // 获取信号数量	    


//QMetaObject::invokeMethod()
用于 在运行时通过方法名调用对象的方法（槽函数或普通成员函数），而 不需要直接调用函数指针
QMetaObject::invokeMethod(obj, "mySlot");           // 调用无参槽函数
QMetaObject::invokeMethod(obj, "calculateSomething",
    Q_RETURN_ARG(int, result),                          // 返回值
    Q_ARG(int, 10), Q_ARG(int, 20));                    // 参数
QMetaObject::invokeMethod(obj, "updateUI", Qt::QueuedConnection);   // 用于不同线程间调用。会将调用请求放入 obj 所在线程的事件队列中，由该线程执行



/********************/moc/************************************************************/
//moc工作流程
1. 你写了一个 QObject 派生类，并用了 Q_OBJECT 宏
        ↓
2. Qt 编译器调用 moc，处理包含 Q_OBJECT 的头文件
        ↓
3. moc 生成一个 moc_类名.cpp，包含：
- 信号 / 槽相关代码
- 元对象表（类名、方法名等）
- 动态调用机制（invokeMethod）
        ↓
4. 这个.moc 文件被自动包含进你的 C++ 代码中
        ↓
5. 编译器将你自己的代码和 moc 生成的代码一起编译成可执行文件


//moc文件内容
qt_meta_stringdata_MyObject	    存放类名、方法名等字符串
qt_meta_data_MyObject	        存放类的方法、信号、槽等信息的"偏移表"
staticMetaObject	            实现 QMetaObject，用于支持 metaObject()
qt_metacall()	                Qt 用于动态调用槽函数的机制
qt_metacast()	                类名字符串转对象指针，用于运行时类型识别（RTTI）


//手动编译moc文件
moc myobject.h - o moc_myobject.cpp







