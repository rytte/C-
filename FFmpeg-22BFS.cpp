/********************/BFS/************************************************************/

BFS（bitstream filter，比特流过滤器），用于对 已压缩的编码包（如 H.264）做结构级处理，但不进行解码。

#include "libavcodec/bsf.h"

//作用
1、修改编码后数据（AVPacket）的内容或封装格式；
2、不解码原始帧，不重新编码；

例如：
1、从 H.264 annexb（裸流）转为 MP4（AVCC 格式）；
2、从 HEVC 去除冗余头；
3、拆分 / 合并 SEI / SPS / PPS；
4、去除 B 帧；
5、修改数据头信息等。


//常用过滤器
h264_mp4toannexb		//把 AVCC 格式 H.264（用于 MP4）转成 Annex B（用于 TS / flv / raw）
hevc_mp4toannexb		//同上，但用于 HEVC
null					//什么都不做，调试用
vp9_superframe_split	//拆分 VP9 Super Frame
extract_extradata		//提取 codec extra data，便于封装


//av_bsf_send_packet / av_bsf_receive_packet函数
int av_bsf_send_packet(AVBSFContext * ctx, const AVPacket * pkt);//将一个原始编码包（如 H.264 packet）送入过滤器。pkt 是只读的，BSF 内部会拷贝内容。
int av_bsf_receive_packet(AVBSFContext * ctx, AVPacket * pkt);	//从过滤器中取出“处理后”的新 packet；

返回 AVERROR(EAGAIN) 表示还没准备好，需要你继续 send_packet；
返回 AVERROR_EOF 表示所有数据已处理完。


//命令行转换
"ffmpeg -i input.h264 -c:v copy output.mp4"								//Annex-B → AVCC（用于 MP4）
"ffmpeg -i input.mp4 -c:v copy -bsf:v h264_mp4toannexb output.ts"		//AVCC → Annex-B（用于 TS）

//代码转换
Annex - B → AVCC：当你将 AVCodecParameters 写入 MP4 容器（如使用 avformat_write_header 并指定格式为 mp4），FFmpeg 会自动将 Annex B 转换成 AVCC。
AVCC → Annex - B：如下实例



/********************/实例/************************************************************/
const AVBitStreamFilter* filter = av_bsf_get_by_name("h264_mp4toannexb");       //获取h264_mp4toannexb过滤器

AVBSFContext* bsf_ctx = nullptr;
av_bsf_alloc(filter, &bsf_ctx);     //过滤器上下文创建

avcodec_parameters_copy(bsf_ctx->par_in, input_stream->codecpar);   // 将视频流的解码参数（codecpar）复制到比特流过滤器的输入参数中
bsf_ctx->time_base_in = input_stream->time_base;
av_bsf_init(bsf_ctx);           //初始化比特流过滤器上下文

// 处理每一个 AVPacket
while (获取 packet 到 pkt) {
    av_bsf_send_packet(bsf_ctx, pkt);

    while (av_bsf_receive_packet(bsf_ctx, &filtered_pkt) == 0) {
        // 使用处理后的 filtered_pkt 写入输出或其它用途
        ...
        av_packet_unref(&filtered_pkt);
    }
}

av_bsf_flush(bsf_ctx);
av_bsf_free(&bsf_ctx);




