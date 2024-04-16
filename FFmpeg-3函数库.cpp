/*************************/ffmpeg函数库/***************************************************************************/
#include "ffmpeg.h"
libavutil
核心工具库，例如log模块。下面很多功能模块都会依赖该库作一些基本的音视频处理操作。

libavformat
一个包含了所有的普通音视格式的解析器和产生器的库。文件格式和协议库，该模块是最重要的模块之一，封装了Protocol层和Demuxer、Muxer层。

libavcodec
一个包含了所有FFmpeg音视频编解码器的库。为了保证最优性能和高可复用性，大多数编解码器从头开发的。

libswresample
该模块用于音频重采样，可以对数字音频进行声道数、数据格式、采样率等多种基本信息进行转换。例如：把一段音频的声道由双声道转换成单声道的数据，就可以通过该库进行操作。

libswscale
该模块提供了将图像进行格式信息转换的模块。例如：可以将YUV数据转换成RGB数据，可以将1280720的尺寸的数据缩放尺寸至800480的数据。

libavfilter
音视频滤镜库，该库提供了音频和视频特效的处理功能。在使用FFmpeg的API进行编解码的过程中，直接使用该模块为音视频数据做特效处理是非常方便同时也非常高效的一种方式。

libavdevice
输入输出设备库。需要编译出播放声音或者视频的工具ffplay，就需要确保该模块是打开的。编译时需要先编译SDL，因为此库是依赖SDL的，该设备模块库播放声音与播放视频使用的都是SDL库。

libpostproc
该年模块用于后期处理，当我们使用AVFilter的时候需要打开该模块的开关，因为Filter中会使用到该模块的一些基础函数。

swresample
该模块可用于音频重采样，可以对数字音频进行声道数、数据格式、采样率等多种基本信息的转换。

swscale
该模块是将图像进行格式转换的模块。比如，可以将YUV的数据转换为RGB的数据，缩放尺寸由1280720变为800480。



/*************************/ffmpeg常用函数简介/***************************************************************************/
//设备相关函数 libavdevice
avdevice_register_all				对设备进行注册。如果我们要捕捉屏幕进行录制屏幕，捕捉摄像头进行录制视频，捕捉麦克风录制麦克风声音时，就需要使用到该函数，首先进行注册。例如（windows下的dshow，Linux下的V4L2等）
avdevice_list_devices				列出可用的音视频设备
avdevice_get_input_list				获取输入设备列表
avdevice_get_output_list				获取输出设备列表
avdevice_open						打开设备
avdevice_close						关闭设备
avdevice_capabilities_create			创建设备参数对象
avdevice_capabilities_free			释放设备参数对象
avdevice_list_input_sources			列出输入源
avdevice_list_output_sinks			列出输出接口
avdevice_list_formats				列出设备支持的音视频格式
avdevice_read_packet				从设备读取音视频包
avdevice_write_packet				向设备写入音视频包
avdevice_version					获取libavdevice库的版本号


//封装格式相关函数	libavformat
avformat_alloc_context				创建格式上下文，返回 AVFormatContext *
avformat_open_input				打开输入文件，并关联格式上下文
avformat_find_stream_info			上下文获取流信息
avformat_seek_file					根据时间戳定位文件的位置；例如我们托方播放器的进度条进行快近和快退时，就可以使用此函数进行定位播放
avformat_free_context				释放不使用的AVFormatContext的内存
avformat_close_input				关闭解复用器。关闭后可以不使用avformat_free_context()进行释放
avformat_write_header				写入封装格式头部
avformat_write_trailer				写入封装格式尾部
avformat_new_stream				创建新的音视频流
avformat_version					获取libavformat库的版本号
avformat_network_init				初始化网络库以及网络加密协议相关的库，推流或者拉流时会使用到
avformat_alloc_output_context2		分配输出格式上下文

avio_open2						打开封装格式的IO上下文
avio_close						关闭封装格式的IO上下文
av_stream_get_end_pts				获取流的结束时间戳
av_stream_get_r_frame_rate			获取流的帧率
av_guess_frame_rate				猜测帧率
av_dump_format					音视频文件的协议封装解析
av_find_best_stream				获取流索引，返回索引值


//编解码相关函数 libavcodec
avcodec_alloc_context3				创建编解码器上下文，返回 AVCodecContext *
avcodec_parameters_to_context		编解码器上下文获取流中编解码器信息。（将AVStream流里面的参数直接复制到AVCodecContext的上下文当中）
avcodec_parameters_from_context		从编解码器上下文中获取编码器参数。
avcodec_find_decoder				根据ID查找解码器
avcodec_find_encoder				根据ID查找编码器
avcodec_find_decoder_by_name		根据解码器名字查找解码器
avcodec_open2					打开编解码器并关联到解码器上下文
avcodec_send_frame				向编解码器发送原始数据帧
avcodec_send_packet				向编解码器发送编码数据包
avcodec_receive_frame				从编解码器接收解码数据帧		//每次调用都会对AVFrame分配data[]缓冲区并保存解码数据；每一次使用后，必须需要使用av_frame_unref释放缓冲区，否则重复解码会造成内存泄露。最后，需要使用av_frame_free 释放整个对象。
avcodec_receive_packet				从编解码器接收编码数据包
avcodec_free_context				释放解码器上下文，此函数包含了avcodec_close()
avcodec_close						关闭解码器
avcodec_get_name					获取编解码器名称
avcodec_get_type					获取编解码器类型
avcodec_parameters_alloc			创建编解码器参数
avcodec_parameters_free			释放编解码器参数对象
avcodec_parameters_copy			复制编解码器参数
avcodec_error_to_string				将错误代码转换为字符串
av_packet_alloc					分配一个AVPacket内存


//通用函数 libavutil
av_log							打印消息
av_log_get_level					返回当前Log等级
av_log_set_level					设置当前Log的级别
av_strerror						打印报错原因
av_malloc							申请内存，返回申请到的内存
av_strdup							复制字符串
av_read_frame						读取一帧数据，读取的是一个AVPacket包
av_seek_frame						在媒体文件中进行帧级别的跳转定位
av_gettime						获取当前时间戳
av_gettime_relative					获取相对时间戳
av_rescale_q						按比例转换时间戳
av_usleep							延时us
av_memcpy_backptr				从后向前拷贝内存
av_fast_malloc						快速分配内存
av_stristart						检查字符串前缀
av_stristr							在字符串中查找子字符串，忽略大小写
av_get_token						从输入字符串中提取标记
av_strcasecmp						比较字符串，忽略大小写
av_codec_get_name				获取编解码器名称
av_codec_get_tag2					获取编解码器四字节参数
av_samples_get_buffer_size			获取给定音频参数所需的缓冲区大小
av_get_default_channel_layout		获取当前声道布局中的声道数目

av_dict_set						设置AVDictionary的键值对
av_dict_get						获取AVDictionary的键值对，并从字典中删除
av_dict_free						释放AVDictionary的堆内存

av_frame_alloc						创建数据帧，返回 AVFrame *
av_frame_clone					克隆数据帧，返回 AVFrame *
av_frame_free						释放数据帧
av_frame_unref					释放帧数据data
av_frame_get_buffer				分配缓冲区
av_frame_get_best_effort_timestamp	获取最佳时间戳
av_frame_copy						复制帧数据
av_frame_copy_props				复制帧属性
av_packet_unref					减少 AVPacket 对 编码数据的引用次数。减到 0 会释放 编码数据的内存。
av_packet_free						释放 AVPacket 自身的内存。里面会调 av_packet_unref

av_image_get_buffer_size			获取图像字节大小
av_image_fill_arrays					分配缓冲区的内存

av_clipl_int32						对整数进行范围限制
av_clipf							对浮点数进行范围限制
av_log2							计算以2为底的对数
av_gcd							计算最大公约数
av_be2ne16						将大端字节序转换为本地字节序
av_be2ne32						将大端字节序转换为本地字节序


//视频转换 libswscale
sws_alloc_context					为 SwsContext 结构体分配内存
sws_init_context					初始化 SwsContext 结构体
sws_getContext					创建图像缩放上下文，返回 SwsContext *
sws_freeContext					释放图像缩放上下文
sws_scale							缩放和转换图像
sws_setColorspaceDetails			设置颜色空间细节
sws_getCachedContext				获取图像缩放上下文的缓存
sws_convertPalette8ToPacked32		将8位调色板转换为32位色彩
sws_setColorspaceDetails			设置颜色空间细节
sws_strerror						获取错误消息字符串
swscale_version					获取libswscale库的版本号


//音频转换 libswresample
swr_alloc							创建音频重采样上下文
swr_free							释放音频重采样上下文
swr_init							初始化音频重采样上下文
swr_convert						进行音频重采样
swr_config_frame					设置输入 / 输出音频帧的参数
swr_set_compensation				设置音频重采样补偿
swr_alloc_set_opts					设置输入 / 输出音频帧的参数并创建音频重采样上下文，返回 SwrContext *
swr_convert_frame					进行音频重采样并输出音频帧
swr_get_delay						获取重采样的延迟
swr_inject_silence					注入静音样本
swresample_strerror				获取错误消息字符串
swresample_version				获取libswresample库的版本号

//过滤器 libavfilter
avfilter_register_all					注册所有可用的滤镜
avfilter_graph_alloc					创建滤镜图
avfilter_graph_free					释放滤镜图
avfilter_graph_parse2				解析滤镜图的字符串描述
avfilter_get_by_name				通过名称获取滤镜
avfilter_graph_create_filter			创建滤镜实例
avfilter_init_str						初始化滤镜参数
av_buffersrc_add_frame				向输入缓冲区添加帧数据
av_buffersink_get_frame				从输出缓冲区获取帧数据
avfilter_inout_alloc					创建输入输出结构
avfilter_inout_free					释放输入输出结构
avfilter_graph_config				配置滤镜图
avfilter_version					获取libavfilter库的版本号








