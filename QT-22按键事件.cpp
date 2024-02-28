按键事件：
1、声明
public:
	virtual void keyPressEvent(QKeyEvent * ev)
		virtual void keyReleaseEvent(QKeyEvent * ev)
		2、添加头文件 < QKeyEvent>
		3、重写虚函数
		4、构造函数中加入this->grabKeyboard()捕获按键