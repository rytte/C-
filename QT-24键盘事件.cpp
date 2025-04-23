按键事件：
1、声明
public:
	virtual void keyPressEvent(QKeyEvent * ev)
		virtual void keyReleaseEvent(QKeyEvent * ev)
		2、添加头文件 <QKeyEvent>
		3、重写虚函数
		4、构造函数中加入this->grabKeyboard()捕获按键


//QKeyEvent 键盘事件类
#include <QKeyEvent>
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
