YPlayPanModule::UpdatePlayContent		1254行		文本打包		//不需要
YPlayPanModule::ThreadPlayPan			340行		文本的定时显示
YPlayPanModule::UdpReceiveHandle		447行		处理文本消息
YPlayPanModule::DealTextCommondMessage	1798行	文本优先级处理
YPlayPanModule::UpdateTextData			1886			更新文本信息




启动时读取预制文本：判断是否存在，存在则读取预制文本而非版式文本
接收到"DEFAULT_PROMPT_TEXT"命令时，将内容设置为默认版式，优先级低于提示文本，则在提示文本定时结束后会自动播放。





改动
class YPlayPanModule						303行		添加m_DefaultInfo属性
YPlayPanModule::YPlayPanModule()			62行			初始化m_DefaultInfo成员
YVoid YPlayPanModule::UpdatePlayContent()	1269行		打包



textinfo结构体	
m_PromptInfo		m_ExclusiveInfo		m_EmergencyInfo

宏定义
PROMPT_TEXT_STATE		EMERGENCY_TEXT_STATE		EXCLUSIVE_TEXT_STATE

*NORMAL_TEXT_STATE(0)->不播放文本，正常播放；



读取日期播表滚动文本位置
MainWindow::Init									主窗口初始化
m_pPlayPanModule->SetPlayPanPath(strPlayPanPath);	设置播放计划路径
YPlayPanModule::ReadDatePlayplan					读取日期播表
ResumeTextDisplayStatusArray();						文本播放状态恢复
UpdateTextData(&tmpTextInfo, iTextType);				更新文本数据

读取xml内容
Timer1000msHandle()													1000ms定时器
m_pCurrentScreen = m_pScreenManager->GetWndByJasonStr					调用窗口创建模块，获取当前窗口对象
YInterfaceWnd* pTmpWnd = YGlobGetWndFromXml							读取版式文件
xmlobj.XmlStreamReaderFile(xmlContent.c_str(), crowedbackgroundimagename);	读取xml版式文件
SetWndProperty(pItemTypeWnd, pLayoutItem);								设置控件参数
pControlName->AddProperty("content", pContentText);						添加到属性

设置显示文本数据位置
Timer1000msHandle()										1000ms定时器
m_pCurrentScreen = m_pScreenManager->GetWndByJasonStr		通过jason描述的内容，获取到窗口对象
//YWndManager::ProcessJson(const YChar* pStrJson)				解析jason文本
UpdateDynamicText(&m_promptTextValue);							更新动态文本
UpdateValue(pChildfaceWnd, strtmpvalue.toStdString());				更新控件内容

从m_PromptInfo到控件播放
每秒进行m_PromptInfo打包到strPlayConten，赋给成员m_strOutPlayContent
1000ms定时器调用GetCurrentPlayContent()获取m_strOutPlayContent值，赋值给strCurrentSecondPlayJason，并解析到jasonRoot
1000ms定时器中，m_pCurrentScreen = m_pScreenManager->GetWndByJasonStr传入jasonRoot。此时与xml的读取、设置显示文本处于同一函数
在函数中赋值给m_strPrevContentJson，该成员m_strPrevContentJson在AtsJson()中被调用
AtsJson()1：YWndManager::Update()中调用
AtsJson()2：m_pCurrentScreen = m_pScreenManager->GetWndByJasonStr中调用
AtsJson()3：UpdateAtsData中调用3次
//暂略

pDynamicText->m_strText设置位置
即UpdateDynamicText(&m_promptTextValue)的传入参数m_promptTextValue的成员m_strText
ProcessJson() 中 m_promptTextValue.m_strText = strtmptext + "        ";			//打包时在键名该为"playprompttext"
**调查该值何时被xml的值替换


agent发送的最后一条滚动文本消息存放在日期播表里



任务
限时文本结束后读取使用日期播表中的文本（而非版式中的文本）
接收到"DEFAULT_PROMPT_TEXT"命令后，使用"DEFAULT_PROMPT_TEXT"中的文本

0、滚动文本定时器结束后读取日期播表文本
1、注册命令消息中加入：YAgentMsgManager::Instance().RegisterMsg(m_strMsgSubscriberName, "DEFAULT_PROMPT_TEXT");
2、UdpReceiveHandle中设置接收"DEFAULT_PROMPT_TEXT"命令
3、DealTextCommondMessage 中 1837行添加 ||  m_msgRoot["limit_style"].asString().empty()

添加全新等级 DEFAULT_TEXT_STATE
添加新成员 m_DefaultInfo
日期播表中的数据读取到m_DefaultInfo中
在DealTextCommondMessage及其内函数中操作DEFAULT_TEXT_STATE和m_DefaultInfo
打包处判断若有m_PromptInfo则打包m_PromptInfo，若m_PromptInfo为空则打包m_DefaultInfo


{
    "header":{
	"messageType":"P2P_command_message",
	"end" : true,
	"messageNo" : "e87c409d362646b19bd050ebb26e545e",
	"messageReceiver" : "station_svr",
	"messageSender" : "station_svr_client1256bd2b00b046ae8cc6ec163e53d52d",
	"timeout" : 1
    },
    "body":{
	"messageCommand":"DEFAULT_PROMPT_TEXT",
	"messageBody" : "{"stationsvr_id":"1.1.1","stationsvr_user":"root","stationsvr_pass":"admin","devid":"18.2.3.4","user":"central","pass":"central","text":"test","background_color":"black","text_color":"white","text_scrollInterval":120,"text_fontSize":85}"
    }
}




{
    "body":{
	"messageBody":"{\"background_color\":\"black\",\"devid\":\"0.22.1.8.1\",\"limit_style\":\"limit_time\",\"limit_time\":\"1\",\"msg_priority\":\"s\",\"pass\":\"central\",\"sceneLayout\":\"d2a9e819-fc73-455b-87cc-9610f5169e8e\",\"stationsvr_id\":\"PC-Bk_Test\",\"stationsvr_pass\":\"admin\",\"stationsvr_user\":\"root\",\"text\":\"各位乘客请注意，由于深圳突降暴雨，地面湿滑，请各位乘客有序排队进站乘车，切勿拥挤，谢谢配合！\",\"text_color\":\"white\",\"text_direction\":\"to_left\",\"user\":\"central\"}\n",
	"messageCommand" : "PLAY_PROMPT_TEXT"
    },
    "header" : {
	"end":true,
	"messageNo" : "39c43a88-ec11-4e02-9400-e2fd7969bb35",
	"messageReceiver" : "bk_player",
	"messageSender" : "Bk_Test_Tool",
	"messageType" : "P2P_command_message",
	"timeout" : 1,
	"zzflag" : "end"
    }
}



"messageCommand":"DEFAULT_PROMPT_TEXT",
"messageBody" :
"{
	"stationsvr_id":"1.1.1",
	"stationsvr_user":"root",
	"stationsvr_pass":"admin",
	"devid":"18.2.3.4",
	"user":"central",
	"pass":"central",
	"text":"test",
	"background_color":"black",
	"text_color":"white",
	"text_scrollInterval":120,
	"text_fontSize":85
}"



"messageCommand" : "PLAY_PROMPT_TEXT"
"messageBody" :
"{
	"stationsvr_id" : "PC-Bk_Test",
	"stationsvr_user" : "root",
	"stationsvr_pass" : "admin",
	"devid" : "0.22.1.8.1",
	"user" : "central"
	"pass" : "central",
	"text" : "各位乘客请注意，由于深圳突降暴雨，地面湿滑，请各位乘客有序排队进站乘车，切勿拥挤，谢谢配合！",
	"background_color":"black",
	"text_color" : "white",

*	"limit_style":"limit_time",
*	"limit_time":"1",
*	"msg_priority":"s",
不涉及	"sceneLayout":"d2a9e819-fc73-455b-87cc-9610f5169e8e",
不涉及	"text_direction":"to_left",
}\n",



bug：先发一次default，再发一次prompt，两个都更新为prompt
	只发default无响应