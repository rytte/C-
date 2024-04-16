#include "ffmpeg.h"
/*************************/初始化;/***************************************************************************/


void avdevice_register_all(void);

// 初始化libavDevice并注册所有输入和输出设备
// 对设备进行注册。如果我们要捕捉屏幕进行录制屏幕，捕捉摄像头进行录制视频，捕捉麦克风录制麦克风声音时
// 就需要使用到该函数进行注册。例如（windows下的dshow，Linux下的V4L2等）



int avformat_network_init(void);			//初始化网络库以及网络加密协议相关的库，推流或者拉流时会使用到

// 执行网络库的全局初始化。这是可选的，不再推荐使用。
// 此函数仅用于解决旧版GNUTLS或OpenSSL库的线程安全问题。
// 如果libavFormat链接到这些库的较新版本，或者如果您不使用它们，则不需要调用此函数。
// 否则，您需要在启动使用该函数的任何其他线程之前调用该函数。
// 一旦删除对较旧的GNUTLS和OpenSSL库的支持，此函数将被弃用，并且此函数将不再有任何用途。




/*************************/日志;/***************************************************************************/

void av_log(void* avcl, int level, const char* fmt, ...) av_printf_format(3, 4);			//打印消息

// 如果级别小于或等于当前的av_log_Level，则向日志发送指定的消息。
// 默认情况下，所有日志记录消息都发送到stderr。可以通过设置不同的日志回调函数来更改此行为。
// 【参阅】av_log_set_allback。
// 【avcl】指向任意结构的指针，其第一个字段是指向AVClass结构的指针，如果是常规日志，则为NULL。
// 【level】使用@ref LAVU_LOG_CONSTANTS“记录常量”表示的消息的重要性级别。
// 【fmt】指定如何将后续参数转换为输出的格式字符串(与printf兼容)。



/*************************/解码;/***************************************************************************/
AVFormatContext* avformat_alloc_context(void);				//创建格式上下文

// 分配AVFormatContext。
// AvFormat_Free_CONTEXT()可用于释放上下文和所有内容。
// 由其中的框架分配。



int avformat_open_input(AVFormatContext** ps, const char* url,          //打开输入文件，并关联格式上下文
        const AVInputFormat* fmt, AVDictionary** options);

// 打开输入流并读取头。编解码器未打开。
// 必须使用avformat_close_input()关闭流。
// 【ps】指向用户提供的AVFormatContext的指针(由avFormat_Alloc_Context分配)。
// 可以是指向空的指针，在这种情况下，此函数将分配AVFormatContext并将其写入p.
// 请注意，用户提供的AVFormatContext将在失败时被释放。
// 【url】要打开的流的url URL。
// 【fmt】如果非空，则此参数强制使用特定的输入格式。否则将自动检测该格式。
// 【options】用AVFormatContext和demuxer私有选项填充的字典。
// 返回时，此参数将被销毁，并替换为包含未找到的选项的字典。可以为空。
// 【返回值】如果成功则返回0，如果失败则返回负值。
// 【注意】如果您想使用自定义IO，请预先分配format上下文并设置其PB字段。



int avformat_find_stream_info(AVFormatContext* ic, AVDictionary** options);             //上下文获取流信息

// 读取媒体文件的包以获取流信息。
// 这对于没有标头的文件格式很有用，例如MPEG。
// 此函数还会计算在MPEG - 2重复帧模式下的实际帧速率。此函数不会更改逻辑文件位置；检查的数据包可能会被缓冲以供以后处理。
// 【ic】媒体文件句柄。
// 【options】如果不为空，则为指向字典的ic.nb_stream长指针数组，其中第i个成员包含与第i个流对应的编解码器选项。返回时，每个字典将填充未找到的选项。
// 【返回值】 >= 0如果正常，则错误时返回AVERROR_xxx。
// 【注意】此函数不能保证打开所有编解码器，因此选项在返回时为非空是非常正常的行为。
// 【用处】让用户以某种方式决定需要什么信息，这样我们就不会浪费时间获取用户不需要的东西。



void av_dump_format(AVFormatContext* ic, int index, const char* url, int is_output);                    //音视频文件的协议封装解析

// 打印输入或输出格式的详细信息，如时长、码率、流、容器、节目、元数据、边数据、编解码器和时基。
// 【ic】要分析的上下文
// 【index】要转储其信息的流的索引，-1为自动选择
// 【url】要打印的URL，如源文件或目标文件
// 【is_output】选择指定的上下文是输入上下文(0)还是输出上下文(1)，输入文件的话为0



int av_find_best_stream(AVFormatContext* ic,
        enum AVMediaType type,
        int wanted_stream_nb,
        int related_stream,
        const struct AVCodec** decoder_ret,
        int flags);

// 在文件中找到“最佳”流。
// 根据各种试探法将最佳流确定为最有可能是用户期望的流。
// 如果DECODER参数非空，则av_find_Best_stream将查找流的编解码器的默认解码器；找不到解码器的流将被忽略。
// 【ic】媒体文件句柄
// 【type】流类型：视频、音频、字幕等。
// 【wanted_stream_nb】用户请求的流编号，或 - 1用于自动选择
// 【related_stream】尝试找到相关的流(例如，在同一程序中)添加到此程序，如果没有，则为 - 1
// 【decoder_ret】如果不为NULL，则返回所选流的解码器
// 【flags】标志；当前未定义任何标志，设为0
// 【返回值】如果成功，则返回非负流编号；如果找不到请求类型的流，则返回AVERROR_STREAM_NOT_FOUND；
// 如果找到流，但没有解码器，则返回AVERROR_DECODER_NOT_FOUND
// 【注意】如果av_find_best_stream成功返回，并且decder_ret不为NULL，则可以保证将 * decder_ret设置为有效的AVCodec。



AVCodecContext* avcodec_alloc_context3(const AVCodec* codec);

//  分配一个AVCodecContext并将其字段设置为默认值。生成的结构应该用avcodec_Free_Context()释放。
// 【codec】如果不为NULL，则为给定的编解码器分配私有数据并初始化默认值。然后使用不同的编解码器调用avcodec_open2()是非法的。
// 如果为NULL，则特定于编解码器的默认设置将不会被初始化，这可能会导致不佳的默认设置(这主要对编码器很重要，例如libx264)。
// 【返回值】使用默认值填充的AVCodecContext，如果失败则为NULL。



int avcodec_parameters_to_context(AVCodecContext* codec, const struct AVCodecParameters* par);

// 根据提供的编解码器参数的值填充编解码器上下文。
// 将释放编解码器中具有PAR中对应字段的任何已分配字段，并将其替换为PAR中相应字段的副本。
// 不会触及编解码器中没有PAR中对应字段的字段。
// 【返回值】 >= 0成功时，失败时为负AVERROR代码。



const AVCodec* avcodec_find_decoder(enum AVCodecID id);

// 查找具有匹配编解码器ID的注册解码器。
// 【id】请求的解码器的ID
// 【返回值】找到则返回一个解码器，没找到则返回NULL。



int avcodec_open2(AVCodecContext* avctx, const AVCodec* codec, AVDictionary** options);

// 初始化AVCodecContext以使用给定的AVCodec。
// 在使用此函数之前，必须为上下文分配avcodec_alloc_context3()。
// 
// 函数avcodec_find_decder_by_name()、avcodec_find_encode_by_name()、avcodec_find_decoder()
// 和avcodec_find_encode()为检索编解码器提供了一种简单的方法。
// 
// 根据编解码器的不同，您可能还需要在编解码器上下文中设置用于解码的选项
// (例如，在比特流中信息不可用的情况下，例如宽度、高度或像素或音频采样格式，例如在对原始音频或视频进行解码时)。
// 
// 编解码器上下文中的选项可以通过在Options AVDicary中设置它们，
// 或者通过在上下文本身中直接设置值，或者通过在调用此函数之前使用av_opt_set()API来设置。
// 
// 例如:
//  * @code
//  * av_dict_set(&opts, "b", "2.5M", 0);
//  * codec = avcodec_find_decoder(AV_CODEC_ID_H264);
//  * if (!codec)
//  *     exit(1);
//  *
//  * context = avcodec_alloc_context3(codec);
//  *
//  * if (avcodec_open2(context, codec, opts) < 0)
//  *     exit(1);
//  * @endcode
//  *
// 在AVCodec参数可用的情况下(例如，当使用libavFormat对流进行解复用并访问解复用器中包含的AVStream时)，
// 可以使用avcodec_参数_to_Context()将编解码器参数复制到编解码器上下文中，如下例所示：
//  *
//  * @code
//  * AVStream *stream = ...;
//  * context = avcodec_alloc_context3(codec);
//  * if (avcodec_parameters_to_context(context, stream->codecpar) < 0)
//  *     exit(1);
//  * if (avcodec_open2(context, codec, NULL) < 0)
//  *     exit(1);
//  * @endcode
//  *
// 【注意】始终在使用解码例程(如@ref avcodec_receive_frame())之前调用此函数。
// 【avctx】要初始化的上下文。
// 【codec】要为其打开此上下文的编解码器。
// 如果之前已将非空编解码器传递给avcodec_alloc_context3()或用于此上下文，则此参数必须为NULL或等于先前传递的编解码器。
// 【options】用AVCodecContext和编解码器私有选项填充的词典可以为空，这些选项设置在avctx中已经设置的选项之上。
// 返回时，此对象将填充在avctx编解码器上下文中找不到的选项。
// 【返回值】成功时为零，错误时为负值
// 【参阅】avcodec_alloc_context3(), avcodec_find_decoder(), avcodec_find_encoder(),
// av_dict_set(), av_opt_set(), av_opt_find(), avcodec_parameters_to_context()



void avformat_close_input(AVFormatContext** s);

// 关闭打开的输入AVFormatContext。释放它及其所有内容，并将 *s 设置为NULL。



AVPacket* av_packet_alloc(void);							//分配一个AVPacket内存

// 分配一个AVPacket并将其字段设置为默认值。结果 struct 必须使用av_Packet_Free()来释放。
// 【返回值】使用缺省值填充的AVPacket，如果失败则为NULL
// 【注意】这只分配AVPacket本身，而不是数据缓冲区。必须通过其他方式进行分配，如av_new_Packet。
// 【参阅】av_new_Packet



AVFrame* av_frame_alloc(void);

// 分配一个AVFrame并将其字段设置为默认值。结果 struct 必须使用av_Frame_Free()释放。
// 【返回值】使用默认值填充的AVFrame，如果失败则为NULL
// 【注意】这只会分配AVFrame本身，而不会分配数据缓冲区。
// 这些缓冲区必须通过其他方式分配，例如，使用av_Frame_Get_Buffer()或手动分配。



int av_image_alloc(uint8_t * pointers[4], int linesizes[4], int w, int h, enum AVPixelFormat pix_fmt, int align);

// 分配一个大小为w和h、像素格式为pix_fmt的图像，并相应地填充指针和行大小。
// 必须使用av_freep(&pointers[0])释放已分配的图像缓冲区。
// 【pointers】要用每个图像平面的指针填充的数组
// 【linesizes】用每个平面的线条大小填充的数组
// 【w】以像素为单位的图像宽度
// 【h】以像素为单位的图像高度
// 【pix_fmt】图像的AVPixelFormat
// 【align】用于缓冲区大小对齐的值
// 【返回值】图像缓冲区所需的大小(以字节为单位)，出现故障时为负错误代码



int av_frame_copy(AVFrame * dst, const AVFrame * src);

// 将帧数据从src复制到dst。
// 此函数不分配任何内容，dst必须已经初始化并使用与src相同的参数进行分配。
// 此函数仅复制帧数据(即数据 / 扩展数据数组的内容)，而不复制任何其他属性。
// 【返回值】 >= 0表示成功，出错表示为负值



int av_frame_copy_props(AVFrame * dst, const AVFrame * src);

// 仅将“METADATA”字段从src复制到dst。
// 对于此函数而言，元数据是那些不影响缓冲区中数据布局的字段。
// 例如PTS、采样率(用于音频)或采样纵横比(用于视频)，但不包括宽度 / 高度或频道布局。
// Side数据也会被复制;



AVFrame* av_frame_clone(const AVFrame * src);

// 创建引用与src相同的数据的新框架。
// 这是av_Frame_alloc() + av_Frame_ref()的快捷方式。
// 【返回值】成功时新创建的AVFrame，错误时为空。



int av_frame_ref(AVFrame * dst, const AVFrame * src);

// 设置对源框架所描述的数据的新引用。
// 将帧属性从src复制到dst，并从src为每个AVBufferRef创建一个新的引用。
// 如果不对src进行引用计数，则分配新的缓冲区并复制数据。
// 【注意】在调用此函数之前，必须使用av_frame_unref(dst)取消引用dst，或者使用av_frame_alloc()重新分配dst，否则将发生未定义的行为。
// 【返回值】成功时为0，错误时为负值



void av_frame_unref(AVFrame * frame);

// 取消引用帧引用的所有缓冲区并重置帧字段。



int av_read_frame(AVFormatContext * s, AVPacket * pkt);

// 应在一个线程中同时解码音视频，若在两个线程中分别解码音视频则需要另外申请一个AVFormatContext



int avcodec_receive_frame(AVCodecContext* avctx, AVFrame* frame);

// 从解码器或编码器返回解码的输出数据(当使用@REF AV_CODEC_FLAG_RECON_FRAME标志时)。
// 【avctx】编解码器上下文
// 【frame】这将被设置为由编解码器分配的参考计数的视频或音频帧(取决于解码器类型)。
// 请注意，该函数将始终在执行任何其他操作之前调用av_Frame_unref(Frame)。
// 【返回值】0                                       成功，则返回一个帧               
// 【返回值】AVERROR(EAGAIN)         在当前状态下不接受输入-用户必须使用avcodec_Receive_Packet()读取输出(读取所有输出后，应重新发送数据包，调用不会因EAGAIN而失败)。
// 【返回值】AVERROR_EOF                编码器已刷新，无法向其发送任何新帧
// 【返回值】AVERROR(EINVAL)          编解码器未打开，它是解码器，或需要刷新
// 【返回值】AVERROR(ENOMEM)      无法将数据包添加到内部队列，或类似情况
// 【返回值】其它负数错误代码             合法编码错误



/*************************/视频转换函数;/***************************************************************************/
void* av_malloc(size_t size);

// 分配一个内存块，其对齐方式适合所有内存访问(包括向量，如果CPU上可用)。
// 【size】要分配的内存块的大小(字节)
// 【返回值】指向已分配块的指针，如果无法分配该块，则返回`NULL`



int av_image_get_buffer_size(enum AVPixelFormat pix_fmt, int width, int height, int align);

// 返回存储具有给定参数的图像所需的数据量的大小(以字节为单位)。
// 【pix_fmt】图像的像素格式。
// 【width】以像素为单位的图像宽度。
// 【height】以像素为单位的图像高度。
// 【align】假定的线大小对齐
// 【返回值】缓冲区大小(以字节为单位)，出现故障时为负错误代码



int av_image_fill_arrays(uint8_t * dst_data[4], int dst_linesize[4],
        const uint8_t * src,
        enum AVPixelFormat pix_fmt, int width, int height, int align);

// 根据指定的图像参数和提供的数组设置数据指针和linesizes。
// 通过使用指向图像数据缓冲区的src地址来填充给定图像的字段。
// 根据指定的像素格式，将设置一个或多个图像数据指针和行大小。
// 如果指定平面格式，将设置多个指向不同图片平面的指针，并且不同平面的线条大小将存储在LINES_SIZES数组中。
// 使用src == NULL调用以获取src缓冲区所需的大小。
// 要在一次调用中分配缓冲区并填充DST_DATA和DST_LINESIZE，请使用av_Image_alloc()。
// 【dst_data[4]】要填写的数据指针。
// 【dst_linesize[4]】DST_DATA中要填充的图像的linesize。
// 【src】将包含或包含实际图像数据的缓冲区，可以为NULL。
// 【pix_fmt】图像的像素格式。
// 【width】以像素为单位的图像宽度。
// 【height】以像素为单位的图像高度。
// 【align】在src中用于行大小对齐的值
// 【返回值】src所需的大小(以字节为单位)，失败时为负错误代码



struct SwsContext* sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat,
        int dstW, int dstH, enum AVPixelFormat dstFormat,
        int flags, SwsFilter * srcFilter,
        SwsFilter * dstFilter, const double* param);

// 分配并返回SwsContext。您需要它来使用sws_scale()执行缩放 / 转换操作。
// 【srcW】源图像的宽度。
// 【srcH】源图像的高度。
// 【srcFormat】源图像格式。
// 【dstW】目标图像的宽度。
// 【dstH】目标图像的高度。
// 【dstFormat】设置目标图像格式。
// 【flags】标志指定用于重新缩放的算法和选项
// 【srcFilter】过滤器
// 【dstFilter】过滤器
// 【param】用于调整SWS_BICUBIC参数[0]和[1]使用的定标器的额外参数调整基函数的形状，
// 参数param[0]调整SWS_GAUSS参数[0]的f(1)和param[1]f`(1)调整指数，从而调整SWS_LANCZOS参数[0]的截止频率调整窗函数的宽度
// 【返回值】指向分配的上下文SwsContext的指针，如果出现错误，则为NULL
// 【注意】此函数将在编写更合理的替代方案后删除



int sws_scale(struct SwsContext* c, const uint8_t* const srcSlice[],
        const int srcStride[], int srcSliceY, int srcSliceH,
        uint8_t* const dst[], const int dstStride[]);

// 缩放srcSlice中的图像切片，并将生成的缩放切片放入DST中的图像中。切片是图像中的一系列连续行。
// 切片必须按顺序提供，可以是从上到下或从下到上的顺序。如果以非连续顺序提供切片，则函数的行为是未定义的。
// 
// 【c】之前使用sws_getContext()创建的伸缩上下文。
// 【srcSlice[]】包含指向源片平面的指针的数组。
// 【srcStride[]】包含源图像每个平面的步幅的数组。
// 【srcSliceY】要处理的切片在源图像中的位置，即切片第一行的图像中的编号(从零开始计数。
// 【srcSliceH】源片的高度，即片中的行数
// 【dst[]】包含指向目标图像平面的指针的数组
// 【dstStride[]】包含目标图像每个平面的步幅的数组
// 【返回值】输出片的高度



/*************************/音频转换函数/***************************************************************************/
int av_samples_get_buffer_size(int* linesize, int nb_channels, int nb_samples, enum AVSampleFormat sample_fmt, int align);

// 获取给定音频参数所需的缓冲区大小。
// 【linesize】计算的linesize，可以为NULL。
// 【nb_channels】通道的数量。
// 【nb_samples】单个通道中的采样数。
// 【sample_fmt】采样格式。
// 【align】缓冲区大小对齐(0 = 默认，1 = 无对齐)。
// 【返回值】所需的缓冲区大小，或故障时的负错误代码



void av_channel_layout_default(AVChannelLayout* ch_layout, int nb_channels);

// 修改给定的通道布局的通道数
// 【ch_layout】要初始化的布局结构
// 【nb_channels】通道数



int swr_alloc_set_opts2(struct SwrContext** ps,
        const AVChannelLayout* out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
        const AVChannelLayout* in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
        int log_offset, void* log_ctx);

// 如果需要，分配SwrContext并设置 / 重置公共参数。
// 该函数不需要为 * ps分配SWR_ALLOC()。
// 另一方面，swr_alloc()可以使用swr_alloc_set_opts2()来设置所分配的上下文上的参数。
// 【ps】指向现有SWR上下文的指针(如果可用)，或指向空的指针(如果不可用)。如果成功， * ps将设置为已分配的上下文。
// 【out_ch_layout】输出通道布局(例如，AV_Channel_Layout_*)。
// 【out_sample_fmt】输出样本格式(AV_SAMPLE_FMT_*)。
// 【out_sample_rate】输出采样率(频率单位为赫兹)。
// 【in_ch_layout】输入频道布局(例如，AV_Channel_Layout_*)。
// 【in_sample_fmt】输入样本格式(AV_SAMPLE_FMT_*)。
// 【in_sample_rate】输入采样率(频率单位为赫兹)。
// 【log_offset】记录级别偏移量。
// 【log_ctx】父日志记录上下文可以为空
// 【返回值】成功时为0，错误时为负AVERROR代码。出错时，释放SWR上下文并将 * ps设置为空。



int swr_init(struct SwrContext* s);

// 在设置用户参数后初始化上下文。
// 【注意】必须使用AVOption API配置上下文
// 【s】要初始化的SWR上下文
// 【返回值】故障情况下的AVERROR错误代码。



int swr_convert(struct SwrContext* s, uint8_t** out, int out_count, const uint8_t** in, int in_count);

// 转换音频。
// in和in_count可以设置为0，以在结束时清除最后几个样本。
// 如果提供的输入多于输出空间，则输入将被缓冲。
// 您可以使用swr_get_out_samples()来检索给定数量的输入样本所需的输出样本数量的上限，从而避免这种缓冲。
// 只要有可能，转换将直接运行而不进行复制。
// 【s】已分配SWR上下文，已设置参数。
// 【out】输出缓冲区，在压缩音频的情况下只需要设置第一个缓冲区。
// 【out_count】每通道样本数中可用于输出的空间量。
// 【in】输入缓冲区，在压缩音频的情况下只需要设置第一个缓冲区。
// 【in_count】一个通道中提供的输入样本数
// 【返回值】每通道输出的样本数，错误时为负值





