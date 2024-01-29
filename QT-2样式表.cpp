/********************/样式表/************************************************************/

//资源
工程中添加 QT Resource File 文件。在该文件中添加资源路径。

样式设计：
color : "#00ff00";								//设置对象颜色
border - image:url(: / 1.jpg);					//设置背景图片，图片随控件大小缩放
background - image:url(: / 1.jpg);				//设置背景图片，图片不随控件大小缩放
QLineEdit{ border:10px solid#ff00ff };			//LineEdit设置边框颜色
QLineEdit{ border - radius:5px solid#ff00ff };	//LineEdit设置边框圆角

派生类对象：
类名#对象名{ 样式设计 }				//UI界面中，当前对象的派生类对象，使用此格式设置。

动作样式：
类名#对象名:动作名{ 样式设计 }		//动作名：例如要在按键按下时显示图片：QPushButton#login_bt:pressed{ border-image:url(:/1.jpg); }

代码实现：
ui->对象名->setStyleSheet("样式设计""样式设计"...)		//可以同时设计多个样式，也可以使用字符串拼接后传入一个字符串。


复选框样式表：
remember->setStyleSheet("QCheckBox{color:rgb(150,150,150);}"                                        //字体框
        "QCheckBox::indicator::unchecked{ border:2px solid#dddddd;border-radius:3px; background-color:white; }"                  //未选中
        "QCheckBox::indicator::checked{ border:2px solid#dddddd; border-radius:3px; background-image:url(:/png/tick.png); }");   //已选中
