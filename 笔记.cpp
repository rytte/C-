


git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890


git config --global - l


git config --global --unset http.proxy
git config --global --unset https.proxy






{
    "body": {
        "messageBody": "{\"background_color\":\"black\",\"devid\":\"0.22.1.8.1\",\"limit_style\":\"limit_time\",\"limit_time\":\"2\",\"msg_priority\":\"s\",\"pass\":\"central\",\"sceneLayout\":\"d2a9e819-fc73-455b-87cc-9610f5169e8e\",\"stationsvr_id\":\"PC-Bk_Test\",\"stationsvr_pass\":\"admin\",\"stationsvr_user\":\"root\",\"text\":\"各位乘客请注意，由于深圳突降暴雨，地面湿滑，请各位乘客有序排队进站乘车，切勿拥挤，谢谢配合！\",\"text_color\":\"white\",\"text_direction\":\"to_left\",\"text_fontSize\":20,\"text_scrollInterval\":90,\"user\":\"central\"}\n",
        "messageCommand" : "PLAY_PROMPT_TEXT"
    },
        "header" : {
            "end": true,
            "messageNo" : "39c43a88-ec11-4e02-9400-e2fd7969bb35",
            "messageReceiver" : "bk_player",
            "messageSender" : "Bk_Test_Tool",
            "messageType" : "P2P_command_message",
            "timeout" : 1,
            "zzflag" : "end"
    }
}


{
    "messageNo": "1684661317418221568",
    "messageBody" : {
        "text_id": "1684661302385836032",
        "text_fontSize" : 0,
        "background_color" : "",
        "text_direction" : "",
        "text_scrollInterval" : 0,
        "msg_priority" : "9",
        "text" : "不能重试下发同一条文字信息 test",
        "text_color" : "",
        "limit_style" : "timer",
        "textEn" : "test",
        "limit_time" : "2024-04-15 15:05:16,2099-12-31 23:59:59"
    },
    "messageCommand": "PLAY_PROMPT_TEXT"
}




AVRational time_base = m_pFormatCtx->streams[m_videoIndex]->time_base;
int64_t duration = m_pFormatCtx->streams[m_videoIndex]->duration;
double microseconds = av_rescale_q(duration, time_base, AVRational({ 1,AV_TIME_BASE }));
printf("Video duration: %.3f seconds\n", microseconds / 1000 / 1000);








//        cv::Mat backImgMat = cv::Mat(m_height, m_width, CV_8UC4, (void*)m_backImg.constBits(), (size_t)m_backImg.bytesPerLine());
//        cv::Mat textImgMat = cv::Mat(m_height, m_width, CV_8UC4, overlayData);
//        cv::Mat dstImgMat = cv::Mat(m_height, m_width, CV_8UC4);

//        // 分离RGBA通道
//        std::vector<cv::Mat> backChannels(4), textChannels(4), destChannels(4);
//        cv::split(backImgMat, backChannels);
//        cv::split(textImgMat, textChannels);

//        // 计算合成后的RGBA通道
//        for (int i = 0; i < 3; ++i)
//        {
//            //destChannels[i] = textChannels[i].mul(textChannels[3]) / 256 + backChannels[i].mul(256 - textChannels[3]) / 256;
//            destChannels[i] = ((textChannels[i] - backChannels[i]).mul(textChannels[3])) / 256 + backChannels[i];
//        }
//        destChannels[3] = textChannels[3] + backChannels[3].mul(256 - textChannels[3]) / 256;

//        // 合并RGB通道和新的alpha通道
//        cv::merge(destChannels, dstImgMat);

//        // 将合成结果复制回 overlayData
//        memcpy(overlayData, dstImgMat.data, dstImgMat.total() * dstImgMat.elemSize());




//        cv::Mat backImgMat = cv::Mat(m_height, m_width, CV_8UC4, static_cast<void*>(m_backImg.bits()), static_cast<size_t>(m_backImg.bytesPerLine()));
//        cv::Mat textImgMat = cv::Mat(m_height, m_width, CV_8UC4, overlayData);
//        cv::Mat dstImgMat = cv::Mat(m_height, m_width, CV_8UC4);
//        cv::Mat alphaMat = cv::Mat(m_height, m_width, CV_8UC4);

//        // 分离RGBA通道
//        std::vector<cv::Mat> textChannels(4);
//        cv::split(textImgMat, textChannels);

//        // 合成新的alphaMat
//        std::array<cv::Mat, 4> alphaChannels = {textChannels[3], textChannels[3], textChannels[3], textChannels[3]};
//        cv::merge(alphaChannels, alphaMat);

//        // 计算合成后的RGBA通道
//        dstImgMat = ((textImgMat - backImgMat).mul(alphaMat)) / 256 + backImgMat;

//        // 将合成结果复制回 overlayData
//        memcpy(overlayData, dstImgMat.data, dstImgMat.total() * dstImgMat.elemSize());







