/********************/对话框/************************************************************/
//1、消息盒子：消息窗口
头文件<QMessageBox>
information(父窗口指针，窗口标签，文本内容，按钮(给定枚举类型)，默认按钮(默认为无))		//返回值为点击的按钮
information(this, "消息盒子", "注册成功", QMessageBox::Yes, QMessageBox::No)

图标：参数都一样。
感叹号information，返回值为 StandardButton 类型
问号question，返回值为 int 类型
警告叹号warning，返回值为 int 类型


//2、文件对话框：选择文件
头文件<QFileDialog>
getOpenFileName(父窗口指针，窗口标签，打开的目录，文件类型过滤，过滤选项)		//返回值为文件名字符串
getOpenFileName(this, "文件对话框", "../", "*.cpp *.h")							//当前目录"./"为工程build文件目录
//"*.cpp *.h"为同时过滤出*cpp和*h；"text(*.cpp);;file(*.h);;"为可选择其中一种。
getOpenFileNames()方法参数与上面相同，但返回的是一个含所有选择文件的字符串链表。


//3、字体对话框：设置字体大小和样式
头文件<QFontDialog>
getFont(传入bool类型参数(记录选择确认还是取消)，传入的Font对象(打开对话框时字体的默认选项)，父窗口指针，窗口标签)
QFont f = ui->label->font();
bool flag;
f = getFont(&flag, f, this, "字体对话框")


//4、颜色对话框：选择颜色获取颜色数据
头文件<QColorDialog>
getColor(颜色对象(打开对话框时的默认颜色默认为白色)，父窗口指针，窗口标签)		//返回QColor颜色对象
QColor color = getColor()
color.blue()		//获取蓝色数据0~255
color.grren()		//获取绿色数据0~255
color.red()			//获取红色数据0~255
color.name()		//获取全色数据"#000000"~"#ffffff"


//5、输入对话框
头文件<QInputDialog>
getText(父窗口指针，窗口标签，提示文本，设置输入模式(echomode默认普通模式)，文本，传入bool类型参数(记录选择确认还是取消))	//返回输入内容
QString str = getText(this, "输入对话框", "请输入账号")

//6、自定义对话框
头文件<QDialog>
自定义对话框是以Dialog类为基础直接设计对话框
QDialog的基类是QWidget

QDialog * d = new QDialog(this);
d->resize(400, 200);
QPushButton* bt = new QPushButton("ok", d);			//可以在对话框上创建按钮等控件
bt->setGeometry(100, 50, 100, 60);					//调整控件位置。自行设定控件槽函数
d->show();		//可替换为exec()方法。exec是进入到对话框的事件循环队列，无法点击其它窗口，直到退出。show是显示对话框，可以点击其它窗口。
