/********************/其它问题;/************************************************************/
//命名冲突
::write()
类中有和标准库函数同名的函数，
加上::使用标准库函数
不加::使用类中成员函数



//QT 使用全局缩放进行全分辨率适配
qputenv("QT_SCALE_FACTOR", "2.0");
注意：
1、这句代码需要放在QApplication实例初始化之前。
2、缩放系数必须大于等于1.0，不然会出现一些奇怪的问题。而且必须是小数形式的字符串。


全局缩放引发了两个问题：
1、图片放大的时候有锯齿。
2、字体在缩放的时候质量不太好。

解决方法：
调整图片缩放质量
QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

文字质量
这需要使用另外一个东西”qt.conf“。
内容如下。
[Platforms]
WindowsArguments = fontengine = freetype

将这个文件放入程序的资源中。路径为":/qt/etc/qt.conf"