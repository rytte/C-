/********************/HDC工具/************************************************************/

//hdc组成
hdc client：运行于电脑上的客户端，用户可以命令终端下请求执行hdc命令。
hdc server：作为后台进程也运行于电脑上，server管理client和设备端daemon之间通信包括连接的复用、数据通信包的收发，以及个别本地命令的直接处理。
hdc daemon：daemon部署于OpenHarmony设备端作为守护进程按需运行，负责处理来自client端请求

整体架构和Android系统的ADB架构非常类似。

aa(Ability Assistant) 主要用于操作和管理设备中的应用程序能力，例如启动应用组件、强制停止进程、打印应用组件相关信息等。
bm(Bundle Manager) 主要用于操作和管理系统中的应用 Bundle（应用包和相关资源）。


//设备管理
"-t"参数：即目标设备，多设备连接的情况下需要指定设备编号

hdc shell					//进入shell命令行
hdc shell <shell命令>		//执行shell命令
hdc -v						//查看版本号
hdc list target				//查看设备编号列表，-v参数可显示详细信息
hdc shell bm get --udid		//查询设备udid
hdc target boot				//重启设备
hdc - kill					//停止hdc server
hdc start - r				//重启hdc server

hdc shell hidumper - s RenderService - a screen	//获取屏幕信息
hdc shell hidumper - s BatteryService - a - i	//获取电量/温度
hdc shell ifconfig								//获取IP信息
hdc shell hidumper - s PowerManagerService - a - s	//查看亮屏状态
hdc shell power - shell wakeup					//屏幕唤醒
hdc shell hidumper - s NetConnManager			//查看网络状态
hdc shell hidumper - s WifiDevice				//查看wifi信息


//应用管理
hdc shell bm dump - a					//获取应用列表
hdc install <appName.hap>				//安装应用
hdc uninstall <appName>					//卸载应用
hdc shell aa dump - l					//获取运行中的应用信息
hdc shell aa start - a EntryAbility - b <appName>	//启动应用
hdc shell aa force - stop <appName>		//退出应用
hdc shell bm dump - n <appName>			//获取应用配置信息json
hdc shell bm clean - h					//清除应用数据相关命令
hdc jpid								//显示可调试应用列表
hdc track-jpid							//动态显示可调试应用列表。


//系统工具
hdc shell aa help		//aa工具
hdc shell bm help		//bm工具
hdc shell param			//param工具
hdc shell aa test - h	//用例测试工具

hdc hilog - h				//系统日志相关
hdc shell hidumper - h		//hidumper工具相关
hdc shell hidumper - s DisplayManagerService	//显示管理服务
hdc shell hidumper - s PowerManagerService		//电源管理服务
hdc shell hidumper - s BatteryService			//电池服务
hdc shell hidumper - s NetConnManager			//网络连接服务


//aa dump命令
hdc shell aa dump <-参数>
"-h, --help"                   //列出可用的命令
"-a, --all"                    //全部转储所有能力
"-l, --mission-list"           //转储任务列表
"-i, --ability"                //转储能力记录
"-e, --extension"              //转储元素名称(FA: serviceAbilityRecords，Stage: ExtensionRecords)
"-p, --pending"                //转储pendingWantRecordId
"-r, --process"                //转储进程
"-d, --data"                   //转储数据能力
"-u, --userId"                 //用户ID（辅助参数，不能单独使用）
"-c, --client"                 //客户端（辅助参数，不能单独使用）


//bm dump命令
hdc shell bm dump < -参数>
"-h, --help"                     //列出可用命令
"-a, --all"                      //列出系统中的所有包
"-n, --bundle-name <appName>"	 //按包名列出包信息
"-s, --shortcut-info"            //列出快捷方式信息
"-d, --device-id <deviceId>"     //指定设备id
"-u, --user-id <userId>"         //指定用户id


//文件传输
hdc file send <local> <remote>		//从本地发送文件至远端设备
hdc file recv <remote> <local>		//从远端设备发送文件至本地


//端口转发
命令							说明
hdc fport ls				展示全部“端口转发主机端口转发数据到设备侧端口”的转发任务
hdc fport local remote		端口转发主机端口转发数据到设备侧端口
hdc fport rm local remote	删除指定“端口转发主机端口转发数据到设备侧端口”的转发任务
hdc rport ls				展示全部“端口转发设备侧端口转发数据到主机端口”的转发任务
hdc rport local remote		端口转发设备侧端口转发数据到主机端口
hdc rport rm local remote	删除指定“端口转发设备侧端口转发数据到主机端口”的转发任务


//系统参数查询
hdc shell param get <系统参数>

系统参数							接口名										描述
const.product.devicetype		const char* GetDeviceType(void)				//返回当前设备类型
const.product.manufacturer		const char* GetManufacture(void)			//返回当前设备生产厂家信息
const.product.brand				const char* GetBrand(void)					//返回当前设备品牌信息
const.product.name				const char* GetMarketName(void)				//返回当前设备传播名
const.build.product				const char* GetProductSeries(void)			//返回当前设备产品系列名
const.product.model				const char* GetProductModel(void)			//返回当前设备认证型号
const.software.model			const char* GetSoftwareModel(void)			//返回当前设备内部软件子型号
const.product.hardwareversion	const char* GetHardwareModel(void)			//返回当前设备硬件版本号
const.product.hardwareprofile	const char* GetHardwareProfile(void)		//返回当前设备硬件profile
ohos.boot.sn					const char* GetSerial(void)					//返回当前设备序列号（SN号）
const.product.software.version	const char* GetDisplayVersion(void)			//返回当前设备用户可见的软件版本号
const.product.bootloader.version	const char* GetBootloaderVersion(void)	//返回当前设备Bootloader版本号
const.product.udid				int GetDevUdid(char* udid, int size)		//获取设备udid（先通过参数获取，获取失败通过计算获取）
								const char* AclGetSerial(void);				//返回当前设备序列号（SN号）（带访问权限检查）
								int AclGetDevUdid(char* udid, int size);	//获取设备udid（带访问权限检查）
const.product.cpu.abilist													//返回CPU架构


//UI操作模拟
UI模拟操作(点击滑动等)
支持操作类型：点击 双击 长按 慢滑 快滑 拖拽 输入文字 KeyEvent

配置参数名		配置参数含义			示例
click			模拟单击操作			hdc shell uitest uiInput click point_x point_y
doubleClick		模拟双击操作			hdc shell uitest uiInput doubleClick point_x point_y
longClick		模拟长按操作			hdc shell uitest uiInput longClick point_x point_y
fling			模拟快滑操作			hdc shell uitest uiInput fling from_x from_y to_x to_y swipeVelocityPps_ stepLength
swipe			模拟慢滑操作			hdc shell uitest uiInput swipe from_x from_y to_x to_y swipeVelocityPps_
drag			模拟拖拽操作			hdc shell uitest uiInput drag from_x from_y to_x to_y swipeVelocityPps_
dircFling		模拟指定方向滑动操作	hdc shell uitest uiInput dircFling direction swipeVelocityPps_ stepLength
inputText		模拟输入框输入文本操作	hdc shell uitest uiInput inputText point_x point_y text
keyEvent		模拟实体按键事件(如:键盘, 电源键, 返回上一级, 返回桌面等), 以及组合按键操作	hdc shell uitest uiInput keyEvent keyID

//UI操作模拟举例
hdc shell uitest uiInput click 100 100				// 点击
hdc shell uitest uiInput doubleClick 100 100		// 双击
hdc shell uitest uiInput longClick 100 100			// 长按
hdc shell uitest uiInput fling 10 10 200 200 500	// 快滑
hdc shell uitest uiInput swipe 10 10 200 200 500	// 慢滑
hdc shell uitest uiInput drag 10 10 100 100 500		// 拖拽
hdc shell uitest uiInput dircFling 0 500			// 左滑
hdc shell uitest uiInput dircFling 1 600			// 右滑
hdc shell uitest uiInput dircFling 2				// 上滑
hdc shell uitest uiInput dircFling 3				// 下滑
hdc shell uitest uiInput inputText 100 100 hello	// 输入框输入
hdc shell uitest uiInput keyEvent Home				// 返回主页
hdc shell uitest uiInput keyEvent Back				// 返回上一步
hdc shell uitest uiInput keyEvent 2072 2038			// 组合键粘贴操作


//屏幕截图
"hdc shell snapshot_display -f /data/local/tmp/1.jpeg"	//（推荐，截图性能高）截图完成后可以通过 hdc file recv 命令导入到本地
"hdc shell uitest screenCap"							// 默认存储路径：/data/local/tmp，文件名：时间戳 + .png。
"hdc shell uitest screenCap -p /data/local/tmp/1.png"	// 指定存储路径和文件名。



