/*************************/ffmpeg常用结构体/***************************************************************************/
#include "ffmpeg.h"

AVIOContext，URLProtocol，URLContext主要存储视音频使用的协议的类型以及状态。
URLProtocol存储输入视音频使用的封装格式。每种协议都对应一个URLProtocol结构。（注意：FFMPEG中文件也被当做一种协议“file”）

常用结构体如下;

AVFormatContext		封装格式上下文结构体，统领全局的结构体，保存了视频文件封装格式等相关信息;
AVInputFormat		输入的format，封装格式（例如：FLV、MP4），每个封装格式都对应一个该结构体;
AVOutputFormat		输出的format，例如：输出到网络流，输出到文件等;
AVIOContext			管理输入输出数据的结构体;
AVStream			一个视频容器（即文件）中存在多路流数据，每路流都对应一个该结构体，例如：视频流、音频流、字幕流等;
AVCodecParameters	编解码器参数结构体;
AVCodecContext		编解码器上下文结构体，保存了音视频编解码相关的信息;
AVCodec				每一种音视频编解码器（例如：H.264解码器）都对应一个该结构体;
AVPacket				存储一帧压缩编码数据;
AVFrame				存储一帧解码后的数据（可以是视频解码后的像素数据，也可以是音频采样后的数据）;

struct AVDictionary {};
struct AVRational {};
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int int16_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;



/*************************/AVFormatContext;/***************************************************************************/
struct AVFormatContext			//封装格式上下文结构体
{
	struct AVInputFormat* iformat;			输入的格式结构体;
	struct AVOutputFormat* oformat;			输出的格式结构体;
	AVIOContext* pb;						输入数据的缓存;
	unsigned int nb_streams;				音视频流的个数;
	AVStream** streams;					输入流的AVStream[]数组;
	int64_t duration;						音视频的时长（单位：微秒us，转换为秒需要除以1000000）;
	int  bit_rate：							音视频的码率（单位bps，转换为kbps需要除以1000）;
	AVDictionary* metadata;					元数据;
};

视频的元数据（metadata）信息可以通过 AVDictionary 获取。元数据存储在AVDictionaryEntry结构体中，是一种key - value对的格式;
struct AVDictionaryEntry
{
	char* key;
	char* value;
};

在ffmpeg中通过av_dict_get()函数获得视频的元数据信息。

第一种方式，提取存在的、特定的键值对信息
AVDictionaryEntry* m = NULL;
m = av_dict_get(pFormatCtx->metadata, "author", m, 0);
printf("作者：%s\n ", m->value);
m = av_dict_get(pFormatCtx->metadata, "description", m, 0);
printf("描述：%s\n ", m->value);

另外一种是循环遍历所有的数据
while (m = av_dict_get(pFormatCtx->metadata, "", m, AV_DICT_IGNORE_SUFFIX))
{
	printf("%s\t:%s\r\n", m->key, m->value);
}



/*************************/IO;/***************************************************************************/
struct AVInputFormat			//输入的format结构体
{
	const char* name;						封装格式名称;
	const char* extensions;					封装格式的扩展名;
	int raw_codec_id;						封装格式ID;
	一些封装格式处理的接口函数, 比如read_packet()
};

struct AVOutputFormat			//输出的format结构体
{
	const char* name;						复⽤器名称;
	const char* long_name;					格式的描述性名称，易于阅读;
	enum AVCodecID audio_codec;			默认的⾳频编解码器;
	enum AVCodecID video_codec;			默认的视频编解码器;
	enum AVCodecID subtitle_codec;			默认的字幕编解码器;
	封装名称描述
		编码格式信息（video / audio 默认编码格式，支持的编码格式列表）
		对封装的操作函数（write_header, write_packet, write_tailer等）
};

struct AVIOContext				//管理输入输出的结构体
{
	unsigned char* buffer;					缓存开始位置;
	int buffer_size;							缓存大小（默认32768）;
	unsigned char* buf_ptr;					当前指针读取到的位置;
	unsigned char* buf_end;					缓存结束的位置;
	void* opaque;							URLContext结构体;
};



/*************************/AVStream;/***************************************************************************/
struct AVStream				//流信息结构体
{
	int index;								标识该视频 / 音频流;
	AVCodecContext* codec;				指向该视频 / 音频流的AVCodecContext（它们是一一对应的关系）;
	AVRational time_base;					该流的时基，通过该值可以把PTS，DTS转化为真正的时间。PTS* time_base = 真正的时间（秒）;
	int64_t duration;						该视频 / 音频流长度;
	AVDictionary* metadata;					元数据信息;
	AVRational avg_frame_rate;				该流的帧率;
	AVPacket attached_pic;					附带的图片。比如说一些MP3，AAC音频文件附带的专辑封面。
};



/*************************/Codec;/***************************************************************************/
struct AVCodecParameters		//编解码器参数结构体
{
	enum AVMediaType codec_type;			媒体类型，比如AVMEDIA_TYPE_VIDEO AVMEDIA_TYPE_AUDIO等;
	enum AVCodecID codec_id;				编解码器类型， 比如AV_CODEC_ID_H264AV_CODEC_ID_AAC等;
};

struct AVCodecContext			//编解码器上下文结构体
{
	enum AVMediaType codec_type;			编解码器的类型（视频，音频...）;
	struct AVCodec* codec;					采用的解码器AVCodec（H.264, MPEG2...）;
	int bit_rate;							平均比特率;
	uint8_t* extradata; int extradata_size;		针对特定编码器包含的附加信息（例如对于H.264解码器来说，存储SPS，PPS等）;
	AVRational time_base;					根据该参数，可以把PTS转化为实际的时间（单位为秒s）;
	int width, height;						如果是视频的话，代表宽和高;
	int refs;								运动估计参考帧的个数（H.264的话会有多帧，MPEG2这类的一般就没有了）;
	int sample_rate;						采样率（音频）;
	int channels;							声道数（音频）;
	enum AVSampleFormat sample_fmt;		采样格式;
	int profile;							型（H.264里面就有，其他编码标准应该也有）;
	int level;								级（和profile差不太多）;
};

struct AVCodec				//音视频编解码器结构体
{
	const char* name;							编解码器的名字，比较短;
	const char* long_name;						编解码器的名字，全称，比较长;
	enum AVMediaType type;					指明了类型，是视频，音频，还是字幕;
	enum AVCodecID id;						ID，不重复;
	const AVRational* supported_framerates;		支持的帧率（仅视频）;
	const enum AVPixelFormat* pix_fmts;			支持的像素格式（仅视频）;
	const int* supported_samplerates;				支持的采样率（仅音频）;
	const enum AVSampleFormat* sample_fmts;		支持的采样格式（仅音频）;
	const uint64_t* channel_layouts;				支持的声道数（仅音频）;
	int priv_data_size;							私有数据的大小;
};



/*************************/AVPacket;/***************************************************************************/
struct AVPacket				//存储一帧压缩编码数据
{
	uint8_t* data;								 压缩编码的数据;
	例如对于H.264来说。1个AVPacket的data通常对应一个NAL;
	注意：在这里只是对应，而不是一模一样。他们之间有微小的差别：使用FFMPEG类库分离出多媒体文件中的H.264码流;
	因此在使用FFMPEG进行视音频处理的时候，常常可以将得到的AVPacket的data数据直接写成文件，从而得到视音频的码流文件;
	int   size;									data的大小;
	int64_t pts;								显示时间戳;
	int64_t dts;								解码时间戳;
	int   stream_index;							标识该AVPacket所属的视频 / 音频流;
};



/*************************/AVFrame;/***************************************************************************/
struct AVFrame				//存储一帧解码后的数据
{
	uint8_t* data[AV_NUM_DATA_POINTERS];		解码后原始数据（对视频来说是YUV，RGB，对音频来说是PCM）;
	int linesize[AV_NUM_DATA_POINTERS];			data中“一行”数据的大小。注意：未必等于图像的宽，一般大于图像的宽;
	int width, height;							视频帧宽和高（1920x1080, 1280x720...）;
	int nb_samples;							音频的一个AVFrame中可能包含多个音频帧，在此标记包含了几个;
	int format;								解码后原始数据类型（YUV420，YUV422，RGB24...）;
	int key_frame;								是否是关键帧;
	enum AVPictureType pict_type;				帧类型（I, B, P...）;
	AVRational sample_aspect_ratio;				宽高比（16: 9，4 : 3...）;
	int64_t pts;								显示时间戳;
	int coded_picture_number;					编码帧序号;
	int display_picture_number;					显示帧序号;
	int8_t* qscale_table;						QP表;
	uint8_t* mbskip_table;						跳过宏块表;
	int16_t(*motion_val[2])[2];					运动矢量表;
	uint32_t* mb_type;							宏块类型表;
	short* dct_coeff;							DCT系数，这个没有提取过;
	int8_t* ref_index[2];							运动估计参考帧列表（貌似H.264这种比较新的标准才会涉及到多参考帧）;
	int interlaced_frame;						是否是隔行扫描;
	uint8_t motion_subsample_log2;				一个宏块中的运动矢量采样个数;
};


(1) data[]
图像数据
对于packed格式的数据（例如RGB24），会存到data[0]里面。
对于planar格式的数据（例如YUV420P），则会分开成data[0]，data[1]，data[2]…（YUV420P中data[0]存Y，data[1]存U，data[2]存V）
音频数据
采样数据PCM, 保存方式同图像数据。 对于对于planar格式的音频数据通道数超过8时，其余通道数据存放于extended_data中。

(2) linesize[]
行字节的跨度，相当于stride。
对于data[i]区域中的一行像素占用的字节数，对于RGB24理论是{w*h*3, 0, …}; 
对于yuv420p，理论是{w, w/2, w/2, 0, …}。但ffmpeg内存会填充对齐，实际行字节数会大于等于理论值。

(3) pict_type
帧数据类型，部分摘取如下
enum AVPictureType {
	AV_PICTURE_TYPE_NONE = 0, ///< Undefined
	AV_PICTURE_TYPE_I,     ///< Intra
	AV_PICTURE_TYPE_P,     ///< Predicted
	AV_PICTURE_TYPE_B,     ///< Bi-dir predicted
	AV_PICTURE_TYPE_S,     ///< S(GMC)-VOP MPEG4
	AV_PICTURE_TYPE_SI,    ///< Switching Intra
	AV_PICTURE_TYPE_SP,    ///< Switching Predicted
	AV_PICTURE_TYPE_BI,    ///< BI type
	...
}


//相关函数
AVFrame* av_frame_alloc(void);					// 分配一个数据帧结构
AVFrame* av_frame_clone(const AVFrame* src);		// 完整的克隆数据帧结构, 包括其内部数据
void av_frame_free(AVFrame** frame);				// 释放数据帧结构及其内部数据
int av_frame_ref(AVFrame* dst, const AVFrame* src);	// 增加引用计数
void av_frame_unref(AVFrame* frame);				// 减少引用计数 
int av_frame_get_buffer(AVFrame* frame, int align);	// 分配缓冲区

//内存分配和引用
avcodec_receive_frame() //开始时调用av_frame_unref(frame)减引用
av_frame_ref()			//需要提前av_frame_alloc为dst分配内存。《只需要一个帧的引用并且需要与原始帧共享数据》
av_frame_clone()		//就是av_frame_alloc()+av_frame_ref()。《需要一个帧的完全独立的副本》
av_frame_copy()		//浅拷贝，复制框架而不复制缓冲区数据《需要一个帧的浅拷贝并且不需要修改数据》
av_frame_unref()		//取消引用帧引用的所有缓冲区并重置帧字段。当帧引用为0时会自动清空数据并释放内存。


//常规解码流程使用
AVFrame* pFrame = av_frame_alloc();  // [1]
while () 
{
	…
	av_receive_frame(ctx, pFrame);
	…  // process
	av_frame_unref(pFrame);         // [2]
}
av_frame_free(pFrame);              // [3]


AVFrame* pFrame = av_frame_alloc()分配一个AVFrame对象，缓冲区data[]未分配。
之后，使用调用av_receive_frame解码，会对pFrame分配data[]缓冲区并保存解码数据；
每一次使用后，必须需要使用av_frame_unref释放缓冲区，否则重复解码会造成内存泄露。
最后，需要使用av_frame_free 释放整个对象。


//内存分配
ffmpeg内部编码器对于图像处理部分为了方便优化处理，通常创建的缓冲区比原始图像大，实际有效数据部分只是缓冲区的一部分。
这一种优化方案直接反应在linesize上，使用8或16或32字节对齐，取决于平台。

对于分辨率为638 * 272的视频解码后yuv420p的缓冲区 linsesize为{ 640,320,320,… }，
可以看到，在三个通道中每一行数据间进行了数据填充，Y区域的行字节数不等于638，U / V区域的行字节数也不等于319。
如果我们需要yuv三个分量无填充的 yuv420p数据，可以手动分配大小为wh3 / 2的内存，再从解码后AVFrame的data[]中拷贝出来;


//方式一：使用malloc原生的内存管理方式
#include <stdlib.h>
uint8_t yuv_buf = malloc(w * h * 3 / 2);

//方式二：ffmpeg内存分配函数
AVFrame* frame_yuv = av_frame_alloc();		// yuv420p对齐处理 变量
av_image_alloc(frame_yuv->data, frame_yuv->linesize,
	video_decoder_ctx->width, video_decoder_ctx->height, AV_PIX_FMT_YUV420P, 1);		// 分配缓冲区，接收转换后yuv420p的1字节对齐数据，分辨率不改变
frame_yuv->width = video_decoder_ctx->width;		// 对于编码，需要AVFrame有对应的参数
frame_yuv->height = video_decoder_ctx->height;
frame_yuv->format = AV_PIX_FMT_YUV420P;

//方式三：原生指针加ffmpeg内存分配函数
uint8_t* yuvbuf;
int linesize[4];
av_image_alloc(&yuvbuf, linesize, video_decoder_ctx->width, video_decoder_ctx->height,
	AV_PIX_FMT_YUV420P, 1);

//方式四：使用av_frame_get_buffer函数（注意检查内存是否连续）
AVFrame* frame_yuv = av_frame_alloc();
frame_yuv->width = video_decoder_ctx->width;
frame_yuv->height = video_decoder_ctx->height;
frame_yuv->format = AV_PIX_FMT_YUV420P;
av_frame_get_buffer(frame_yuv, 1);  // 必须先指定frame的 音频/视频 参数。align = 0,  由系统选择最优对齐方式
注意，av_frame_get_buffer(frame_yuv, 1); 保证y, u, v分量数据区域是1字节对齐的、连续的，但是y, u, v三个数据区不是1字节对齐、也不是连续的。

函数根据用户输入的 图像分辨率 w, h 像素格式 pix_fmt，以及对齐字节数 等参数，按照linesize分配需要的内存。
使用完后，需要av_freep释放内存，如果内存对象是AVFrame则调用av_frame_free即可;
uint8_t* yuvbuf； 经过av_image_alloc分配内存后的释放方法为 av_freep(&(&yuvbuf)[0])。

使用av_image_alloc分配1字节对齐的yuv420p缓冲区内存后，三个分量对应的内存区域是连续的，无填充的。
linesize不再是{ 640,320,320 }，而是{ 638,319,319 }。
并且 data[2] - data[1] = 1 / 4 * w * h, data[1] - data[0] = w * h，
也就是说，尽管YUV三个分别存放于三个指针指向的内存区域，但这三块内存实际是连续的。
从data[0]连续读取w * h * 3 / 2个字节，就是完整的yuv数据。


//获取无填充1字节对齐的yuv420p数据
//方法一：最直接也低效的方式是使用3层for循环拷贝数据，对应原生内存管理的方式。
for (int i = 0; i < frame->height; i++)
	memcpy(yuvbuf + i * frame->width, frame->data[0] + i * frame->linesize[0], frame->width);
for (int i = 0; i < frame->height / 2; i++)
	memcpy(yuvbuf + i * frame->width / 2, frame->data[1] + i * frame->linesize[1], frame->width / 2);
for (int i = 0; i < frame->height / 2; i++)
	memcpy(yuvbuf + i * frame->width / 2, frame->data[2] + i * frame->linesize[2], frame->width / 2);

//方法二：av_image_copy函数
av_image_copy(frame_yuv->data, frame_yuv->linesize,
               const uint8_t **)frame->data, frame->linesize,
               (AVPixelFormat)frame->format, frame->height, frame->width);

av_image_copy(&yuvbuf, linesize,
               (const uint8_t **)frame->data, frame->linesize,
                (AVPixelFormat)frame->format, frame->height, frame->width);

//方法三：sws_scale函数
SwsContext* sws_ctx =				// SwsContext上下文，用于sws_scale调用
sws_getContext(video_decoder_ctx->width, video_decoder_ctx->height, video_decoder_ctx->pix_fmt, // 输入格式
	frame_yuv->width, frame_yuv->height, AV_PIX_FMT_YUV420P,                         // 输出格式
	SWS_BILINEAR, NULL, NULL, NULL);                                                 // 变换处理

同理，针对上一节两种内存分配的对象不同，使用方式如下
sws_scale(sws_ctx,
	frame->data, frame->linesize, 0, frame->height,
	frame_yuv->data, frame_yuv->linesize);

sws_scale(sws_ctx,
	frame->data, frame->linesize, 0, frame->height,
	&yuvbuf, linesize);


//特殊编码器输入要求
某些硬件编码器处于性能考虑，对yuv420p的内存布局对齐方式有要求。
这种情况下，不能使用使用1字节对齐分配数据（例如h264_omx使用opencv转yuv420p的数据直接编码导致有重影）。
使用16 / 32补齐进行尝试。


