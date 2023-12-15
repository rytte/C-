
//主函数
YInt32 main(YInt32 argc, YChar *argv[])
{
	QApplication application(argc, argv);						//创建应用

	MainWindow window;									//创建窗口
							、、1、MainWindow成员属性初始化、ffmpegLib初始化
							、、2、音频数据缓冲区初始化


	printf("Version:V300R001C00B15\n");						//打印版本号

	//清理临终文件，保留最新2个
	ClearCoredumpFile("/tmp/", "ops_player", 1);				//清理临终文件，保留最新2个

	//ops通信初始化
	window.m_OpsClient.Init();								//ops通信初始化，创建线程不断接收消息
							、、1、打开并读取config.json数据赋值给YOpsClient成员属性
							、、2、传入读取到的成员属性初始化成员类指针m_pMsgClient（YMsgClient）
							、、3、m_pMsgClient初始化：成员属性赋值，初始化读写队列，开启线程循环
											线程循环：首轮：清理资源（关闭amqp通道和连接）、
														创建连接（创建amqp新连接和通道套接字、amqp套接字非阻塞打开）
														初始化通道（打开通道、创建队列、设置消费信息参数）
													 循环：获取可发送数据、发送数据、接收消息到接收缓冲区	//在OPSClient定时器中处理接收的消息


	if (window.m_OpsClient.m_opsConf.m_strOps_mode == "rdp")			//如果是远程控制模式，则拼接字符串并执行指令
	{
		YChar strConnect[512] = "";
		sprintf(strConnect, "xfreerdp --ignore-certificate --rfx -a 32 -f -u %s -p %s --plugin rdpsnd --data pulse -- %s",
			window.m_OpsClient.m_opsConf.m_strFreeRDP_name.c_str(),
			window.m_OpsClient.m_opsConf.m_strFreeRDP_pass.c_str(),
			window.m_OpsClient.m_opsConf.m_strFreeRDP_ip.c_str());
		printf("Start remote server connection command:%s\n", strConnect);

		system(strConnect);
	}
	else															//否则，初始化MainWindow主窗口，调用时传入读取到的YOpsClient成员属性初始化MainWindow成员属性
	{
#ifndef debian
		window.Init(window.m_OpsClient.m_opsConf.m_strInput_filename_net, window.m_OpsClient.m_opsConf.m_vInputfilename_local, false);
#else
		window.Init(window.m_OpsClient.m_opsConf.m_strInput_filename_net, window.m_OpsClient.m_opsConf.m_vInputfilename_local, true);
#endif
	}															

	return application.exec();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
YVoid MainWindow::Init(const std::string & strMultiMediaNetPath, const std::vector<std::string> & strMultiMediaLoacalPath, bool useGpu)
{
	QRect screenRect = QApplication::desktop()->screenGeometry();			//获取屏幕位置大小
	m_pScreenFactory = YGlobCreateWndFactory();							//创建YWndCreate（创建对象并返回指针）
	m_pScreenFactory->Init(screenRect.width(), screenRect.height());			//传入获取的屏幕位置大小初始化YWndCreate
							创建PlayerVideo对象（主窗口）
							{
								设置PlayerVideo界面属性
								调用YGlobCreateYuvAndRgbSws()
								{
									创建YYuvAndRgbSws结构体
									{
										清空结构体
										创建信号量并初始化锁
									}
									通过传入参数，对结构体的变量m_supportFrameNum（最大帧数）赋值
								}
							}
							设置PlayerVideo属性
							显示界面


	YGlobSleep(200);        //等200ms，让每秒播放计划控制部分，先执行

	m_strMultiMediaLoacalFile = strMultiMediaLoacalPath;					//使用形参赋值
	m_strMultiMediaNetPath = strMultiMediaNetPath;						//使用形参赋值

	m_pMultiMediaDecodeLocalFile = YGlobCreateMultiMediaDecode();			//创建YMulitiMediaDecode本地多媒体解码对象
	m_pMultiMediaDecodeNetStream = YGlobCreateMultiMediaDecode();		//创建YMulitiMediaDecode网络多媒体解码对象
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


	m_useGpu = useGpu;					//使用GPU

	m_pMultiMediaDecodeNetStream->SetSourceFileName(m_strMultiMediaNetPath.c_str());						//设置源文件名：检测"\"和"\""和"\n"并消除，确定多媒体文件类型
	m_pMultiMediaDecodeNetStream->SetRequestFrameServer(m_OpsClient.m_opsConf.m_strPatchFrame_ip, 1235);		//设置请求帧服务器：传参设置服务器IP和端口号。接收端口号、组播IP、代理服务器IP、代理服务器端口号为默认
	m_pMultiMediaDecodeNetStream->Start(m_useGpu);														//开始：m_useGpu = bUseCuda;	m_userCommand = COMMAND_RESTART;

#ifdef debian
	RKDrmInit();
#endif

	connect(&m_1000msTimer, SIGNAL(timeout()), this, SLOT(Timer1000msHandle()));						//连接1000ms定时器槽函数
	connect(this, SIGNAL(sig_40msTimeout()), this, SLOT(Timer40msHandle()), Qt::QueuedConnection);			//连接40ms超时槽函数

	m_videoPlayTimerTick = YGlobStartVideoPlay(CallbackPlayVideoFetchData, YNULL, this);					//开始视频播放（传入回调函数）
							创建YPlayVideoUserData结构体
							结构体变量赋值
							结构体变量m_videoCallBack=回调函数（获取播放视频数据）{ 未传参则返回√，传参则执行40ms定时器函数 }
							结构体变量m_circleBufHandleScrollTextInfo=初始化循环缓冲区
							创建视频播放线程，传入结构体
							{
								设置基本属性
								循环
								{
									获取当前时间戳
									根据用户设置的interval绘制一帧视频：如果发送回调时间间隔>=1且最后一次回调时间+时间间隔<= 当前时间戳：传入结构体执行回调函数（40ms定时器函数）、最后一秒时间戳 += 时间间隔
									等待2ms
								}
							}
							创建滚动字幕播放线程，传入结构体
							{
								设置基本属性
								循环
								{
									获取当前时间戳
									滚动字幕绘制间隔固定：如果回调函数存在且最后一次回调时间+滚动间隔<= 当前时间戳
									{
										循环绘制
										等待2ms
									}
								}
							}

	//先执行一次后，再启动定时器
	Timer1000msHandle();													//执行1000ms定时器函数
							收发消息：获取ats模块获取ats信息的json描述
							{
								循环（读到消息）
								{
									消息头类型（命令）
									{
										消息体类型：握手指令、开屏指令、关屏指令、关机指令、复位指令、查询CPU占有率、查询内存使用率、查询硬盘使用率、查询OPS屏幕开关状态、切换网络流地址、手动切播放模式
									}
								}
							}
							读取改变播放源信息（切换网络流地址时做的改变）
							如果屏幕状态为关，则涂黑
							如果是本地播放模式
							{
								设置解码流资源
							}
							否则为网络播放模式
							{
								如果网络超时5000ms且小于6000ms...，则重设网络流
								如果网络恢复了，则重设为音视频解码
							}
							如果当前是本地播放
							{
								解码本地文件设为结束，然后再设为开始 
							}
							调用窗口创建模块，获取当前窗口对象


	Timer40msHandle();													//执行40ms超时函数
							根据当前是流媒体，还是本地媒体，确定从哪个源头，取视频流和音频流
							判断视频数据是否可以取到，如果可以取到，设置图像大小，设置视频帧数，将视频数据拷贝到当前的窗口对象中
							判断音频数据是否可以取到，如果可以取到，启动播放声音


	m_1000msTimer.start(1000);												//开启定时器，间隔为1000ms

	YGlobOpenPlayAudio(44100, 2, CallbackAudioFetchData, this);					//打开音频播放（传入回调函数）
							初始化音频对象，设置各个音频对象参数
							创建线程循环播放音频数据

	YGlobChangeAudioVolume(100);											//设置音量大小为100
}




循环缓冲区：read从文件读取出一个avpacket包，再send到解码器缓冲区，多余的包写入待解码缓冲区。receive取出解码器解完的avframe帧，播放出来，未播放的帧写入已解码缓冲区。