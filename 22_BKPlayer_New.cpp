
//主函数
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);										//创建应用
	a.setQuitOnLastWindowClosed(false);								//设置当最后一个可见的主窗口关闭时，应用程序不退出

	MainWindow m;												//创建窗口
										
	//清理coredump文件
	ClearCoredumpFile("/media/nvme/log/coredump/", "bk_player", 1);		//清理临终文件

	string appName = "bk_player";
	YLogger::GetInstance()->SetAppName(appName);
	YLogger::GetInstance()->SetFileMaxSize(125);
	YLogger::GetInstance()->SetFileMaxCount(8);
	YLogger::GetInstance()->OpenFileOutput();

	//默认路径
	string planPath = "../AgentToPlayControl/play_plan/";
	string layoutPath = "../AgentToPlayControl/layout_template/";

	//如果有额外路径参数，则使用额外的路径，不使用默认路径
	if (argc > 1 && argv[1] != nullptr)
		planPath = argv[1];

	if (argc > 2 && argv[2] != nullptr)
		layoutPath = argv[2];

	m.SetLayoutPath(layoutPath);										//设置版式路径
	m.SetPlayPlanPath(planPath);										//设置播放计划路径，并读取播放计划表
													设置播放计划路径
													读取播放计划表
													{
														拼接播放计划JSON文件路径
														打开文件并转换为Json::Value格式
														读取键"startTime"、"endTime"的值并转换为时间戳，读取键"layoutName"的值，存入播表项信息结构体ItemListObj中
														并将ItemListObj存入m_layoutPlan动态数组

														如果有音量键信息
														则读取"startTime"、"endTime"、"value"同上
													}

	QApplication::setOverrideCursor(Qt::BlankCursor);					//隐藏鼠标

	YLOG_INFO("Version: %s", bk_version.c_str());						//打印版本号
	return a.exec();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow()
{
	m_strHeartBeatIp = "127.0.0.1";										//设置心跳IP			心跳：MainWindow子线程中每一秒发送一次信息到agent，接收agent响应超时则重启
	m_iHeartBeatPort = 6060;											//设置心跳端口号
	m_pHeartBeatHandle = YGlobCreateUdpSock(0);							//设置心跳UDP套接字

	m_strPlayPlanPath = "";												//初始化播放计划路径、布局路径、布局名称为空
	m_strLayoutPath = "";
	m_strLayoutName = "";
	m_strObjectName = "MainWindow";									//设置MainWindow对象名为"MainWindow"	（无用）
	m_layoutFileLastModified = QDateTime::currentDateTime();					//初始化布局文件最后修改时间为当前时间
	m_strLastTextInfo = "";

	m_bUseChange = YFALSE;											//中英文切换m_bUseChange初始化为false
	m_bChangeTimeout = YTRUE;										//中英文切换m_bChangeTimeout初始化为true
	m_iCurLanguage = 0;												//中英文切换m_iCurLanguage初始化为0中文
	m_strCurVolumeValue = "";											//初始化当前音量值为空

	m_windowLock = YGlobCreateLocker();									//创建并初始化锁m_windowLock
	m_pWindow = YNULL;												//初始化版式窗口m_pWindow = NULL	
	m_pBlackWindow = new YWindow();									//创建黑屏版式窗口对象						（ControlBase应单独派生窗口类使用）
													构造函数（此处无传参，因此无控件）
													{
														父控件指针 = NULL
														清空子控件对象map（控件ID, 子对象指针）
														清空属性参数map（控件ID，属性值）

														连接信号ShowSig()到show()槽函数
														连接信号HideSig()到hide()槽函数
														连接信号Update()到ShowControls()显示控件槽函数

														从Json提取控件参数默认值存入map表
														如果map中控件"name"对应值匹配则清空默认值（并隐藏该控件）
														通过名字辨别当前控件是否需要中英文切换
														根据传入的JSON表内容创建子控件（此处无传值，因此return不创建）					（定义Json::Value propertyJson作为YControlBase成员，可简化复杂传参）
														{
															new 天气信息模块
															{
																清空天气预警信息列表
																线程状态设为停
																创建线程Thread获取天气信息
																{
																	while (线程未退出)
																	{
																		获取当前时间戳
																		超时5s清空天气信息：天气预警信息列表，清空子控件内容，刷新显示控件
																		预警消息每1s滚动：清空子控件内容，设置属性，刷新显示控件
																		更新时间：最后时间戳=当前时间戳
																		初始化消息对象
																		注册消息
																		获取天气消息
																		解析节点数据，如果是天气信息
																		{
																			获取键"Weather"的值
																			清空子控件内容
																			设置控件内容
																			刷新显示控件
																			记录更新时间
																		}
																		否则如果是天气预警信息：清空列表，更新列表，更新记录
																	}
																}
															}
															new 滚动字幕模块
															{
																初始化成员
																创建动态图片帧循序缓冲区m_dynamicImageBuffer
																创建显示对象YDisplayManage
																{
																	初始化成员
																	连接信号UpdateSig()到UpdateSlot()槽函数
																	设置父指针
																}
																创建滚动图片对象YDynamicImage：初始化成员
																设置线程状态为停止
																创建线程Thread
																{
																	while (线程未退出)
																	{
																		设置滚动间隔为30ms
																		释放上一帧图片数据
																		检测内容更新，如果有更新则刷新显示页面
																		获取图像数据：记录更新时间、创建共享内存、获取数据并写入共享内存缓冲区、显示更新数据
																	}
																}
																创建线程ImageSynthesisThread
																{
																	while (线程未退出)
																	{
																		如果还有空缓冲区，则获取图像，设置内容
																		写入缓冲区
																	}
																}
															}
															new 到站信息模块
															{
																更新到站信息
																更新拥挤度信息
																更新列车时刻表信息
																注册消息对象
																创建线程Thread
																{
																	while (线程未退出)
																	{
																		初始化列车运行消息
																		超时清空
																		获取Json信息
																		收到ATS消息，记录当前时间
																		更新到站信息
																		更新拥挤度信息
																		更新列车时刻表信息
																		刷新界面
																	}
																}
															}
															new 拥挤度信息模块
															{
																初始化成员
																创建定时器m_pBlinkTimer
																连接信号timeout()到FlickerTimeout()槽函数
																连接信号PlatformDoorsSignal()到UpdatePlatformDoors()槽函数
																注册消息对象
																添加屏蔽门控件
																创建线程Thread
																{
																	while (线程未退出)
																	{
																		设置IP和端口号
																		超时清空页面
																		获取JSON消息
																		更新拥挤度信息
																		刷新页面
																	}
																}
															}
															new 时刻表信息模块
															{
																更新到站信息
																更新拥挤度信息
																更新列车时刻表信息
																注册消息对象
																创建线程Thread
																{
																	while (线程未退出)
																	{
																		设置IP和端口号
																		超时清空页面
																		获取JSON信息
																		更新列车时刻表信息
																		刷新页面
																	}
																}
															}
															new 媒体播放模块
															{
																视频区设置黑色背景
																初始化成员
																创建4个视频解码器：主流、帮主流、副帮主流、本地流
																{
																	初始化成员
																	创建4个循环缓冲区：视频未解码、音频未解码、视频已解码、音频已解码
																	创建分流线程//略
																	创建视频解码线程//略
																	创建音频解码线程//略
																}
																设置各流的解码模式
																创建音频播放//略
																创建视频渲染//略
																创建视频区滚动字幕//略
																创建线程Thread同步播放//略
															}
															new 日期时间模块
															{
																创建定时器m_pTimer
																连接信号timeout()到UpdateSlot()槽函数：获取m_childrenObjectMap中的日期时间并更新
																启动定时器(1s)
															}
															new 文本模块
															{
																创建定时器m_pTimer
																连接信号timeout()到UpdateSlot()槽函数
																启动定时器(30ms)
															}
														}
													}

	QDesktopWidget * pScreenWidget = QApplication::desktop();				//获取设备屏幕窗口
	QRect screenRect = pScreenWidget->screenGeometry();					//获取设备屏幕窗口大小screenRect
	m_pBlackWindow->SetProperty("name", "black_window");					//黑屏窗口增加控件属性
	m_pBlackWindow->SetProperty("positionX", to_string(screenRect.x()));		
	m_pBlackWindow->SetProperty("positionY", to_string(screenRect.y()));
	m_pBlackWindow->SetProperty("width", to_string(screenRect.width()));
	m_pBlackWindow->SetProperty("height", to_string(screenRect.height()));
	m_pBlackWindow->ShowControls();									//黑屏窗口显示控件
													ShowControls()
													{
														去除标题栏
														获取位置信息
														设置控件位置
														设置不透明度
														获取背景颜色信息，设置渐变背景色
														获取背景图片信息
														拼接路径
														设置控件样式
														显示子控件
													}
													
	m_pAgentText = new YAgentText();									//创建Agent文本对象（紧急/提示文本）。构造：清空成员文本消息Vector
	m_pAgentDynamicText = new YAgentText();								//创建Agent动态文本对象（紧急/提示文本）。构造：清空成员文本消息Vector

	m_dataBaseMap.clear();												//成员数据库Map清空
	m_layoutPlan.clear();												//成员版式计划Vector清空
	m_volumePlan.clear();												//成员音量计划Vector清空

	//线程状态
	m_threadState = THREAD_STOPED;									//线程状态设为停止

	//初始化Agent消息
	InitAgentMessage();												//初始化Agent消息
													创建Agent单例对象，构造函数
													{
														创建UdpJSON消息对象，构造
														{
															初始化组播参数为空
															创建锁
															创建3个缓冲区：发送JSON、接收JSON、接收字节。
															初始化成员线程状态为停止
															创建线程Thread（消息收发）
															{
																开启线程状态
																创建数组dataBuffer
																while (线程未退出)
																{
																	创建UdpSocket
																	清空dataBuffer
																	接收Udp消息到dataBuffer
																	如果接收字数合法，则写入接收字节缓冲区
																	否则处理消息：获取缓冲区内容并判断是否为JSON信息且完整，转为JSON格式并写入接收JSON缓冲区
																	当发送JSON缓冲区有内容时，将内容通过UdpSocket发送出去
																}
															}
														}
														创建发送缓冲区m_sendFifo
														初始化成员线程状态为停止
														创建线程ThreadRun
														{
															开启线程状态
															while (线程未退出)
															{
																接收JSON消息
																判断命令类型并写入循环缓冲区buffer
																当Agent消息发送缓冲区m_sendFifo有内容时，将缓冲区内容写入发送JSON缓冲区，会在上面Thread线程中发送出去
															}
														}
													}

													Agent初始化：成员UdpJson消息初始化：服务器、发送端口、接收端口初始化。
													Agent注册一堆消息
													{
														如果该消息对象已经存在，则判断命令消息是否存在，如果命令消息不存在则添加进消息对象的成员数组中去
														否则创建消息对象，并添加该命令消息
													}
		
	//连接信号槽
	connect(this, SIGNAL(CreateWindowSignal()), this, SLOT(CreateWindowSlot()));				//连接CreateWindowSignal()信号到CreateWindowSlot()槽函数

	//创建线程
	YGlobCreateThread(YTASK_PRIO_ATS_STATIONINFO_COMM, Thread, this);				//创建线程Thread（每1s获取一次版式）
}													



//线程函数//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
YTHREAD_FUN_DEF MainWindow::Thread(YVoid * pUserData)
{
	MainWindow * pThis = (MainWindow *)pUserData;					//获取MainWindow指针
	pThis->m_threadState = THREAD_RUN;							//开启线程状态
	YULong lastTick = 0;
	YULong lastChangeLanguageTick = 0;

	while (pThis->m_threadState > 0)									//while(线程未退出)
	{
		if (pThis->m_threadState == THREAD_STOPED)			
		{
			YGlobSleep(NOTHING_SLEEP_MS);
			continue;
		}
		else if (pThis->m_threadState == THREAD_NEED_STOP)
		{
			pThis->m_threadState = THREAD_STOPED;
			continue;
		}

		//创建版式
		YULong curTick = YGlobGetMillSecondTick();					//获取当前时间戳
		if (curTick - lastTick >= 1000)									//if 当前 - 最后时间戳 >= 1000ms，也就是每秒一次
		{
			//读取配置文件
			pThis->ReadConfigure();	
													读取配置文件	.. / AgentToPlayControl / play_plan / bk_configure.json
													{
														打开该JSON配置文件
														解析到 Json::Value configureJson
														从 configureJson 获取键值信息存入数据库m_dataBaseMap
													}

			//创建版式
			pThis->CreateWindowSignal();							//创建版式：发射CreateWindowSignal()；
													紧急版式标志位设置为 false
													if (数据库m_dataBaseMap中键"EmergencyLayoutName"的值不为空)
													{
														获取键"EmergencyLayoutName"的值作为版式名
														紧急版式标志位设置为 true
													}
													else
													{
														获取当前时间戳
														for (遍历m_layoutPlan容器)
														{
															如果当前时间戳 > 版式计划m_layoutPlan容器元素的起始时间 且 < 结束时间
															{
																临时版式名=元素值
																最后改变版式时间=元素最后改变时间
															}	
														}
													}
													如果临时版式名仍然为空，则将其指定为预设文件"Layout_preset.json"
													打开版式文件
													从数据库Map中获取资源文件路径
													if (JSON配置文件解析成功&&资源文件不为空)
													{
														创建新窗口，传入JSON配置和资源文件路径 pTmpWindow = new YWindow ( layoutJson, resourcePath );
														设置图片路径
														显示控件
														{
															去除标题栏
															获取坐标和长宽信息
															设置控件位置
															设置不透明度
															获取背景颜色信息
															设置渐变背景色
															获取背景图片信息
															拼接路径
															设置控件样式
															显示m_childrenObjectMap容器中子控件
														}
														检查和模块同等级的控件被覆盖的问题
														释放旧窗口
														判断当前版式是否为中英文切换版式
														记录当前显示的版式
														记录当前版式是不是紧急版式
													}

			//发送心跳
			pThis->SendHeartBeat();										//发送心跳：通过UdpSocket每一秒发送一次消息到agent

			//清理旧文件
			pThis->m_pSaveJsonFile->ClearTimeOutFileToLocal();				//清理旧文件

			//更新音量值
			YInt64 cur1970Tick = YGlobGetSecondsFrom1970();				//更新音量值
			for (YUInt32 index = 0; index < pThis->m_volumePlan.size(); index++)
			{
				ItemListObj curItem = pThis->m_volumePlan[index];
				if (cur1970Tick > curItem.startTime && cur1970Tick < curItem.endTime)
				{
					YInt32 volume = atoi(curItem.value.c_str());
					pThis->m_dataBaseMap["volume"].plan_value = to_string(volume >= 0 && volume <= 100 ? volume : 0);
					break;
				}
			}

			//记录时间戳
			lastTick = curTick;											//最后时间戳 = 当前时间戳	

			static int i = 0;
			i++;
			if (i % 5 == 0)
			{
				for (auto ptr : pThis->m_dataBaseMap)
				{
					std::cout << ptr.first << std::endl;
				}
			}
			std::cout << std::endl << std::endl;
		}

		if (pThis->m_bUseChange)										//如果需要改变语言，间隔在15s以上时则改变
		{
			if (TRANSFORM_LANGUAGE_INTERVAL <= YGlobGetMillSecondTick() - lastChangeLanguageTick)
			{
				pThis->m_bChangeTimeout = YTRUE;
				lastChangeLanguageTick = YGlobGetMillSecondTick();
			}
		}

		//接收Agent消息
		pThis->ReceiveAgentMessage();
													接收Agent消息
													{
													    获取Agent消息
														保存文件到本地对象
														判断信息头和信息体
														获取命令和信息

														if 读取播放计划（需确认命令）
														{
															拼接播放计划JSON文件路径		.. / AgentToPlayControl / play_plan / bk_play_plan.json
															打开JSON文件
															转为Json::Value格式 playPlanJson
															读取版式列表，存入动态数组Vector
															读取音量列表，存入动态数组Vector
														}
														else if 设置动态文本
														{
															如果显示模式为限定时间或定时显示
															{
																初始化起、止时间结构体
																起止时间转成1970年始时间戳字符串
															}
															如果显示模式为无限时，则将起止时间设为0
															查找文本是否存在，如果存在则返回，不存在则添加进m_agentTextMessage的Victor容器
														}
														else if 取消动态文本：遍历m_agentTextMessage容器，擦除对应消息文本
														else if 紧急消息 || 提示文本：添加动态文本，同时将消息体文本置空
														else if 按照文本ID撤销文本
														else if 改变媒体播放类型（直播、录播）：改变m_dataBaseMap的对应键值
														else if 按照类型撤销文本
														else if 设置音量：设置m_dataBaseMap音量键的值
														else if 查看音量：获取m_dataBaseMap音量键的值
														else if 设置亮度：设置m_dataBaseMap亮度键的值
														else if 查看亮度：获取m_dataBaseMap亮度键的值
														else if 显示预制图片（需确认命令）：设置m_dataBaseMap预置图片键的值为"presetPicture.jpg"
														else if 开启屏幕：设置m_dataBaseMap屏幕状态键的值为开
														else if 关闭屏幕：设置m_dataBaseMap屏幕状态键的值为关
														else if 全屏黑屏：设置m_dataBaseMap屏幕黑色状态键的值为开
														else if 取消黑屏：设置m_dataBaseMap屏幕黑色状态键的值为关
														else if 程序退出：给Agent发送消息，然后再退出
														将上面调整的消息发送给Agent
													}

		//响应更新消息
		if (pThis->m_strLayoutName != "")
			pThis->UpdateMessage();
													如果版式名不为空，响应更新消息
													{
														给列车运行消息模块设置站台信息（站台名称，运行方向）从m_dataBaseMap中获取值
														如果播放状态为关，则设置预置图片
														设置媒体音量，如果音量发生改变，则更新记录并将更新信息发送给Agent
													}
													设置直播、群主、副群主的流地址
													设置到站信息模块
													设置拥挤度模块
													设置时刻表模块
													设置天气模块
													获取紧急 / 提示文本
													//暂略

		//睡眠
		YGlobSleep(NOTHING_SLEEP_MS);
	}
	YTHREAD_RETURN;
}




									中英文切换：当m_bUseChange为true时，现在时间 - 最后一次修改语言时间 >= 15s则切换语言，那么在UpdateMessage函数中
										黑白屏、子控件、json文件


											YControlBase			//控件基类
											【公有函数】
											增加控件属性
											获取控件属性（字符型）
											获取控件属性（整型）
											设置图片路径
											获取父控件
											获取控件
											Json值转为字符串格式
											清空内容
											设置语言模式
											显示
											隐藏
											检查子控件的层级关系，将与子模块同级的子控件提升到顶层显示
											virtual 显示控件
											【信号】
											显示信号
											隐藏信号
											刷新信号
											【私有函数】
											设置位置
											设置样式
											递归遍历
											绘制事件
											添加子对象
											【私有类属性】
											父控件
											【保护成员】
											Map保存派生的子控件对象
											Map保存参数


										【m_dataBaseMap】
										如果键"EmergencyLayoutName"不为空则显示紧急版式
										如果版式名不等于键"CurLayoutName"的值 或 成员最后修改时间不等于临时最后修改时间，就刷新版式
										资源路径=键"resourcePath"的值的成员值
										键"DynamicTextID"的值的成员值=空
										键"CurTextId"的值的成员值=空
										键"CurLayoutName"的值的成员值=版式名
										如果是紧急版式，则键"isEmergencyLayout"的成员值=true ，否则=false
										从JSON配置文件中获取键值对共20对
										判断或改变键值

										CurLayoutName				//当前版式名
										EmergencyLayoutName			//紧急版式名
										Stream_Addr_1				//流地址1
										Stream_Addr_2				//流地址2
										Stream_Addr_3				//流地址3
										atsMessageAddr				//ATS信息IP地址
										atsMessagePort				//ATS信息端口号
										cameraAccess					//相机进入
										cameraUrl					//相机地址
										coach						//教授
										direction						//方向
										matrixInputUrl					//矩阵输入地址
										mediaPlayState				//媒体播放状态
										mediaPlayType				//媒体播放类型
										position						//位置
										resourcePath					//资源地址
										role							//角色
										screenSignal					//屏幕信号
										stationName					//站名
										volume						//音量
										weatherMessageAddr			//天气信息IP地址
										weatherMessagePort			//天气信息端口号
			





						开启线程状态
						while (线程未退出)
						{
							获取当前时间戳
							if (当前 - 最后时间戳 >= 1000ms)
							{
								读取配置文件	.. / AgentToPlayControl / play_plan / bk_configure.json
								{
									打开该JSON配置文件
									解析到 Json::Value configureJson
									从 configureJson 获取键值信息存入数据库m_dataBaseMap
								}
								创建版式：发射CreateWindowSignal()；
								{
									紧急版式标志位设置为 false
									if (数据库m_dataBaseMap中键"EmergencyLayoutName"的值不为空)
									{
										获取键"EmergencyLayoutName"的值作为版式名
										紧急版式标志位设置为 true
									}
									else
									{
										获取当前时间戳
										for (遍历m_layoutPlan容器)
										{
											如果当前时间戳 > 版式计划m_layoutPlan容器元素的起始时间 且 < 结束时间
											{
												临时版式名 = 元素值
												最后改变版式时间 = 元素最后改变时间
											}
										}
									}
									如果临时版式名仍然为空，则将其指定为预设文件"Layout_preset.json"
									打开版式文件
									从数据库Map中获取资源文件路径
									if (JSON配置文件解析成功&&资源文件不为空)
									{
										创建新窗口，传入JSON配置和资源文件路径 pTmpWindow = new YWindow(layoutJson, resourcePath);
										设置图片路径
										显示控件
										{
											去除标题栏
											获取坐标和长宽信息
											设置控件位置
											设置不透明度
											获取背景颜色信息
											设置渐变背景色
											获取背景图片信息
											拼接路径
											设置控件样式
											显示m_childrenObjectMap容器中子控件
										}
										检查和模块同等级的控件被覆盖的问题
										释放旧窗口
										判断当前版式是否为中英文切换版式
										记录当前显示的版式
										记录当前版式是不是紧急版式
									}
								}
								发送心跳：通过UdpSocket每一秒发送一次消息到agent
								清理旧文件
								更新音量值
								最后时间戳 = 当前时间戳
							}
							如果需要改变语言，间隔在15s以上时则改变
							接收Agent消息
							{
								获取Agent消息
								保存文件到本地对象
								判断信息头和信息体
								获取命令和信息

								if 读取播放计划（需确认命令）
								{
									拼接播放计划JSON文件路径		.. / AgentToPlayControl / play_plan / bk_play_plan.json
									打开JSON文件
									转为Json::Value格式 playPlanJson
									读取版式列表，存入动态数组Vector
									读取音量列表，存入动态数组Vector
								}
								else if 设置动态文本
								{
									如果显示模式为限定时间或定时显示
									{
										初始化起、止时间结构体
										起止时间转成1970年始时间戳字符串
									}
									如果显示模式为无限时，则将起止时间设为0
									查找文本是否存在，如果存在则返回，不存在则添加进m_agentTextMessage的Victor容器
								}
								else if 取消动态文本：遍历m_agentTextMessage容器，擦除对应消息文本
								else if 紧急消息 || 提示文本：添加动态文本，同时将消息体文本置空
								else if 按照文本ID撤销文本
								else if 改变媒体播放类型（直播、录播）：改变m_dataBaseMap的对应键值
								else if 按照类型撤销文本
								else if 设置音量：设置m_dataBaseMap音量键的值
								else if 查看音量：获取m_dataBaseMap音量键的值
								else if 设置亮度：设置m_dataBaseMap亮度键的值
								else if 查看亮度：获取m_dataBaseMap亮度键的值
								else if 显示预制图片（需确认命令）：设置m_dataBaseMap预置图片键的值为"presetPicture.jpg"
								else if 开启屏幕：设置m_dataBaseMap屏幕状态键的值为开
								else if 关闭屏幕：设置m_dataBaseMap屏幕状态键的值为关
								else if 全屏黑屏：设置m_dataBaseMap屏幕黑色状态键的值为开
								else if 取消黑屏：设置m_dataBaseMap屏幕黑色状态键的值为关
								else if 程序退出：给Agent发送消息，然后再退出
								将上面调整的消息发送给Agent
							}
							如果版式名不为空，响应更新消息
							{
								给列车运行消息模块设置站台信息（站台名称，运行方向）从m_dataBaseMap中获取值
								如果播放状态为关，则设置预置图片
								设置媒体音量，如果音量发生改变，则更新记录并将更新信息发送给Agent
							}
							设置直播、群主、副群主的流地址
							设置到站信息模块
							设置拥挤度模块
							设置时刻表模块
							设置天气模块
							获取紧急 / 提示文本
							//暂略
						}