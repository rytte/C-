
//主函数
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);										//创建应用

	ClearCoredumpFile("/media/nvme/log/coredump/", "bk_video_forward", 1);			//清理临终文件

	std::string tpath = QCoreApplication::applicationDirPath().toLocal8Bit().data();			//获取应用程序目录路径
	tpath = tpath + "/plugins";													//拼接应用程序插件路径
	QApplication::addLibraryPath(QString::fromLocal8Bit(tpath.c_str()));					//添加库路径

	std::string tEncoderName = "";												//定义编码类型字符串
#ifdef linux
	tEncoderName = "UTF-8";													//编码类型为UTF-8
#else
	tEncoderName = "GB2312";													//编码类型为GB2312	
#endif
	QTextCodec *codec = QTextCodec::codecForName(tEncoderName.c_str());				//定义编解码器
	QTextCodec::setCodecForLocale(codec);										//使用本机编码

	YMonitorManageService monitorManage;										//创建监控管理对象
												构造函数
												{
													ffmpeg初始化
													初始化Agent消息
													{
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
													}

													设置音频采样率和视频帧率
													创建视频捕获
													{
														创建图片合成，构造函数
														{
															初始化输入缓冲区
															设置输出属性
															创建视频转码器
															拷贝输出缓冲区
															初始化输出缓冲区
															初始化成员
															创建线程ThreadSynthesis图像合成线程//略
															创建线程ThreadScale输出到监控端线程//略
														}
														创建YScreenShot屏幕拍摄
														{
															初始化成员
															创建视频管道包缓冲区
															创建线程ThreadScreenShot//略
														}
														创建YCutBlockTranscode剪切转码块
														{
															初始化成员
															创建输入和输出缓冲区
															创建线程ThreadTranscode//略
														}
														创建4个共享缓冲区
														创建视频转码器
														创建线程Image1SwsScaleThreadFun//略
														创建线程Image2SwsScaleThreadFun//略
														创建线程Image3SwsScaleThreadFun//略
														创建线程Image4SwsScaleThreadFun//略
														创建线程ThreadVideoCapture//略
													}
												}
	if (argv[1] != nullptr)														
		monitorManage.Init(argv[1]);												//如果有参数，则传入参数初始化
	else
		monitorManage.Init();													//否则，使用默认参数初始化
	monitorManage.Start();														//开启线程状态

	YLOG_INFO("build bk_video_forward on %s", bk_video_forward_version.c_str());			//打印版本号

	return a.exec();	
}