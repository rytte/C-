/********************/QT基础/************************************************************/
QMainWindow类：是窗口的框架，包含：MenuBar菜单栏，ToolBar工具栏，StatusBar状态栏，CentralWidget中央控件。
头文件：#include<QMainWindow>
qmake： QT += widgets

UI底层界面就是CentralWidget对象。

Q_OBJECT		宏定义，实现信号与槽的功能

ui->setupUi		UI界面的QMainWindow窗口框架和各种控件初始化。

Ctrl + F		在帮助索引中搜索相关内容。


QT工程编译后会生成一个build文件，程序在这里执行。


void setWindowTitle(const QString&)          //设置窗口标题
void setWindowIcon(Icon(":/资源图片名"))     //设置窗口图标


Qt Designer被称为Qt设计师，用于设计和构建图形用户界面（Qt Widgets）。也就是可视化图形设计界面。
Qt Linguist被称为Qt语言家。主要任务是读取翻译文件、为翻译人员提供友好的翻译界面，是用于界面国际化的重要工具。它能帮助你很容易读懂C++语言。
Qt Assistant被称为Qt助手，是Qt自带的一款可定制、可重新发行的帮助文件浏览器。它支持HTML文件，用户可以利用其定制自己的功能强大的帮助文档浏览器。


//一般快捷键
动作						快捷键
打开文件或项目(O)…			Ctrl+O
新建文件或项目(N)…			Ctrl+N
在外部编辑器中打开			Alt+V, Alt+I
全选(A)					Ctrl+A
删除						Del
剪切(T)					Ctrl+X
复制©					Ctrl+C
粘贴						Ctrl+V
撤销						Ctrl+Y
打印						Ctrl+P
保存						Ctrl+S
保存所有文件(L)…	CTRL+Shift+S
关闭窗口	Ctrl+W
关闭所有文件	Ctrl+Shift+W
关闭当前文件	Ctrl+F4
后退	Alt+Left
前进	Alt+Right
跳转行(G)…	Ctrl+L
历史中下个打开的文件	Ctrl+Shift+Tab
切换到其他分栏	Ctrl+E, O
历史中先前打开的文件	Ctrl+Tab
激活定位器	Ctrl+K
切换到欢迎模式	Ctrl+1
切换到编辑模式	Ctrl+2
切换到设计模式	Ctrl+3
切换到调试模式	Ctrl+4
切换到项目模式	Ctrl+5
切换到分析模式	Ctrl+6
切换到帮助模式	Ctrl+7
切换问题窗口	Alt+1 (Cmd+1 on OS X)
切换搜索结果窗口	Alt+2 (Cmd+2 on OS X)
切换应用程序输出窗口	Alt+3 (Cmd+3 on OS X)
切换编译输出窗口	Alt+4 (Cmd+4 on OS X)
切换其它输出窗口	Alt+编号 (Cmd+编号 on OS X) 编号为"输出窗口"中的编号
激活书签窗口	Alt+M
激活文件系统窗口	Alt+Y
激活打开文档窗口	Alt+O
最大化输出窗口	Alt+9
输出窗口-下一项	F6
输出窗口-上一项	Shift+F6
激活项目窗口	Alt+X
全屏	Ctrl+Shift+F11
切换侧边栏	Alt+0 (Cmd+0 on OS X)
撤销	Ctrl+Z
移动到编辑模式。在编辑模式下：第一次按下将焦点移动到编辑器中，第二次按下关闭辅助窗口	Esc
退出Qt Creator	Ctrl+Q
//编辑快捷键
动作	快捷键
自动缩进	Ctrl+I
折叠	Ctrl+<
展开	Ctrl+>
在此范围内触发完成	Ctrl+Space
复制行	Ctrl+Ins
复制到行下	Ctrl+Alt+Down
复制到行上	Ctrl+Alt+Up
查看剪切板历史	Ctrl+Shift+V
剪切行	Shift+Del
追加行	Ctrl+J
在当前行上方插入新行	Ctrl+Shift+Enter
在当前行下方插入新行	Ctrl+Enter
减小字体大小	Ctrl± (Ctrl+鼠标滚轮向下)
增加字体大小	Ctrl++ (Ctrl+鼠标滚轮向上)
重置字体大小	Ctrl+0
切换Vim的编辑风格	Alt+V, Alt+V
分栏	Ctrl+E, 2
左右分栏	Ctrl+E, 3
删除所有分割	Ctrl+E, 1
删除当前分割	Ctrl+E, 0
全选	Ctrl+A
跳转至块结尾	Ctrl+]
跳转至块开始	Ctrl+[
跳转至以}结尾的块	Ctrl+}
跳转至以{开始的块	Ctrl+{
向下移动当前行	Ctrl+Shift+Down
向上移动当前行	Ctrl+Shift+Up
在此范围激活重构	Alt+Enter
重新包装段	Ctrl+E, R
选择当前块，第二次按下选择父块	Ctrl+U
启用文本换行	Ctrl+E, Ctrl+W
注释选中的内容	Ctrl+/
可视化的空白	Ctrl+E, Ctrl+V
调整大小	Ctrl+J
网格布局	Ctrl+G
水平布局	Ctrl+H
垂直布局	Ctrl+L
预览	Alt+Shift+R
编辑信号和槽	F4
切换书签	CTRL+M
下个书签	Ctrl+.
上个书签	Ctrl+,
取得代码片段	Alt+C, Alt+F
粘贴代码片段	Alt+C, Alt+P
查找所有引用	Ctrl+Shift+U
跟随鼠标下的符号	F2
重命名光标所在符号	Ctrl+Shift+R
切换函数声明/定义	Shift+F2
打开类型层次窗口	Ctrl+Shift+T
切换头文件/源文件	F4
选中的文本变小写	Alt+U
选中的文本变大写	Alt+Shift+U
在JavaScript中执行静态检查来查找共同问题	Ctrl+Shift+C
查找和替换	Ctrl+F
向下查找	F3
向上查找	Shift+F3
查找选中文本下一次出现	Ctrl+F3
查找选中文本上一次出现	Ctrl+Shift+F3
替换和查找下一个	Ctrl+=
打开高级搜索	Ctrl+Shift+F
录制宏	Alt+(
停止录制宏	Alt+)
播放最近的宏	Alt+R
显示Qt Quick工具栏	Ctrl+Alt+Space
在FakeVim模式执行用户行为	Alt+V, n, 其中n是用户动作的数量, 从1到9
//图像浏览器快捷键
动作	快捷键
切换背景	Ctrl+[
显示轮廓线	Ctrl+]
放大	Ctrl++
缩小	Ctrl±
适应屏幕	Ctrl+=
原始大小	Ctrl+0
//Qt Quick设计师快捷键
动作	快捷键
打开定义所选组件的QML文件	F2
切换代码编辑器/可视化编辑器	F4
切换左侧侧边栏	Ctrl+Alt+0
切换右侧侧边栏	Ctrl+Alt+Shift+0
//调试快捷键
动作	快捷键
开始/继续调试	F5
停止调试	Shift+F5
单步跳过	F10
单步进入	F11
单步跳出	Shift+F11
切换断点	F9
运行到选择的函数	Ctrl+F6
执行到行	Ctrl+F10
相反方向	F12(暂无)
//项目快捷键
动作	快捷键
构建项目	Ctrl+B
构建所有项目	Ctrl+Shift+B
新建项目…	Ctrl+Shift+N
载入项目…	Ctrl+Shift+O
选择构建套件(Kit)构建和运行项目	Ctrl+T
运行	Ctrl+R
//帮助快捷键
动作	快捷键
上下文相关帮助	F1
在帮助模式下激活内容	Ctrl+T(暂无)
添加书签	Ctrl+M
在帮助模式下激活索引	Ctrl+I(暂无)
重置字体大小	Ctrl+0(暂无)
在帮助模式下激活查找	Ctrl+S(暂无)


全局搜索
Ctrl + Shift + U


//文本编辑宏
当你在代码编辑器中打开一个文件，可以记录键盘序列作为宏。然后，你可以运行重复序列的宏。可以保存最新的宏并分配快捷键运行，或从定位器运行。



/********************/QT元对象系统/************************************************************/
QObject 类不仅是所有 Qt 对象的基类，还是“Qt 中的对象模型（Object Model）”的核心类。
我们知道元对象模型最重要的功能就是“信号 - 槽”机制，该机制使 Qt 对象之间可以进行无缝的交互。
那么只要是 QObject 及其子类，都可以使用信号 - 槽机制。

//QObject特性
1、QObject如果有对象，必须在同一线程中
2、QObject类的成员变量是否为其子对象问题
3、禁用拷贝构造函数，禁用赋值运算符


QObject 对象是具有线程亲和性（Thread Affinity）的。什么意思呢？
就是这个类创建的对象收到信号或者事件的时候，处理信号的槽函数以及处理事件的某某函数也是和这个对象在一个线程中运行。

Qt对标准C++增加了一些功能：signals, slots, object properties, events, event filters, string translation, timers, object trees, guarded pointers, dynamic cast.

我们知道在各种容器中能以value方式存放的类型，必须有默认的构造函数，拷贝构造函数和赋值操作。
由于QObject及所有继承自它的子类都没有提供拷贝构造和赋值操作，当我们使用QList<QObject>时，编译器就会报错。
如果我们要在容器中存储这中类型的对象，我们就要使用它们的指针。如QList<QObject*>


https://zhuanlan.zhihu.com/p/43598693
https://blog.csdn.net/dengjin20104042056/article/details/115272771


/********************/常用控件方法/************************************************************/
每种控件方法通常有多个重载，以geometry()方法为例：

const QRect & geometry() const				//获取位置和尺寸，返回引用
void	setGeometry(int x, int y, int w, int h)		//设置位置和尺寸（传入数字参数）
void	setGeometry(const QRect&)				//设置位置和尺寸（传入已有对象）


/************************************************************/
QObject类
void setObjectName(const QString & name)			//设置控件对象名称


QWidget类
void setGeometry()				//设置位置和尺寸
void setSizePolicy()				//设置策略模式
void setMinimumSize()			//设置最小尺寸
void setMaximumSize()			//设置最大尺寸
void setFont()					//设置字体。需要另外定义字体类QFont，设置好进行传入。


/************************************************************/
标签QLabel：
#include<QLabel>
void setText()					//设置标题文本
void setAlignment()				//设置对齐，多个参数需要使用"|"符号隔开。


编辑行QLineEdit：
#include<QLineEdit>
void setEchoMode()				//设置输出模式
void setPlaceholderText()		//设置提示词


按钮QPushButton：
#include<QPushButton>



/********************/QString/************************************************************/
QString：string的派生类
1、方法fromUtf8()	将字符串转换为uft - 8格式。
2、格式化输出		QString str = QString("今天是%1年%2月%3日").arg(2023).arg(7).arg(5)



QString->String
QString qstr;
String str = qstr.toStdString(); //QString转换为String
String->QString
String str;
QString qstr = QString::fromStdString(str); //String转换为QString
QString转换为String中文输出乱码解决
QString path;
//QString转String 乱码解决
String cstr = String((const char*)path.toLocal8Bit());



/********************/QLabel/************************************************************/

setPixmap()
clear();


