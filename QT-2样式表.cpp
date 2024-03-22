/********************/样式表/************************************************************/
样式表用于设置控件外观，将会作用于其所有子控件。

//代码格式
对象名->setStyleSheet("样式设计""样式设计"...)		//可以同时设计多个样式，也可以使用字符串拼接后传入一个字符串。

//样式设计
不同属性间使用分号分隔
"color : #00ff00;"                				                //设置对象颜色
"color : rgb(240,240,240)"                                               //设置对象颜色
"background-color : red;"                                               //设置背景颜色
"border-image : url(:/1.jpg);"				                //设置背景图片，图片随控件大小缩放，资源文件用冒号":"表示
"background-image : url(:/1.jpg);"			                //设置背景图片，图片不随控件大小缩放
"QLineEdit{ border : 10px solid#ff00ff };"		        //LineEdit设置边框颜色
"QLineEdit{ border-radius : 5px  solid#ff00ff };"             //LineEdit设置边框圆角
"QCheckBox[checked = true]"                                        //只对被勾选的checkbox生效

//指定对象（父子控件关系）
涉及到的类名只能使用Q_OBJECT声明的才有效。若自定义的类不含Q_OBJECT，则需要填写其继承的含Q_OBJECT声明的父类类名。
".QLabel { color : red }"(待验证)                     //应用于自己。                   条件：为QLabel类型或QLabel子类的对象
"QLabel { color : red }"                                  //应用于自己和所有子控件。条件：为QLabel类型或QLabel子类的对象
"#aa { color : red }"                                       //应用于自己和所有子控件。条件：对象名(ObjectName)为aa的对象
"QLabel#aa { color : red }"                            //应用于自己和所有子控件。条件：为QLabel类型或QLabel子类，且对象名(ObjectName)为aa的对象
"QLabel>QPushButton { color : red }"          //应用于直接子控件。          条件：作用于QLabel控件内部的一级QPushButton控件
"QLabel  QPushButton { color : red }"          //应用于所有子控件。          条件：作用于QLabel控件内部的所有QPushButton控件
"QLabel>#aa { color : red }"                         //应用于直接子控件。          条件：作用于QLabel控件内部的一级对象名(ObjectName)为aa的控件
"QLabel  #aa { color : red }"                         //应用于所有子控件。          条件：作用于QLabel控件内部的所有对象名(ObjectName)为aa的控件

//逗号
多个选择器可以指定同一个声明，使用逗号分隔选择器，例如：
"#aa, #bb { color : red }"                               //应用于自己和所有子控件。条件：对象名(ObjectName)为aa和bb的对象
"QLabel, QPushButton { color : red }"           //应用于自己和所有子控件。条件：为QLabel、QPushButton类型或QLabel、QPushButton子类的对象

//动作样式
类名#对象名:动作名{ 样式设计 }		             //动作名：例如要在按键按下时显示图片：QPushButton#login_bt:pressed{ border-image:url(:/1.jpg); }

//复选框样式表
setStyleSheet("QCheckBox{color:rgb(150,150,150);}"                                                                                                                      //字体框
        "QCheckBox::indicator::unchecked{ border:2px solid#dddddd;border-radius:3px; background-color:white; }"                    //未选中
        "QCheckBox::indicator::checked{ border:2px solid#dddddd; border-radius:3px; background-image:url(:/png/tick.png); }");   //已选中

//QTableWidget样式表
setStyleSheet("QTabBar::tab { width: 149px; height: 60px;background-color:white;color:rgb(120,120,120);}"
        "QTabBar::tab:selected{ color:rgb(75,75,110); border-bottom:2px solid#4b4b6e; }"
        "QTabBar::tab:hover{ color:rgb(0,0,0) }");


//边框样式
border - style:groove / ridge / double / inset / outset


//通过文件加载QSS
工程中添加 QT Resource File 文件。在该文件中添加资源路径。后缀.qss。

QFile file(":/styles.qss");
if (file.open(QFile::ReadOnly | QFile::Text)) 
{
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
}



