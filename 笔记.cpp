


git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890


git config --global - l


git config --global --unset http.proxy
git config --global --unset https.proxy






{
    "body": {
        "messageBody": "{\"background_color\":\"black\",\"devid\":\"0.22.1.8.1\",\"limit_style\":\"limit_time\",\"limit_time\":\"2\",\"msg_priority\":\"s\",\"pass\":\"central\",\"sceneLayout\":\"d2a9e819-fc73-455b-87cc-9610f5169e8e\",\"stationsvr_id\":\"PC-Bk_Test\",\"stationsvr_pass\":\"admin\",\"stationsvr_user\":\"root\",\"text\":\"¸÷Î»³Ë¿ÍÇë×¢Òâ£¬ÓÉÓÚÉîÛÚÍ»½µ±©Óê£¬µØÃæÊª»¬£¬Çë¸÷Î»³Ë¿ÍÓÐÐòÅÅ¶Ó½øÕ¾³Ë³µ£¬ÇÐÎðÓµ¼·£¬Ð»Ð»ÅäºÏ£¡\",\"text_color\":\"white\",\"text_direction\":\"to_left\",\"text_fontSize\":20,\"text_scrollInterval\":90,\"user\":\"central\"}\n",
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
        "text" : "²»ÄÜÖØÊÔÏÂ·¢Í¬Ò»ÌõÎÄ×ÖÐÅÏ¢ test",
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

//        // ·ÖÀëRGBAÍ¨µÀ
//        std::vector<cv::Mat> backChannels(4), textChannels(4), destChannels(4);
//        cv::split(backImgMat, backChannels);
//        cv::split(textImgMat, textChannels);

//        // ¼ÆËãºÏ³ÉºóµÄRGBAÍ¨µÀ
//        for (int i = 0; i < 3; ++i)
//        {
//            //destChannels[i] = textChannels[i].mul(textChannels[3]) / 256 + backChannels[i].mul(256 - textChannels[3]) / 256;
//            destChannels[i] = ((textChannels[i] - backChannels[i]).mul(textChannels[3])) / 256 + backChannels[i];
//        }
//        destChannels[3] = textChannels[3] + backChannels[3].mul(256 - textChannels[3]) / 256;

//        // ºÏ²¢RGBÍ¨µÀºÍÐÂµÄalphaÍ¨µÀ
//        cv::merge(destChannels, dstImgMat);

//        // ½«ºÏ³É½á¹û¸´ÖÆ»Ø overlayData
//        memcpy(overlayData, dstImgMat.data, dstImgMat.total() * dstImgMat.elemSize());




//        cv::Mat backImgMat = cv::Mat(m_height, m_width, CV_8UC4, static_cast<void*>(m_backImg.bits()), static_cast<size_t>(m_backImg.bytesPerLine()));
//        cv::Mat textImgMat = cv::Mat(m_height, m_width, CV_8UC4, overlayData);
//        cv::Mat dstImgMat = cv::Mat(m_height, m_width, CV_8UC4);
//        cv::Mat alphaMat = cv::Mat(m_height, m_width, CV_8UC4);

//        // ·ÖÀëRGBAÍ¨µÀ
//        std::vector<cv::Mat> textChannels(4);
//        cv::split(textImgMat, textChannels);

//        // ºÏ³ÉÐÂµÄalphaMat
//        std::array<cv::Mat, 4> alphaChannels = {textChannels[3], textChannels[3], textChannels[3], textChannels[3]};
//        cv::merge(alphaChannels, alphaMat);

//        // ¼ÆËãºÏ³ÉºóµÄRGBAÍ¨µÀ
//        dstImgMat = ((textImgMat - backImgMat).mul(alphaMat)) / 256 + backImgMat;

//        // ½«ºÏ³É½á¹û¸´ÖÆ»Ø overlayData
//        memcpy(overlayData, dstImgMat.data, dstImgMat.total() * dstImgMat.elemSize());





{
	"id": 601,
	"mediaType" : 6,
	"rect" : "0,0,200,200",
	"ChEnMode" : 3,
	"backlmage" : "backjpg",
	"md5" : "64303e21b9c¨®1f9ab3d04088638cecd2",
	"backColor" : "",
	"zOrder" : 0,
	"params" : {
		"ATS": {
			"train1": {
				"destCh ": {
					"rect": "1,0,117,71",
						"tip" : "¿ªÍù",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},
					"destEn ": {
					"rect": "1,0,117,71",
						"tip" : "To",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},

					"trainTimeCh": {
					"rect": "0,153,214,71",
						"tip" : "±¾´ÎÁÐ³µ",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 40,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"status": {
							"rect": "20,231,185,69",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"time": {
							"rect": "128,227,140,70",
								"text" : "5",
								"font" : {
								"name": "Arial",
									"size" : 80,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"min": {
							"rect": "263,229,114,70",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						}
					}
				},

					"trainTimeEn": {
					"rect": "0,153,214,71",
						"tip" : "This  train",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 40,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"status": {
							"rect": "20,231,185,69",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"time": {
							"rect": "128,227,140,70",
								"text" : "5",
								"font" : {
								"name": "Arial",
									"size" : 80,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"min": {
							"rect ": "263, 229, 114, 70",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 45,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFD",
									"align" : 4,
									"effect" : 0
							}
						}
					}
				},

					"trainTipCh": {
						"rect": "1,0,117,71",
						"tip" : "ÊÇ·ñ¿ì³µ",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
						},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},

					"trainTipEn": {
					"rect": "1,0,117,71",
						"tip" : "IsFast",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 55,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 35,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},
					"trainTipImage":{
					"rect":"1,0,117,71"
				}
			},
				"train2": {
				"destCh ": {
					"rect": "1,0,117,71",
						"tip" : "¿ªÍù",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},
					"destEn ": {
					"rect": "1,0,117,71",
						"tip" : "To",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},

					"trainTimeCh": {
					"rect": "0,153,214,71",
						"tip" : "±¾´ÎÁÐ³µ",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 40,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"status": {
							"rect": "20,231,185,69",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"time": {
							"rect": "128,227,140,70",
								"text" : "5",
								"font" : {
								"name": "Arial",
									"size" : 80,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"min": {
							"rect": "263,229,114,70",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						}
					}
				},

					"trainTimeEn": {
					"rect": "0,153,214,71",
						"tip" : "This  train",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 40,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"status": {
							"rect": "20,231,185,69",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"time": {
							"rect": "128,227,140,70",
								"text" : "5",
								"font" : {
								"name": "Arial",
									"size" : 80,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"min": {
							"rect ": "263, 229, 114, 70",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 45,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFD",
									"align" : 4,
									"effect" : 0
							}
						}
					}
				},

					"trainTipCh": {
					"rect": "1,0,117,71",
						"tip" : "ÊÇ·ñ¿ì³µ",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},

					"trainTipEn": {
					"rect": "1,0,117,71",
						"tip" : "IsFast",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 55,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 35,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},
					"trainTipImage":{
					"rect":"1,0,117,71"
				}
			},
				"train3": {
				"destCh ": {
					"rect": "1,0,117,71",
						"tip" : "¿ªÍù",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},
					"destEn ": {
					"rect": "1,0,117,71",
						"tip" : "To",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},

					"trainTimeCh": {
					"rect": "0,153,214,71",
						"tip" : "±¾´ÎÁÐ³µ",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 40,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"status": {
							"rect": "20,231,185,69",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"time": {
							"rect": "128,227,140,70",
								"text" : "5",
								"font" : {
								"name": "Arial",
									"size" : 80,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"min": {
							"rect": "263,229,114,70",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						}
					}
				},

					"trainTimeEn": {
					"rect": "0,153,214,71",
						"tip" : "This  train",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 40,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"status": {
							"rect": "20,231,185,69",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 40,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"time": {
							"rect": "128,227,140,70",
								"text" : "5",
								"font" : {
								"name": "Arial",
									"size" : 80,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFF",
									"align" : 4,
									"effect" : 0
							}
						},
							"min": {
							"rect ": "263, 229, 114, 70",
								"text" : "",
								"font" : {
								"name": "Î¢ÈíÑÅºÚ",
									"size" : 45,
									"bold" : false,
									"italic" : false,
									"textColor" : "#FFFFFD",
									"align" : 4,
									"effect" : 0
							}
						}
					}
				},

					"trainTipCh": {
					"rect": "1,0,117,71",
						"tip" : "ÊÇ·ñ¿ì³µ",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
							"size" : 50,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
					},
						"content": {
						"rect": "35,73,438,74",
							"text" : "",
							"font" : {
							"name": "Î¢ÈíÑÅºÚ",
								"size" : 36,
								"bold" : false,
								"italic" : false,
								"textColor" : "#FFFFFF",
								"align" : 4,
								"effect" : 0
						}
					}
				},

					"trainTipEn": {
						"rect": "1,0,117,71",
						"tip" : "IsFast",
						"font" : {
						"name": "Î¢ÈíÑÅºÚ",
						"size" : 55,
						"bold" : false,
						"italic" : false,
						"textColor" : "#FFFFFF",
						"align" : 4,
						"effect" : 0
					},
					"content": {
						"rect": "35,73,438,74",
						"text" : "",
						"font" : {
							"name": "Î¢ÈíÑÅºÚ",
							"size" : 35,
							"bold" : false,
							"italic" : false,
							"textColor" : "#FFFFFF",
							"align" : 4,
							"effect" : 0
						}
					}
				},
				"trainTipImage":{
				"rect":"1,0,117,71"
				}
			}
		},
		"trainTipImageList": [
		{
			"TipID": 1,
			"TipName" : "ÆÕÍ¨",
			"fileName" : "dot1.jpg",
			"md5" : "87903e21b9c61f9ab3d04088638cecd1"
		},
		{
			"TipID": 2,
			"TipName" : "Ö±´ï",
			"fileName" : "dot1.jpg",
			"md5" : "87903e21b9c61f9ab3d04088638cecd1"
		}],
		"atsType": 0
	}
}


