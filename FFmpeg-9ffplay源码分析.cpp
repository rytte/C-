/*************************/ffplay源码分析（version 6.1）/***************************************************************************/
;
struct AVInputFormat {};
struct  FrameQueue{};
struct PacketQueue{};
struct Clock{};
struct SDL_Thread{};
struct SDL_cond {};
struct AVFormatContext{};


struct VideoState
{
	char* filename;					//文件名
	const struct AVInputFormat* iformat;	//输入文件格式

	FrameQueue pictq;					//视频帧队列
	FrameQueue subpq;				//字幕帧队列
	FrameQueue sampq;				//音频帧队列

	PacketQueue audioq;				//音频包队列
	PacketQueue subtitleq;				//字幕包队列
	PacketQueue videoq;				//视频包队列

	Clock audclk;						//音频时钟
	Clock vidclk;						//视频时钟
	Clock extclk;						//未知时钟

	int audio_volume;					//音量
	int av_sync_type;					//同步类型（默认音频同步）
	int eof;							//结束标志

	AVFormatContext* ic;				//输入文件上下文

	enum ShowMode {
		SHOW_MODE_NONE = -1, SHOW_MODE_VIDEO = 0, SHOW_MODE_WAVES, SHOW_MODE_RDFT, SHOW_MODE_NB
	} show_mode;						//显示模式

	SDL_Thread* read_tid;				//读取线程
	SDL_cond* continue_read_thread;		//条件变量
};



void main()
{
	初始化设备等;
	解析命令行参数;
	初始化SDL;

	is = stream_open(input_filename, file_iformat);		
	{
		创建视频 / 音频 / 字幕的帧与包的数据缓存队列;
		初始化 VideoState 结构体;
		创建读取线程 read_thread;
	}

	处理由图形用户界面发送的事件		event_loop(is);
}


static int read_thread(void* arg)
{
	输入参数处理;
	解码流程;
}





重要结构体;
VideoState;
AVFormatContext;
