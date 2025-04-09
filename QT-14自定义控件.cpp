/********************/自定义控件/************************************************************/
自定义控件：对已有控件派生类的事件方法进行重写。构造函数需与父类保持一致，重写的虚函数需要声明，事件方法返回父类该事件（即调用父类控件原本的功能）。
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


