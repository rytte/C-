
//主函数
int main(int argc, char *argv[])
{
	QApplication application(argc, argv);						//创建应用

	printf("\n");
	printf("Version:%s\n", BK_PLAYER_VERSION);				//打印版本号
	printf("\n");

	//clear coredumpfiles
	ClearCoredumpFile("/tmp/", "bk_player", 1);					//清理临终文件

	MainWindow window;									//创建窗口
										构造函数
										{
											成员变量赋值
											心跳地址初始化
											new UDP套接字
											创建音频数据缓冲区
											创建循环控制缓冲区块
											创建视频共享内存：初始化一些属性

											new 共享音频缓冲区
											new 共享音频结构体
											new 音频转换器结构体
										}

	std::string strPlayPanPath;								//定义字符串接收传入参数
	std::string strPlayContentPath;
	std::string strXmlStylePath;
	std::string strSysLogAddress;

	if (argc >= 5)											//如果有传入路径则使用指定路径
	{
		strPlayPanPath = argv[1];   //播放计划的路径
		strPlayContentPath = argv[2];
		strXmlStylePath = argv[3];
		strSysLogAddress = argv[4]; //SysLog服务的IP
	}
	else {												//否则使用默认路径
		if (argc > 1 && argc < 5)
		{
			printf("Start Commond line error, programme will exit\n");
			return 0;
		}

		printf("\n****\n\tNot Set start commond parameter, Use the defaut parameter!\n****\n");
		strPlayPanPath = "../AgentToPlayControl/detailed_arrangement";		//播放计划的路径
		strPlayContentPath = "../AgentToPlayControl/content_template";
		strXmlStylePath = "../AgentToPlayControl/layout_template";
#ifdef linux
		strSysLogAddress = "10.18.2.129";
#endif
	}

#ifdef linux
	YGlobInitSysLog(strSysLogAddress, "Bk_Player");				//初始化SysLog服务
	//写播控版本号
	YGlobWriteSysLog("上传播控版本号", BK_PLAYER_VERSION, SYSLOGLEVEL::INFO_LOG, LOGTYPE::RUN_LOG, LOGACTIONTYPE::SYSVERSION_ACTION);
#endif
	window.Init(strPlayPanPath, strPlayContentPath, strXmlStylePath, true);		//传入参数初始化主窗口
	QApplication::setOverrideCursor(Qt::BlankCursor);						//隐藏鼠标
	return application.exec();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
YVoid MainWindow::Init(const std::string & strPlayPanPath, const std::string & strPlayContentPath, const std::string & strXmlStylePath, bool useGpu)
{
	YGlobSetCurrentThreadPrio(YTASK_PRIO_UI);							//设置当前线程优先级

	YAgentMsgManager::Instance().Init("127.0.0.1", 4040, 7070);				//创建静态成员Agent并为其初始化
											创建发送缓冲区m_sendFifo和接收缓冲区m_readFifo
											初始化服务器IP和收发端口号
											创建线程（收发数据）
											while(线程未退出)
											{
												定义局部dataBuffer接收和cSendBuffer发送缓冲区
												分发数据：DistributeMsg()
												{
													检查json消息完整性
													遍历消息结构体数组中的每一字符串数组，如果已有该字符串消息&&成员m_msgFifo还能够写入，则直接将接收的消息写入m_msgFifo
												}
												接收数据：从udp套接字读取数据写入m_readFifo
												发送数据（如果发送缓冲区有数据）
												{
													检测消息完整性
													读取cSendBuffer缓冲区内容并发送
												}
											}

	YAgentMsgManager::Instance().RegisterMsg(m_strMsgSubscriberName, "LIST_FRAME_LOSS_RATIO");			//Manager调用RegisterMsg注册消息:“列表帧丢失率”
	YAgentMsgManager::Instance().RegisterMsg(m_strMsgSubscriberName, "VIDEO_PLAY_FINISH_MESSAGE");		//Manager调用RegisterMsg注册消息:“视频播放结束消息”
											判断接收到消息且合法，则属性获取消息，否则初始化订阅者消息结构体
											
	m_pPlayPanModule = YGlobCreatePlayPanManage();				//创建播放计划类对象：初始化成员变量和网络设置，重置文本信息数据
	m_pPlayPanModule->SetPlayPanPath(strPlayPanPath);			//设置播放计划路径，并读取日期播表数据：日期，站名和当前车厢位置、播控身份、文本等数据
	m_pPlayPanModule->SetPlayContentPath(strPlayContentPath);		//设置内容路径
	m_pPlayPanModule->Init();									//Agent初始化
											注册一堆消息：对消息结构体m_msgSubscribers数组成员的赋值
											更新播放内容（20230912.json文件解析）
											{
												获取时间、列表ID、版式、播放内容
												解析内容模板JSON文件
												解析ATS信息
												解析模式
												视频播放选择
												打包紧急信息、提示信息、紧急滚动文本
												各种信息打包
											}
											创建线程
											while (线程未退出)
											{
												接收UDP数据并解析JSON 更新紧急信息：UdpReceiveHandle()
												{
													读取消息
													校验数据的包头包尾
													解析命令消息
												}
											}
								
	YGlobSleep(200);        //等200ms，让每秒播放计划控制部分，先执行

	//记录配置文件路径，创建窗口对象，创建并初始化ATS与Weather模块
	m_strPlayPanPath = strPlayPanPath;							//设置播放计划路径
	m_strXmlStylePath = strXmlStylePath;							//设置Xml样式路径
	m_pScreenManager = YGlobGetWndManager()					//创建窗口对象
											初始化成员
											初始化列车信息
											初始化天气信息
											初始化天气警告信息
											清除列车拥挤度信息
		
	InitAtsAndWeatherMoudle();									//初始化ATS和天气模块
											初始化成员
											获取ATS和天气信息
											创建ATS客户端对象：初始化成员
											设置ATS客户端的服务器信息
											启动ATS模块
											{
												解析site_list.json文件
												判断json文件是否有数据，获取ID和站点名
												创建线程
												{
													创建不同UDP套接字
													循环
													{
														判断播控身份，选择接收对应的ATS信息（组播或单播数据）(site:地面播控 / train : 车载播控)
														未收到则睡眠（sleep->continue）
														判断消息完整性
														转换为json数据
														解析节点数据
													}
												}
											}
											获取站名列表
											创建天气客户端对象：初始化成员
											设置天气客户端属性和【回调函数】
											成员对象窗口工厂结构体初始化：初始化变量和脸帧循环缓冲区

	//第一路视频流
	m_pMultiMediaDecodeServerStream = YGlobCreateMultiMediaDecode();					//创建Server流解码对象
	m_pMultiMediaDecodeServerStream->SetDecodeMode(YInterfaceMultiMediaDecode::DECODE_MODE_VIDEO_AND_AUDIO);	//设置解码模式
	m_pMultiMediaDecodeServerStream->SetDecodedAFrameCallback(CallbackWriteVideoFrameToSharedBuffer, this);			//设置m_callBackFun为解码一帧的【回调函数】

	m_pMultiMediaDecodeLeaderStream = YGlobCreateMultiMediaDecode();					//创建Leader流解码对象
	m_pMultiMediaDecodeLeaderStream->SetDecodeMode(YInterfaceMultiMediaDecode::DECODE_MODE_ONLY_CHECK_NET);	//设置解码模式
	m_pMultiMediaDecodeLeaderStream->SetDecodedAFrameCallback(CallbackWriteVideoFrameToSharedBuffer, this);			//设置m_callBackFun为解码一帧的【回调函数】

	m_pMultiMediaDecodeViceLeaderStream = YGlobCreateMultiMediaDecode();				//创建ViceLeader流解码对象
	m_pMultiMediaDecodeViceLeaderStream->SetDecodeMode(YInterfaceMultiMediaDecode::DECODE_MODE_ONLY_CHECK_NET);	//设置解码模式
	m_pMultiMediaDecodeViceLeaderStream->SetDecodedAFrameCallback(CallbackWriteVideoFrameToSharedBuffer, this);		//设置m_callBackFun为解码一帧的【回调函数】

	m_pMultiMediaDecodeLocalFile = YGlobCreateMultiMediaDecode();						//创建LocalFile本地文件流解码对象
											初始化一堆成员属性
											初始化4个循环缓冲区并获取指针（未解码视频包，未解码音频包，已解码视频包，已解码音频包）
											创建分流线程
											{
												循环读取流中数据，放入待解码缓冲区
												{
													如果收到 COMMAND_RESET 或 COMMAND_RESTART 命令，则释放资源
													{
														数据重新排序
														设置属性
														等待线程退出
														清除4个循环缓冲区的帧数据
														停止视频解码
														停止音频解码
														关闭上下文句柄
													}
													准备开始（分流）
													{
														打开一个流
														获取流信息
														找到视频流和音频流
														创建视频流解析器：设置解码器类型，av_bitstream_filter_init初始化过滤器
														视频流：打开并配置解码器，计算每个pts对应的秒数，设置视频时间基和各参数
														音频流：打开并配置解码器，设置音频时间基和各参数
														重置m_pAvPacket队列缓冲区
														如果是UDP媒体类型
														{
															设置补包参数
															设置音频区间
														}
													}
													循环（分流线程运行）
													{
														有命令则打断播放，continue
														如果有视频流，视频待解码的缓冲区满了，continue，等待解码线程去解码
														如果有音频流，音频流待解码的缓冲区满了，continue，等待解码线程去解码
														如果读不到数据，continue
														如果补包模块发现数据出错，则需要重启解码器，continue
														如果是视频流
														{
															读取一个包
															如果需要增加到整理队列中去，增加进去，否则，增加到待解码缓冲区
															pAvPacket使用后释放
														}
														否则如果是音频流
														{
															读取一个包
															如果需要增加到整理队列中去，增加进去，否则，增加到待解码缓冲区
															pAvPacket使用后释放
														}
													}
												}
											}
											创建视频解码线程
											{
												循环
												{
													本地文件读取过快，需要延时控制速度
													如果当前模式为只解码音频或仅检测网络，则关闭视频解码器，否则开启视频解码器
													如果存放未解码数据的缓冲区是否为空，则等待两秒 continue
													如果存放已解码数据的缓冲区是否已满，如果满了则等待空了再解
													如果读到了数据，继续读数据，先回调写入共享内存，再存入循环缓冲
													读一个avpacket，进行解码//略
												}
											}
											创建音频解码线程
											{
												循环
												{
													本地文件读取过快，需要延时控制速度
													如果当前模式为只解码视频或仅检测网络，则关闭音频解码器，否则开启音频解码器
													如果存放未解码数据的缓冲区是否为空，则等待两秒 continue
													如果存放已解码数据的缓冲区是否已满，如果满了则等待空了再解
													读取read循环缓冲区，若读到数据
													{
														如果为只解视频或检测网络 { 如果能回调解码前的音频数据，则调用该函数，否则释放未解码数据 }
														如果能回调解码前的音频数据，复制包数据并解码
														如果发送解码包解码成功，则进入循环进行解码，解码完毕或缓冲区满则跳出循环
														释放包
													}
												}
											}
											设置延时ms
	m_pMultiMediaDecodeLocalFile->SetDecodedAFrameCallback(CallbackWriteVideoFrameToSharedBuffer, this);		//设置m_callBackFun为解码一帧的【回调函数】

	m_bUseGpu = useGpu;						//使用GPU

	//创建转码器
	m_pSwsHandle = YGlobCreateYuvAndRgbSws();							//创建转码器：创建YYuvAndRgbSws图片转码结构体并初始化成员变量

	//创建共享内存
	m_pCaptureScreen = new YSharedVideoFrame();							//创建视频帧共享内存结构体（截屏）
	m_pSharedVideo = new YSharedVideoFrame();							//创建视频帧共享内存结构体（共享视频）
	m_pScrollSharedVideo = new YSharedVideoFrame();						//创建视频帧共享内存结构体（滚动共享视频）
	m_pSecondSharedVideo = new YSharedVideoFrame();						//创建视频帧共享内存结构体（第二共享视频）
	m_pSharedBufferHandle = YGlobCreateSharedBuffer(FIRST_VIDEO_SHM_KEY);						//创建共享循环缓冲区
	m_pSharedBufferHandle_ScrollText = YGlobCreateSharedBuffer(SCROLL_TEXT_SHM_KEY);			//创建共享循环缓冲区（滚动文字）
	m_pSharedBufferHandle_CaptureScreen = YGlobCreateSharedBuffer(CAPTURE_SCREEN_SHM_KEY);	//创建共享循环缓冲区（截屏）

#ifdef debian
	//第二路视频流
	m_pMultiMediaDecodeServerStreamSecond = YGlobCreateMultiMediaDecode();
	m_pMultiMediaDecodeServerStreamSecond->SetDecodeMode(YInterfaceMultiMediaDecode::DECODE_MODE_VIDEO);
	m_pMultiMediaDecodeServerStreamSecond->SetDecodedAFrameCallback(CallbackWriteSecondVideoFrameToSharedBuffer, this);

	m_pMultiMediaDecodeLocalFileSecond = YGlobCreateMultiMediaDecode();
	m_pMultiMediaDecodeLocalFileSecond->SetDecodedAFrameCallback(CallbackWriteSecondVideoFrameToSharedBuffer, this);
	m_pMultiMediaDecodeLocalFileSecond->SetEnableAutoDecode(YTRUE);

	//创建第二路视频的共享内存
	m_pSharedBufferHandle_SecondVideo = YGlobCreateSharedBuffer(SECOND_VIDEO_SHM_KEY);

	//创建转码器
	m_pSecondVideoSwsHandle = YGlobCreateYuvAndRgbSws();

	//初始化RKDrm显示
	RKDrmInit();
	RKDrmSetDisplayMode(YFALSE);
	//初始化RGA转码
	Rga_Init();
#endif

	connect(&m_1000msTimer, SIGNAL(timeout()), this, SLOT(Timer1000msHandle()));						//连接1000ms定时器槽函数	//***********
	connect(this, SIGNAL(sig_40msTimeout()), this, SLOT(Timer40msHandle()), Qt::QueuedConnection);			//连接40ms超时槽函数		//***********
	connect(this, SIGNAL(sig_AtsTimeout()), this, SLOT(AtsWndUpdate()), Qt::QueuedConnection);				//连接ATS超时槽函数		//***********
	connect(this, SIGNAL(sig_WeatherTimeout()), this, SLOT(WeatherWndUpdate()), Qt::QueuedConnection);	//连接天气超时槽函数		//***********
#ifdef debian
	connect(this, SIGNAL(sig_SecondVideo40msTimeout()), this, SLOT(SecondVideoTimer40msHandle()), Qt::QueuedConnection);
#endif

	YGlobOpenPlayAudio(44100, 2, CallbackAudioFetchData, this);										//打开音频播放
											初始化AudioOutput（SDL）音频输出结构体，设置各个音频对象参数，m_callBack变量设为传入的【回调函数】
											（#ifdef debian）创建线程循环播放音频数据
											{
												计算 块 = 字节数 / 周期数据大小
												调用CallbackAudioFetchData【回调函数】
												{
													获取当前多媒体解码视频流
													获取音频帧最大字节	
													循环（缓冲中等待播放的声音帧数>0；缓冲区空余个数>= 音频帧最大字节）
													{
														获取音频帧
														{
															处理声音缓冲过多的情况，并删除过多的数据
															返回音视频同步后的帧
															{
																读取m_circleBufAudioFrame循环缓冲区一帧数据
																循环遍历：如果该音视频帧不合理（如太多了）则释放掉，否则返回该帧
															}
														}
														设置共享音频结构体变量
														写入该帧到m_pSharedBufferHandle_Audio共享音频循环缓冲区
														该帧进行重采样，转码：创建转码结构体并设置成员变量，进行转码，返回转码后的音频帧
														将转码后的音频帧写入m_pAudioDataBuf循环缓冲区
														读取m_pAudioDataBuf循环缓冲区一帧数据并返回
													}
												}
											}

	//车载控制模块
	m_pTrainControlManageObj = new YTrainControlManage();			//************
	m_pTrainControlManageObj->SetTrainConfigPath(strPlayPanPath);		//************

	//播放屏的开关控制
	m_pScreenEquipmentControl = new ScreenControlManage();
	m_pScreenEquipmentControl->ScreenControlInit(ScreenControlManage::PHILIPS_3451D_SCREEN);

	//LCD屏显示管理
	m_pLcdDisplayManageObj = new LcdDisplayManage();
	m_pLcdDisplayManageObj->Init("/dev/ttyVIZ1", 9600, 0xff);
	m_pLcdDisplayManageObj->Start();
#ifndef WIN32
	m_pLcdDisplayManageObj->AddDisplayContent("IpAddress:", YGlobGetLocalDeviceIP());
#endif

	m_pVideoPlayTimerTick = YGlobStartVideoPlay(CallbackPlayVideoFetchData, CallbackPlayScrollText, this);
	m_pScrollTextPlayHandle = YGlobStartScrollTextPlay(CallbackPlayScrollText, this);
	m_pEmergencyScrollTextPlayHandle = YGlobStartScrollTextPlay(CallbackPlayEmergencyScrollText, this);

	//先执行一次后，再启动定时器
	Timer1000msHandle();
	Timer40msHandle();
#ifdef debian
	SecondVideoTimer40msHandle();
#endif

	m_ScreenRect = QApplication::desktop()->screenGrometry();
	m_1000msTimer.start(1000);
}