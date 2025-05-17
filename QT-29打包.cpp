/********************/打包/************************************************************/

//图标
1、将图标图片（.ico格式）放入资源文件中（可以一起打包）
2、setWindowIcon(QIcon(":/cover.ico")); 设置窗口图标
3、源目录下新建txt文件，输入一行内容 IDI_ICON1 ICON DISCARDABLE "cover.ico" , 改文件名为cover.rc
4、pro文件中加入一行 RC_FILE += cover.rc
5、执行qmake、重新构建，完成。

//设置exe程序名称
可在.pro文件中添加一行：
TARGET = name
name就是输出的exe文件名称。

//打包
1、使用Release编译项目
2、复制生成的exe文件到新建文件夹
3、新建文件夹中打开Qt5.12.12命令行，输入："windeployqt project.exe"
4、完成

//压缩
1、下载安装Enigma Virtual Box工具
2、EVB：打开exe文件
3、EVB：修改打包后的文件名
4、EVB：添加文件夹（递归）【Add...->Add Folder Recursive】，选择打包的文件夹，点击OK
5、选项中勾选压缩文件【Files Options->Compress File->OK】
6、点击Process开始打包
7、完成





