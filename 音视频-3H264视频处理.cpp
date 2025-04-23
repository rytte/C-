/********************/H264视频处理/************************************************************/

//获取H264文件
使用FFmpeg解封装本地视频如aki.mp4，读取AVPacket，将AVPacket::data写入aki.h264文件：fwrite(packet->data, 1, packet->size, fd);

//无法播放
H264文件无法播放，因为没有PTS等信息

//封装为MP4文件
"ffmpeg -i aki.h264 - c:v copy aki.mp4"	转换后可以播放
FFmpeg会从 NAL 单元（起始码如 0x000001）中找出 I 帧、P 帧、SPS / PPS 等。自动分析帧率（如果没有，则可能出错或需你指定帧率）。
MP4 封装格式需要时间戳、索引表、帧信息等元数据。FFmpeg 自动为这些帧生成封装信息，使播放器能正常解码和跳转。

//手动封装MP4文件（解析H264）





AVStream::r_frame_rate（实际帧率）
AVStream::avg_frame_rate（平均帧率）

//压缩编码模式
模式	    参数	                    文件大小	    画质	        控制目的
CRF     "-crf 18~28"	        不定	        稳定	🔥      质量优先
CBR     "-b:v 1000k"	        固定	        可变	        码率限制
ABR     "-b:v 1000k + 宽容度"	大致固定	    尽量稳定	    混合模式
QP      "-qp 20"	            不定	        不均衡	    每帧定量

//编码时pts添加场景
使用场景	                            是否建议加 pts	    原因
仅编码为 H.264 裸流、追求体积最小	    ❌ 不加	            简化结构，减小码率
后续封装 MP4 / 含 B 帧 / 同步需求	    ✅ 一定加	        避免帧序错乱，正确封装
帧类型固定（无 B 帧）	                可选	                有无影响不大
想保留编码稳定性与预测一致性	        ✅ 加	            提高稳定性，逻辑清晰

//DTS使用场景
使用场景	                    DTS 是否重要
实时推流（无 B 帧）	        ❌ 不重要
解码裸流为 YUV	            ❌ 不重要（用帧序或恒定帧率估算即可）
转码含 B 帧的 h264 到 mp4	    ✅ 重要
视频剪辑、多轨合成	        ✅ 重要
简单播放 h264 裸流	        ❌ 通常不重要（可估算）


//封装格式区别
特性               FLV / AVI（偏老旧）                   MP4 / MOV / MKV（现代主流）
设计年代           上世纪 90~2000 初                     2000 年后
支持的编解码器     少、依赖特定格式（如 FLV / H.263）      支持各种音视频编码（H264、AAC、Opus 等）
流媒体特性         FLV 支持流式播放；AVI 差               MP4 / MOV 支持快进，流播放需优化（hint track）MKV 天生支持流媒体
时间戳精度         较低（尤其是 AVI）                     高精度（纳秒级）
索引和帧控制       AVI / FLV 索引简单或无索引             MP4 / MOV 有 moov 原子结构做精确控制；MKV 结构灵活
容错性            高（尤其是 AVI、FLV）                  低，时间轴错就会卡顿（特别是 MP4）
字幕、章节支持     差                                    MKV 原生支持字幕、章节等
文件大小支持       AVI 有 2GB 限制                       没有限制（MP4 / MKV 可处理超大文件）
播放器兼容性       AVI / FLV 被 Flash 等支持；旧时代主力   MP4 是主流（浏览器 / 手机通用）；MKV 是现代 PC 通用




//使用FFmpeg将H264封装为MP4
打开输入流(H.264裸流)
↓
创建输出 AVFormatContext（MP4）
↓
添加视频流（AVStream），设置编码参数
↓
打开输出文件（avio_open）
↓
写文件头（avformat_write_header）
↓
循环读取每个H264帧 → 包装成 AVPacket → 添加时间戳
↓
调用 av_write_frame() 写入
↓
写文件尾（av_write_trailer）
↓
释放资源



extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/timestamp.h>
}

int main() {
    const char* input_filename = "input.h264";
    const char* output_filename = "output.mp4";

    av_register_all();  // 可选（旧版需要）

    AVFormatContext* ifmt_ctx = nullptr;
    AVFormatContext* ofmt_ctx = nullptr;
    AVOutputFormat* ofmt = nullptr;
    AVStream* out_stream = nullptr;

    FILE* infile = fopen(input_filename, "rb");
    if (!infile) {
        printf("Cannot open input file\n");
        return -1;
    }

    // 创建输出上下文（mp4封装）
    avformat_alloc_output_context2(&ofmt_ctx, nullptr, nullptr, output_filename);
    if (!ofmt_ctx) {
        printf("Could not create output context\n");
        return -1;
    }
    ofmt = ofmt_ctx->oformat;

    // 添加视频流
    out_stream = avformat_new_stream(ofmt_ctx, nullptr);
    if (!out_stream) {
        printf("Failed allocating output stream\n");
        return -1;
    }

    // 设置 H.264 编码参数
    out_stream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    out_stream->codecpar->codec_id = AV_CODEC_ID_H264;
    out_stream->codecpar->width = 1280;
    out_stream->codecpar->height = 720;
    out_stream->codecpar->format = AV_PIX_FMT_YUV420P;
    out_stream->time_base = (AVRational){ 1, 25 };  // 假设25fps

    // 打开输出文件
    if (!(ofmt->flags & AVFMT_NOFILE)) {
        if (avio_open(&ofmt_ctx->pb, output_filename, AVIO_FLAG_WRITE) < 0) {
            printf("Could not open output file\n");
            return -1;
        }
    }

    // 写 MP4 文件头
    if (avformat_write_header(ofmt_ctx, nullptr) < 0) {
        printf("Error occurred when writing header\n");
        return -1;
    }

    // 构造 packet 数据（这里简单从裸流读数据）
    uint8_t buffer[4096];
    int64_t pts = 0;
    while (!feof(infile)) {
        int size = fread(buffer, 1, sizeof(buffer), infile);
        if (size <= 0) break;

        AVPacket pkt;
        av_init_packet(&pkt);
        pkt.data = buffer;
        pkt.size = size;

        pkt.stream_index = out_stream->index;
        pkt.pts = pts;
        pkt.dts = pts;
        pkt.duration = 1;
        pkt.pos = -1;

        pkt.pts = av_rescale_q(pkt.pts, (AVRational) { 1, 25 }, out_stream->time_base);
        pkt.dts = pkt.pts;
        pkt.duration = av_rescale_q(1, (AVRational) { 1, 25 }, out_stream->time_base);

        if (av_write_frame(ofmt_ctx, &pkt) < 0) {
            printf("Error while writing packet\n");
            break;
        }

        pts++;
    }

    // 写文件尾
    av_write_trailer(ofmt_ctx);

    // 释放资源
    fclose(infile);
    avio_closep(&ofmt_ctx->pb);
    avformat_free_context(ofmt_ctx);

    return 0;
}
