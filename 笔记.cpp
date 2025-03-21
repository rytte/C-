


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








{
    "_elements": [
    {
        "_type": "element",
        "_name" : "note",
        "_elements" : [
        {
            "_type": "element",
                "_name" : "title"
        },
        {
            "_type": "element",
            "_name" : "todo"
        },
        {
            "_type": "element",
            "_name" : "todo"
        }
    ]
    }
    ]
}


{
    "_elements": [
        {
            "_type": "element",
            "_name": "note",
            "_elements": [
                {
                    "_type": "element",
                    "_name": "title",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "Happy"
                        }
                    ]
                },
                {
                    "_type": "element",
                    "_name": "todo",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "Work"
                        }
                    ]
                },
                {
                    "_type": "element",
                    "_name": "todo",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "Play"
                        }
                    ]
                }
            ]
        }
    ]
}


{
    "note": {
        "title": "Happy",
        "todo" : ["Work", "Play"]
    }
}




{
    "backgroundImage": "MTTlj7fnur_nq5nljoXliIflm74=.png",
    "width": 3840,
    "height": 2160,
    "terminalType": 2,
    "scaling": 4,
    "LayoutItem": [
        {
            "id": "39f61c8d-6b7d-4e32-abca-b8a002b07e94",
            "opacity": 1,
            "width": 400,
            "height": 140,
            "positionX": 56,
            "positionY": 440,
            "itemType": "STATIC_TEXT",
            "LayoutItemUnit": {
                "id": "28fa74ac-bff9-493d-a41b-99f140e277ff",
                "content": "开往：",
                "componentType": "Text",
                "fontSize": 112,
                "fontFamily": "SourceHanSansSC",
                "textColor": "#000000",
                "bold": false,
                "italic": false,
                "align": "center",
                "language": 0,
                "positionX": 0,
                "positionY": 0,
                "width": 400,
                "height": 140
            }
        },
        {
            "id": "f892e4b6-d553-4c90-86d8-ffa1b6ffeabc",
            "opacity": 1,
            "width": 400,
            "height": 140,
            "positionX": 56,
            "positionY": 1356,
            "itemType": "STATIC_TEXT",
            "LayoutItemUnit": {
                "id": "50733acb-0066-4f80-befe-832607d1c822",
                "content": "开往：",
                "componentType": "Text",
                "fontSize": 112,
                "fontFamily": "SourceHanSansSC",
                "textColor": "#000000",
                "bold": false,
                "italic": false,
                "align": "center",
                "language": 0,
                "positionX": 0,
                "positionY": 0,
                "width": 400,
                "height": 140
            }
        },
        {
            "id": "64712011-2914-49f4-b1f6-9248da9f94d6",
            "opacity": 1,
            "width": 924,
            "height": 140,
            "positionX": 60,
            "positionY": 52,
            "itemType": "DIGITAL_CLOCK",
            "LayoutItemUnit": {
                "id": "fde3ee06-6fea-4898-aa03-354276e7fbaa",
                "content": "2024年8月23日 星期五",
                "componentType": "Time",
                "fontSize": 72,
                "fontFamily": "SourceHanSansSC",
                "textColor": "#000000",
                "bold": false,
                "italic": false,
                "align": "center",
                "language": 0,
                "positionX": 0,
                "positionY": 0,
                "width": 924,
                "height": 140
            }
        },
        {
            "id": "1690d3b2-4383-4453-8cb5-03996874c248",
            "opacity": 1,
            "width": 400,
            "height": 160,
            "positionX": 60,
            "positionY": 692,
            "itemType": "STATIC_TEXT",
            "LayoutItemUnit": {
                "id": "391db367-9f07-417a-9a01-75016d2e421b",
                "content": "首班车",
                "componentType": "Text",
                "fontSize": 112,
                "fontFamily": "SourceHanSansSC",
                "textColor": "#eb3249",
                "bold": false,
                "italic": false,
                "align": "center",
                "language": 0,
                "positionX": 0,
                "positionY": 0,
                "width": 400,
                "height": 160
            }
        },
        {
            "id": "60a8f4ac-24d7-4c4a-98f7-8db9ef3f96ba",
            "opacity": 1,
            "width": 400,
            "height": 160,
            "positionX": 60,
            "positionY": 972,
            "itemType": "STATIC_TEXT",
            "LayoutItemUnit": {
                "id": "66dbf518-2e0e-4d64-a258-acf969867487",
                "content": "末班车",
                "componentType": "Text",
                "fontSize": 112,
                "fontFamily": "SourceHanSansSC",
                "textColor": "#eb3249",
                "bold": false,
                "italic": false,
                "align": "center",
                "language": 0,
                "positionX": 0,
                "positionY": 0,
                "width": 400,
                "height": 160
            }
        },
        {
            "id": "46ec3b21-f280-4657-9e7e-6aa5e68edccf",
            "opacity": 1,
            "width": 400,
            "height": 160,
            "positionX": 60,
            "positionY": 1600,
            "itemType": "STATIC_TEXT",
            "LayoutItemUnit": {
                "id": "0538b566-c01a-496c-aee4-c434f67dd467",
                "content": "首班车",
                "componentType": "Text",
                "fontSize": 112,
                "fontFamily": "SourceHanSansSC",
                "textColor": "#eb3249",
                "bold": false,
                "italic": false,
                "align": "center",
                "language": 0,
                "positionX": 0,
                "positionY": 0,
                "width": 400,
                "height": 160
            }
        }
    ]
}


{
    "_elements": [
        {
            "_type": "element",
            "_name": "LayoutTemplate",
            "_elements": [
                {
                    "_type": "element",
                    "_name": "backgroundImage",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "MTTlj7fnur_nq5nljoXliIflm74=.png"
                        }
                    ]
                },
                {
                    "_type": "element",
                    "_name": "width",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "3840"
                        }
                    ]
                },
                {
                    "_type": "element",
                    "_name": "height",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "2160"
                        }
                    ]
                },
                {
                    "_type": "element",
                    "_name": "terminalType",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "2"
                        }
                    ]
                },
                {
                    "_type": "element",
                    "_name": "scaling",
                    "_elements": [
                        {
                            "_type": "text",
                            "_text": "4.0"
                        }
                    ]
                },
                {（subElement）
                    "_type": "element",
                    "_name": "LayoutItem",
                    "_elements": [
                        {（layoutItem）
                            "_type": "element",
                            "_name": "id",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "39f61c8d-6b7d-4e32-abca-b8a002b07e94"
                                }
                            ]
                        },
                        {（layoutItem）
                            "_type": "element",
                            "_name": "opacity",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "1.0"
                                }
                            ]
                        },
                        {
                            "_type": "element",
                            "_name": "width",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "400"
                                }
                            ]
                        },
                        {
                            "_type": "element",
                            "_name": "height",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "140"
                                }
                            ]
                        },
                        {
                            "_type": "element",
                            "_name": "positionX",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "56"
                                }
                            ]
                        },
                        {
                            "_type": "element",
                            "_name": "positionY",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "440"
                                }
                            ]
                        },
                        {
                            "_type": "element",
                            "_name": "itemType",
                            "_elements": [
                                {
                                    "_type": "text",
                                    "_text": "STATIC_TEXT"
                                }
                            ]
                        },
                        {
                            "_type": "element",
                            "_name": "LayoutItemUnit",
                            "_elements": [
                                {
                                    "_type": "element",
                                    "_name": "id",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "28fa74ac-bff9-493d-a41b-99f140e277ff"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "content",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "开往："
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "componentType",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "Text"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "fontSize",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "112"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "fontFamily",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "SourceHanSansSC"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "textColor",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "#000000"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "bold",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "false"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "italic",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "false"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "align",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "center"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "language",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "0"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "positionX",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "0"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "positionY",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "0"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "width",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "400"
                                        }
                                    ]
                                },
                                {
                                    "_type": "element",
                                    "_name": "height",
                                    "_elements": [
                                        {
                                            "_type": "text",
                                            "_text": "140"
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    ]
}





{
    "body": {
        "messageBody": {
            "devid": "0.14.10.1.4",
            "currentUser": "root/超管",
            "filefullpath": "/playlist/line12test/0.14.10.1.4line12test.json",
            "filename": "/playlist/line12test/0.14.10.1.4line12test.json",
            "pass": "admin",
            "user": "root",
            "plan_id": "24a7b0a9-024c-46d6-8bb4-0fabb88af77e",
            "http_ip": "10.18.10.16"
        },
        "messageCommand": "DOWNLOAD_PLAY_CTRL_PLAN"
    },
    "header": {
        "end": true,
        "messageNo": "2f204542-d186-4bd6-979e-d3b8afdd57d3",
        "messagePublishType": "direct",
        "messageReceiver": "0.14.10.1.4",
        "messageSender": "0.business.0",
        "messageType": "P2P_command_message",
        "timeout": 900000
    }
}










{
    "body": {
        "messageBody": {
            "planInfo": {
                "stationCount": 10,
                "stationInfoList": [
                    {
                        "firstLastTrainInfo": [
                            {
                                "destinationCode": "010",
                                "destinationId": "0.12.0",
                                "flag": "first train",
                                "pisStationId": "0.12.9",
                                "platformId": 21,
                                "scheduledArrivalTime": "06:29",
                                "scheduledDepartTime": "06:29",
                                "serverNumber": "008",
                                "stationId": 10
                            }
                        ],
                        "index": 1,
                        "name": "0.12.9",
                        "platInfoId": 21,
                        "stationCode": 10,
                        "trainInfoList": [
                            {
                                "arrivalStatus": 0,
                                "coachList": [
                                    {
                                        "crowded": "1",
                                        "id": "1"
                                    },
                                    {
                                        "crowded": "2",
                                        "id": "2"
                                    },
                                    {
                                        "crowded": "3",
                                        "id": "3"
                                    },
                                    {
                                        "crowded": "4",
                                        "id": "4"
                                    },
                                    {
                                        "crowded": "5",
                                        "id": "5"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "6"
                                    }
                                ],
                                "compartmentCount": 0,
                                "departureStatus": 0,
                                "destinationCodeLen": 0,
                                "driverNumber": -1,
                                "english_status": "3Min",
                                "express": "0",
                                "holdStatus": 0,
                                "orderNumber": "11",
                                "otpTime": 2,
                                "outOfService": "no clear",
                                "passengerAttributesStatus": 1,
                                "preArrival": 0,
                                "scheduledArrivalTime": "2024-11-16 21:46:01",
                                "scheduledDepartTime": "2024-11-16 21:46:36",
                                "serialid": 1,
                                "serverNumber": "018",
                                "skipStatus": 0,
                                "status": "3分钟",
                                "terminal": "0.12.0",
                                "trainCnFlag": "正常",
                                "trainFlag": "no",
                                "trainId": "12028",
                                "trainScheduleList": [

                                ],
                                "validityField": "valid"
                            },
                            {
                                "arrivalStatus": 0,
                                "coachList": [
                                    {
                                        "crowded": "1",
                                        "id": "1"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "2"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "3"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "4"
                                    },
                                    {
                                        "crowded": "2",
                                        "id": "5"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "6"
                                    }
                                ],
                                "compartmentCount": 0,
                                "departureStatus": 0,
                                "destinationCodeLen": 0,
                                "driverNumber": -1,
                                "english_status": "10Min",
                                "express": "0",
                                "holdStatus": 0,
                                "orderNumber": "09",
                                "otpTime": 29,
                                "outOfService": "no clear",
                                "passengerAttributesStatus": 1,
                                "preArrival": 0,
                                "scheduledArrivalTime": "2024-11-16 21:52:32",
                                "scheduledDepartTime": "2024-11-16 21:53:07",
                                "serialid": 2,
                                "serverNumber": "030",
                                "skipStatus": 0,
                                "status": "10分钟",
                                "terminal": "0.12.0",
                                "trainCnFlag": "正常",
                                "trainFlag": "no",
                                "trainId": "12051",
                                "validityField": "valid"
                            },
                            {
                                "arrivalStatus": 0,
                                "coachList": [
                                    {
                                        "crowded": "1",
                                        "id": "1"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "2"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "3"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "4"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "5"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "6"
                                    }
                                ],
                                "compartmentCount": 0,
                                "departureStatus": 0,
                                "destinationCodeLen": 0,
                                "driverNumber": -1,
                                "english_status": "16Min",
                                "express": "0",
                                "holdStatus": 0,
                                "orderNumber": "11",
                                "otpTime": 20,
                                "outOfService": "no clear",
                                "passengerAttributesStatus": 1,
                                "preArrival": 0,
                                "scheduledArrivalTime": "2024-11-16 21:58:27",
                                "scheduledDepartTime": "2024-11-16 21:59:02",
                                "serialid": 3,
                                "serverNumber": "021",
                                "skipStatus": 0,
                                "status": "16分钟",
                                "terminal": "0.12.0",
                                "trainCnFlag": "正常",
                                "trainFlag": "no",
                                "trainId": "12015",
                                "validityField": "valid"
                            }
                        ]
                    },
                    {
                        "firstLastTrainInfo": [
                            {
                                "destinationCode": "010",
                                "destinationId": "0.12.0",
                                "flag": "first train",
                                "pisStationId": "0.12.14",
                                "platformId": 30,
                                "scheduledArrivalTime": "06:17",
                                "scheduledDepartTime": "06:18",
                                "serverNumber": "008",
                                "stationId": 15
                            }
                        ],
                        "index": 1,
                        "name": "0.12.14",
                        "platInfoId": 30,
                        "stationCode": 15,
                        "trainInfoList": [
                            {
                                "arrivalStatus": 0,
                                "coachList": [
                                    {
                                        "crowded": "1",
                                        "id": "1"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "2"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "3"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "4"
                                    },
                                    {
                                        "crowded": "2",
                                        "id": "5"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "6"
                                    }
                                ],
                                "compartmentCount": 0,
                                "departureStatus": 1,
                                "destinationCodeLen": 0,
                                "driverNumber": -1,
                                "english_status": "1Min",
                                "express": "0",
                                "holdStatus": 0,
                                "orderNumber": "09",
                                "otpTime": 29,
                                "outOfService": "no clear",
                                "passengerAttributesStatus": 1,
                                "preArrival": 0,
                                "scheduledArrivalTime": "2024-11-16 21:42:18",
                                "scheduledDepartTime": "2024-11-16 21:43:03",
                                "serialid": 0,
                                "serverNumber": "030",
                                "skipStatus": 0,
                                "status": "1分钟",
                                "terminal": "0.12.0",
                                "trainCnFlag": "正常",
                                "trainFlag": "no",
                                "trainId": "12051",
                                "validityField": "valid"
                            },
                            {
                                "arrivalStatus": 0,
                                "coachList": [
                                    {
                                        "crowded": "1",
                                        "id": "1"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "2"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "3"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "4"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "5"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "6"
                                    }
                                ],
                                "compartmentCount": 0,
                                "departureStatus": 0,
                                "destinationCodeLen": 0,
                                "driverNumber": -1,
                                "english_status": "5Min",
                                "express": "0",
                                "holdStatus": 0,
                                "orderNumber": "11",
                                "otpTime": 20,
                                "outOfService": "no clear",
                                "passengerAttributesStatus": 1,
                                "preArrival": 0,
                                "scheduledArrivalTime": "2024-11-16 21:47:22",
                                "scheduledDepartTime": "2024-11-16 21:48:07",
                                "serialid": 1,
                                "serverNumber": "021",
                                "skipStatus": 0,
                                "status": "5分钟",
                                "terminal": "0.12.0",
                                "trainCnFlag": "正常",
                                "trainFlag": "no",
                                "trainId": "12015",
                                "trainScheduleList": [

                                ],
                                "validityField": "valid"
                            },
                            {
                                "arrivalStatus": 0,
                                "coachList": [
                                    {
                                        "crowded": "1",
                                        "id": "1"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "2"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "3"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "4"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "5"
                                    },
                                    {
                                        "crowded": "1",
                                        "id": "6"
                                    }
                                ],
                                "compartmentCount": 0,
                                "departureStatus": 0,
                                "destinationCodeLen": 0,
                                "driverNumber": -1,
                                "english_status": "11Min",
                                "express": "0",
                                "holdStatus": 0,
                                "orderNumber": "11",
                                "otpTime": 29,
                                "outOfService": "no clear",
                                "passengerAttributesStatus": 1,
                                "preArrival": 0,
                                "scheduledArrivalTime": "2024-11-16 21:53:35",
                                "scheduledDepartTime": "2024-11-16 21:54:20",
                                "serialid": 2,
                                "serverNumber": "011",
                                "skipStatus": 0,
                                "status": "11分钟",
                                "terminal": "0.12.0",
                                "trainCnFlag": "正常",
                                "trainFlag": "no",
                                "trainId": "12011",
                                "validityField": "valid"
                            }
                        ]
                    }
                ]
            }
        },
        "messageCommand": "ATS_PLAN"
    },
    "header": {
        "end": true,
        "messageNo": "1205eacb-36e5-4830-b195-6d03af78a23a",
        "messageType": "P2P_command_message",
        "timeout": 10,
        "zzflag": "end"
    }
}