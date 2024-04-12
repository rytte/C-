/********************/工具链/************************************************************/
//MSYS2
MSYS2是一个包含MinGW - w64工具链、GNU工具集和一些开源库的平台，它提供了一种在Windows上编译和运行Unix / Linux程序的方式。
MSYS2与MinGW - w64相似，但比MinGW - w64更完整和稳定，提供了Pacman包管理器以方便用户安装和管理软件包。

//MinGW
MinGW - w64是一个Windows下的C / C++编程工具集，它提供了运行在Windows上的GNU工具集和GCC编译器。
MinGW - w64与MSYS2类似，但主要用于编译Windows本地应用程序，而非Unix / Linux程序。
MinGW - w64也可以用于交叉编译，为其他平台生成Windows可执行文件。

//Cygwin
Cygwin是一个在Windows平台上运行的兼容性层，提供了类Unix环境的工具和开发库。
Cygwin将Unix程序编译为Windows本地代码，然后在Windows上运行。
它提供了最完整的Linux / Unix环境，但相对于MSYS2和MinGW - w64，Cygwin的性能较差。

//比较
MSYS2适用于需要在Windows上编译和运行Unix / Linux程序的场景，
MinGW - w64适用于编译Windows本地应用程序的场景，
Cygwin适用于需要最完整的Linux / Unix环境的场景。


/********************/Pacman/************************************************************/
Pacman 是Arch Linux中的包管理工具，命令如下。

pacman - S 软件包名1 软件包名2 ...		//安装软件包及其依赖

pacman - R 软件包名				//卸载一个包，并且删除它的所有依赖。

pacman - Rs 软件包名				//卸载一个包，以及其不被其他包所需要的依赖项

pacman - Syu						//升级所有已安装的软件包

S 代表同步
y 代表更新本地存储库
u 代表系统更新

Q 选项查询本地包数据库
S 选项查询同步数据库
F 选项查询文件数据库

pacman - Ss 字符串1 字符串2 ...		//在数据库中搜索包，包括包的名称和描述

pacman - Qs 字符串1 字符串2 ...		//查找已经被安装的包

pacman - F 字符串1 字符串2 ...			//根据文件名在远程软包中查找它所属的包

pactree 软件包名					//查看一个包的依赖树

pacman 将其下载的包存储在 / var / cache / Pacman / pkg / 中，并且不会自动删除旧版本或卸载的版本

pacman - Sc						//删除当前未安装的所有缓存包和未使用的同步数据库

pacman - Scc						//从缓存中删除所有文件，请使用清除选项两次，这是最激进的方法，不会在缓存文件夹中留下任何内容

pacman - U 本地软件包路径.pkg.tar.xz	//安装不是来自远程存储库的“本地”包，即第三方的包

pacman - U http://www.example.com/repo/example.pkg.tar.xz	//安装官方存储库中未包含的“远程”软件包









