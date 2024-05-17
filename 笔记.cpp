


git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890


git config --global - l


git config --global --unset http.proxy
git config --global --unset https.proxy






{
        "messageCommand": "READ_ARRANGEMENT",
        "messageBody" : {
                "text_id": "dabe86b385423212342323"
        }
}

READ_ARRANGEMENT

PLAY_PROMPT_TEXT

PLAY_EXCLUSIVE_TEXT

RECOVER_TO_PLAN_MODE




[
{
        "tripNum": 1,
                "trainCode" : "34",
                "trainType" : 0,
                "trainTypeCn" : "未知",
                "trainTypeEn" : "Unknown",
                "trainGroupCn" : "4节编组",
                "trainGroupEn" : "4-section grouping",
                "originalTime" : 1712905200,
                "arriveTimeStr" : "07:00",
                "arriveTime" : 1,
                "unit" : 0,
                "unitCn" : "分",
                "unitEn" : "min",
                "nearStation" : 0,
                "nearStationCn" : "即将到站",
                "nearStationEn" : "Arriving",
                "startStationCode" : "1",
                "startStationName" : "福州火车站",
                "startStationNameEn" : "FuZhouHuoChe",
                "destStationCode" : "15",
                "destStationName" : "文岭站",
                "destStationNameEn" : "WenLing",
                "holdStatus" : 0,
                "holdStatusCn" : "非扣车",
                "holdStatusEn" : "Unhold",
                "stableStatus" : 0,
                "stableStatusCn" : "非停稳",
                "stableStatusEn" : "Unstable",
                "skinStatus" : 0,
                "skinStatusCn" : null,
                "skinStatusEn" : null,
                "serviceStatus" : 0,
                "serviceStatusCn" : "非清客",
                "serviceStatusEn" : "Unservice",
                "lastTrain" : 0,
                "firstTrain" : 0,
                "crowdings" : [
                        0,
                                0,
                                0,
                                0
                ] ,
                "temperature": [
                        0,
                                0,
                                0,
                                0
                ]
},
    {
        "tripNum": 2,
        "trainCode" : "35",
        "trainType" : 0,
        "trainTypeCn" : "未知",
        "trainTypeEn" : "Unknown",
        "trainGroupCn" : "4节编组",
        "trainGroupEn" : "4-section grouping",
        "originalTime" : 1712908800,
        "arriveTimeStr" : "08:00",
        "arriveTime" : 1,
        "unit" : 0,
        "unitCn" : "分",
        "unitEn" : "min",
        "nearStation" : 0,
        "nearStationCn" : "即将到站",
        "nearStationEn" : "Arriving",
        "startStationCode" : "1",
        "startStationName" : "福州火车站",
        "startStationNameEn" : "FuZhouHuoChe",
        "destStationCode" : "15",
        "destStationName" : "文岭站",
        "destStationNameEn" : "WenLing",
        "holdStatus" : 0,
        "holdStatusCn" : "非扣车",
        "holdStatusEn" : "Unhold",
        "stableStatus" : 0,
        "stableStatusCn" : "非停稳",
        "stableStatusEn" : "Unstable",
        "skinStatus" : 0,
        "skinStatusCn" : null,
        "skinStatusEn" : null,
        "serviceStatus" : 0,
        "serviceStatusCn" : "非清客",
        "serviceStatusEn" : "Unservice",
        "lastTrain" : 0,
        "firstTrain" : 0,
        "crowdings" : [
            0,
            0,
            0,
            0
        ] ,
        "temperature": [
            0,
            0,
            0,
            0
        ]
    },
    {
        "tripNum": 3,
        "trainCode" : "36",
        "trainType" : 0,
        "trainTypeCn" : "未知",
        "trainTypeEn" : "Unknown",
        "trainGroupCn" : "4节编组",
        "trainGroupEn" : "4-section grouping",
        "originalTime" : 1712912400,
        "arriveTimeStr" : "09:00",
        "arriveTime" : 1,
        "unit" : 0,
        "unitCn" : "分",
        "unitEn" : "min",
        "nearStation" : 0,
        "nearStationCn" : "即将到站",
        "nearStationEn" : "Arriving",
        "startStationCode" : "1",
        "startStationName" : "福州火车站",
        "startStationNameEn" : "FuZhouHuoChe",
        "destStationCode" : "15",
        "destStationName" : "文岭站",
        "destStationNameEn" : "WenLing",
        "holdStatus" : 0,
        "holdStatusCn" : "非扣车",
        "holdStatusEn" : "Unhold",
        "stableStatus" : 0,
        "stableStatusCn" : "非停稳",
        "stableStatusEn" : "Unstable",
        "skinStatus" : 0,
        "skinStatusCn" : null,
        "skinStatusEn" : null,
        "serviceStatus" : 0,
        "serviceStatusCn" : "非清客",
        "serviceStatusEn" : "Unservice",
        "lastTrain" : 0,
        "firstTrain" : 0,
        "crowdings" : [
            0,
            0,
            0,
            0
        ] ,
        "temperature": [
            0,
            0,
            0,
            0
        ]
    }
]


AVRational time_base = m_pFormatCtx->streams[m_videoIndex]->time_base;
int64_t duration = m_pFormatCtx->streams[m_videoIndex]->duration;
double microseconds = av_rescale_q(duration, time_base, AVRational({ 1,AV_TIME_BASE }));
printf("Video duration: %.3f seconds\n", microseconds / 1000 / 1000);

