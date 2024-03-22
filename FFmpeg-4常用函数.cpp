/*************************/初始化/***************************************************************************/


void avdevice_register_all(void);			//对设备进行注册。如果我们要捕捉屏幕进行录制屏幕，捕捉摄像头进行录制视频，捕捉麦克风录制麦克风声音时，就需要使用到该函数，首先进行注册。例如（windows下的dshow，Linux下的V4L2等）

初始化libavDevice并注册所有输入和输出设备



int avformat_network_init(void);			//初始化网络库以及网络加密协议相关的库，推流或者拉流时会使用到

执行网络库的全局初始化。这是可选的，不再推荐使用。
此函数仅用于解决旧版GNUTLS或OpenSSL库的线程安全问题。
如果libavFormat链接到这些库的较新版本，或者如果您不使用它们，则不需要调用此函数。
否则，您需要在启动使用该函数的任何其他线程之前调用该函数。
一旦删除对较旧的GNUTLS和OpenSSL库的支持，此函数将被弃用，并且此函数将不再有任何用途。




/*************************/日志/***************************************************************************/

void av_log(void* avcl, int level, const char* fmt, ...) av_printf_format(3, 4);			//打印消息

如果级别小于或等于当前的av_log_Level，则向日志发送指定的消息。默认情况下，所有日志记录消息都发送到stderr。可以通过设置不同的日志回调函数来更改此行为。
@请参阅av_log_set_allback。
@param avcl指向任意结构的指针，其第一个字段是指向AVClass结构的指针，如果是常规日志，则为NULL。
@param Level使用@ref LAVU_LOG_CONSTANTS“记录常量”表示的消息的重要性级别。
@param fmt指定如何将后续参数转换为输出的格式字符串(与printf兼容)。



/*************************/解码/***************************************************************************/

AVPacket* av_packet_alloc(void);							//分配一个AVPacket内存

分配一个AVPacket并将其字段设置为默认值。
结果结构必须使用av_Packet_Free()来释放。
@返回包含缺省值的AVPacket，失败则返回空。
@NOTE这只会分配AVPacket本身，不会分配数据缓冲区。
这些必须通过其他方式进行分配，例如av_new_Packet。
@查看av_new_Packet



AVFormatContext* avformat_alloc_context(void);				//创建格式上下文，返回 AVFormatContext *

分配AVFormatContext。
AvFormat_Free_CONTEXT()可用于释放上下文和所有内容。
由其中的框架分配。



int avformat_open_input(AVFormatContext** ps, const char* url,          //打开输入文件，并关联格式上下文
        const AVInputFormat* fmt, AVDictionary** options);

打开输入流并读取头。
编解码器未打开。
必须使用avFormat_Close_Input()关闭流。
@param ps指向用户提供的AVFormatContext的指针(由avFormat_Alloc_Context分配)。
可以是指向空的指针，在这种情况下，此函数将分配AVFormatContext并将其写入ps。
请注意，用户提供的AVFormatContext将被释放。
在失败时。
@param要打开的流的url URL。
@param fmt如果非空，则此参数强制使用特定的输入格式。否则将自动检测该格式。
@param选项用AVFormatContext和demuxer私有选项填充的字典。返回时，此参数将被销毁，并替换为包含未找到的选项的字典。
可以为空。
@如果成功则返回0，如果失败则返回负值。
@note如果您想使用自定义IO，请预先分配Format上下文并设置其PB字段。



int avformat_find_stream_info(AVFormatContext* ic, AVDictionary** options);             //上下文获取流信息

读取媒体文件的包以获取流信息。
这对于没有标头的文件格式(如mpeg)非常有用。
这函数还计算在MPEG - 2重复帧模式下的实际帧速率。此函数不改变逻辑文件位置；检查的包可能会被缓冲以供以后处理。
@param ic媒体文件句柄。
@param Options如果不为空，则为指向字典的ic.nb_stream长指针数组，其中第i个成员包含与第i个流对应的编解码器选项。返回时，每个字典将填充未找到的选项。
@Return >= 0如果正常，则错误时返回AVERROR_xxx。
@note此函数不能保证打开所有编解码器，因此选项在返回时为非空是非常正常的行为。
@TODO让用户以某种方式决定需要什么信息，这样我们就不会浪费时间获取用户不需要的东西。






