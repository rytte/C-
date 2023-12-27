/********************/打包/************************************************************/
QML项目打包
1.使用Release编译项目
2.复制生成的qml.exe文件到新建文件夹
3.打开Qt5.12.12命令行
4.进入新建文件夹，输入：windeployqt  qml.exe --qmldir "qml项目源码路径"
5.完成

如果需要修改QML源码
1.将项目中qml文件不放在qrc中
2.main.cpp文件中修改：const QUrl url(QStringLiteral("./QMLSource/main.qml"));
3.在新建文件夹中创建”QMLSource“文件夹，将qml源码放进去
4.完成

