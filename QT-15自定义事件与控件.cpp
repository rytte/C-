/********************/自定义事件与控件/************************************************************/
自定义事件：对已有控件的事件方法进行重写。
自定义控件：对已有控件派生类的事件方法进行重写。构造函数需与父类保持一致，重写的虚函数需要声明，事件方法返回父类该事件（即调用父类控件原本的功能）。

事件执行流程：
事件产生(窗口)->事件过滤(过滤器)->事件分发(指定执行窗口)->事件执行(具体控件)

自定义事件：
1、修改事件的执行动作
2、修改事件过滤器的动作
3、修改事件分发时的动作
4、修改事件产生时的动作

自定义的事件的四种方法，起始都是对QEvent类对象的重新设置。

QObject类方法
virtual bool event(QEvent*e)								//事件方法
virtual bool eventFilter(QObject*watched, QEvent* event)		//事件过滤器方法

QWidget类方法
virtual void enterEvent(QEvent* event)				//进入事件
virtual void leaveEvent(QEvent* event)				//离开事件
virtual void keyPressEvent(QKeyEvent* event)		//按键按下事件
virtual void keyReleaseEvent(QKeyEvent* event)		//按键松开事件
virtual void moveEvent(QMoveEvent* event)			//移动事件
virtual void paintEvent(QPaintEvent* event)			//绘图事件
virtual void resizeEvent(QResizeEvent* event)		//重新设置尺寸事件

按键事件：
1、声明
public:
	virtual void keyPressEvent(QKeyEvent* ev)
	virtual void keyReleaseEvent(QKeyEvent* ev)
2、添加头文件<QKeyEvent>
3、重写虚函数
4、构造函数中加入this->grabKeyboard()捕获按键


//修改事件过滤器动作
（1）在界面中安装事件过滤器
void installEventFilter(QObject* filterObj)
（2）在类重重写事件过滤函数
virtual bool eventFilter(QObject* watched, QEvent* event)		//watched:控件		event:事件

enum QEvent::Type  QT事件种类
QEvent::None				没有任何事件发生
QEvent::Enter				鼠标进入控件
QEvent::MouseButtonPress	鼠标按键按下
QEvent::Move				窗口坐标改变
QEvent::MouseMove			鼠标移动
....						...


//修改事件分发时的动作
在QApplication类的基础上派生出自定义的工程类，实现自定义的事件循环队列。在这里重写notify的事件分发方法。
virtual bool notify(QObject* receiver, QEvent* e) override
main函数中的application类对象使用自定义的app类对象。


//修改在事件处理时的动作
在QWiget类的event函数中判断事件类型，并修改方法


/************************************************************/
自定义控件
以QT中的默认控件类为基础，派生出自定义的控件类。自定义控件类要与基类的构造函数完全一致。这样才能兼容原控件类的方法。

在UI界面上创建自定义控件
（1）把基类控件拖到UI界面。
（2）点击基类控件，右键选中”提升为”。在输入栏中输入自定义的类名称
（3）选中自定义的控件类，点击提升。


//QKeyEvent 键盘事件类
头文件<QKeyEvent>
QKeyEvent(QEvent::Type type, int key, Qt::KeyboardModifiers modifiers, const QString& text = QString(), bool autorep = false, ushort count = 1)
type:  事件种类
key : 按下哪一个事件
modifiers : 协助模式
Qt::NoModifier   无辅助
Qt::ShiftModifier  shift键辅助
Qt::ControlModifier   ctrl键辅助
text : 传递过去的内容


如果Qt有安装自动输入法的控件，可以通过以下方法调用输入法
（1）在QApplication对象创建之前调用软键盘
qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
（2）指定w窗口，当它被开启输入时，显示软键盘
	w->setAttribute(Qt::WA_InputMethodEnabled, true);