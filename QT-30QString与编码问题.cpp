/********************/QString/************************************************************/
QString：string的派生类
1、方法fromUtf8()	将字符串转换为uft - 8格式。
2、格式化输出		QString str = QString("今天是%1年%2月%3日").arg(2023).arg(7).arg(5)



QString->String
QString qstr;
String str = qstr.toStdString();	  //QString转换为String
String str = qstr.toUtf8.constData(); //QString转换为String
String->QString
String str;
QString qstr = QString::fromStdString(str); //String转换为QString
QString转换为String中文输出乱码解决
QString path;
//QString转String 乱码解决
String cstr = String((const char*)path.toLocal8Bit());


//字符编码
UTF8(UTF8)
Local8Bits(本地系统的编码:GBK、ISO - 8859 - 1等)
Latin1(ANSI)


//Qt Creator 控制台输出中文乱码解决方法
1、工具 >> 选项 >> 文本编辑器 >> 勾选 "Display file encoding" >> Apply >> OK
2、点击右上角编码方式 >> 选择"System" >> Save with Encoding
3、解决

//Qt Creator 源码中文显示乱码
1、工具 >> 选项 >> 文本编辑器 >> 勾选 "Display file encoding" >> Apply >> OK
2、点击右上角编码方式 >> 选择"System" >> Load with Encoding
3、解决

