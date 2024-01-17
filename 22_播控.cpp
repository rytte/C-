//******************************//main
创建MainWindow m;				//将MainWindow m;放在设置路径上面	
创建日志系统
设置路径

//******************************//MainWindow
初始化（ new UDP类：加入组播/设置监听）

new 窗口m_pBlackWindow
{
	【<ShowSig>show()】
	【<HideSig>hide()】
	【<Update>ShowControls()：显示控件及其子控件：设置长宽位置样式】
	从Json提取控件参数存入Map表
	判断中英文切换
	new YWeatherInfo 《持续更新天气信息》
	new YDynamicTextLabel（ new YDisplayManage（ new YOpenglDisplay：初始化成员）【<UpdateSig>UpdateSlot()：显示图像】）（ new YDynamicImage）《不断显示新画面》《不断进行显示图像的合成》
	new YTrainRunInfo：设置到站信息模块名（ new YTrainRunMessage单例（ new YUdpJsonMessage）《持续获取udpjson消息》）《持续更新到站信息并刷新页面》
	new YCrowdDegree（ new QTimer）【<timeout>FlickerTimeout()：刷新隔离门画面】【<PlatformDoorsSignal>UpdatePlatformDoors()：刷新隔离门画面】
	new YTrainRunInfo：设置时刻表信息模块名（ new YTrainRunMessage单例（ new YUdpJsonMessage）《持续获取udpjson消息》）《持续更新到站信息并刷新页面》
	new YMediaPlay
	new YDateTime（ new QTimer）【<timeout>UpdateSlot()：每秒更新数据】
	new YTextLabel（ new QLabel）（ new QTimer：30ms）【<timeout>UpdateSlot()：每30ms更新数据】
	new YControlBase*n
}

为窗口m_pBlackWindow设置各种属性

m_pBlackWindow显示控件及其子控件：设置长宽位置样式

new 代理文本m_pAgentText：清空接收的文本vec

new 代理文本m_pAgentDynamicText：清空接收的文本vec

清空 数据库map 版式计划vec 音量计划vec 容器

初始化Agent消息：单例模式（ new updjson消息对象用于agent接收消息：创建3个循环缓冲区，《持续收发消息线程：缓冲区内有就读/发》），《持续处理消息线程：判断命令类型，处理命令》，初始化服务器地址信息，注册接收命令

连接信号槽【<CreateWindowSignal>CreateWindowSlot()：创建窗口，判断紧急版式，打开版式文件并读取， 传入版式json new 一个新窗口m_pWindow替代旧窗口m_pWindow：设置图片路径属性，显示控件，检查覆盖。判断中英文切换】

《持续更新版式》
{
	每隔1s{ 读取配置文件，发射CreateWindowSlot创建版式，发送心跳，更新音量值。 }
	接收agent消息判断命令
	响应版式更新消息
	{ 
		new 列车运行消息模块单例
		{
			new updjson消息对象创建3个循环缓冲区，《持续收发消息线程：缓冲区内有就读 / 发》）
			《持续获取列车运行消息，递归遍历json》
		}
		为m_pWindow的子控件设置一堆属性
	}
}







QList<YControlBase *>::iterator iter;
QList<YControlBase *> children = this->findChildren<YControlBase *>();
for(iter = children.begin(); iter != children.end(); iter++)
    std::cout << (*iter)->objectName().toStdString() << std::endl;

QList<YControlBase*> children = this->findChildren<YControlBase*>();
for (auto& child : children)

YControlBase* child = this->findChild<YControlBase*>("CrowdDegreeModule");
if (child)
	std::cout << objectName().toStdString() << std::endl;


//        while(pBaseParent && pBaseParent->parent())
//            pBaseParent = dynamic_cast<YControlBase *>(pBaseParent->parent());





//******************************//Text
"align":"center",
"backgroundColor" : "#ff9c01",
"backgroundImage" : "",
"bold" : "false",
"borderColor" : "",
"content" : "末班车",
"fontFamily" : "SourceHanSansSC",
"fontSize" : "33",
"height" : "41",
"itemType" : "Text",
"layoutItem" : [

] ,
"name" : "trainFlagTs_3",
"opacity" : "1.0",
"positionX" : "328",
"positionY" : "493",
"speed" : "",
"textColor" : "#ffffff",
"width" : "165"

//******************************//Image
"content":" / hdfs / default / coach.png",
"height" : "33",
"itemType" : "Image",
"layoutItem" : [

] ,
"name" : "coachTextTs_3",
"opacity" : "1.0",
"positionX" : "407",
"positionY" : "101",
"width" : "165"

//******************************//DynamicText
"align" : "align",
"backgroundColor" : "",
"backgroundImage" : "",
"bold" : "false",
"borderColor" : "",
"content" : "尊敬的各位乘客，请按照地面箭头排队候车，先下后上，谢谢合作！",
"effect" : "left",
"fontFamily" : "SourceHanSansSC",
"fontSize" : "36",
"height" : "49",
"itemType" : "DynamicText",
"layoutItem" : [

] ,
"name" : "96c1f577-72c6-479a-9d81-3f912d8362f7",
"opacity" : "1.0",
"positionX" : "0",
"positionY" : "1026",
"speed" : "3",
"textColor" : "#ffffff",
"width" : "1920"

//******************************//main_windown
"backgroundColor" : "#999999",
"backgroundImage" : "/hdfs/6IOM5pmvQDJ4.png",
"height" : "1080",
"itemType" : "main_windown",
//"languageMode" : "1",
"layoutItem" : [
	......
]
"name" : "6195be08-715b-4e8f-889c-7cb0570bf10a",
"opacity" : "1.0",
"width" : "1920"

//******************************//DateTimeModule
"height" : "41",
"itemType" : "DateTimeModule",
"layoutItem" : [
{
        ......
}
],
"name":"48a3ea23-e690-459e-a28c-748bc2e987e7",
"opacity" : "1.0",
"positionX" : "33",
"positionY" : "23",
"width" : "1324"

//******************************//MediaPlayerModule
"height" : "761",
"itemType" : "MediaPlayerModule",
"layoutItem" : [
	......
] ,
"name" : "e09f096f-5e15-442c-a04c-c8b2299e9315",
"opacity" : "1.0",
"positionX" : "18",
"positionY" : "79",
"width" : "1357"

//******************************//MediaStream
"content" : [
{
	"media":"/hdfs/food.mp4",
	"playTimes" : "1",
	"priority" : "0"
}
] ,
"height":"761",
"itemType" : "MediaStream",
"layoutItem" : [
	
] ,
"name" : "3c97d48d-26f9-448d-b08c-e86c136308e7",
"opacity" : "1.0",
"positionX" : "0",
"positionY" : "0",
"width" : "1357"

//******************************//ArrivalInfoModule
"height" : "692",
"itemType" : "ArrivalInfoModule",
"layoutItem" : [
	......
]
"name":"4f0efdaa-a189-43c4-b30a-df801064411f",
"positionX" : "1393",
"positionY" : "135",
"width" : "496"

//******************************//CrowdDegreeModule
"height" : "134",
"itemType" : "CrowdDegreeModule",
"layoutItem" : [

]
"name":"aa18066f-09ee-45a0-b301-674cb94801ee",
"positionX" : "523",
"positionY" : "865",
"width" : "1186"





//YControlBase
SetProperty("imagePath", resoucePath, "");
SetProperty("contentCn", "");
SetProperty("contentEn", "");
SetProperty("languageMode", to_string(languageMode));
SetProperty("record_opacity", opacity);
SetProperty("record_positionX", to_string(x));
SetProperty("record_positionY", to_string(y));
SetProperty("record_width", to_string(w));
SetProperty("record_height", to_string(h));
SetProperty("record_bgColor", bgColor);
SetProperty("record_bgImage", bgImage);
SetProperty("record_boW", boW);
SetProperty("record_boR", boR);
SetProperty("record_boColor", boColor);
SetProperty("controlVisible", "true");
pBaseParent->SetProperty("curVolumeValue", tmpVolume);

//MediaStream
pBaseParent->SetProperty("isBadDoor", "YTRUE", "MediaStream");
pBaseParent->SetProperty("doorDestroyText", doorRemindText, "MediaStream");
m_pWindow->SetProperty("presetPicture", "presetPicture.jpg", "MediaStream");
m_pWindow->SetProperty("volume", m_dataBaseMap["volume"].GetValue(), "MediaStream");
m_pWindow->SetProperty("Stream_Addr_1", m_dataBaseMap["Stream_Addr_1"].GetValue(), "MediaStream");
m_pWindow->SetProperty("Stream_Addr_2", m_dataBaseMap["Stream_Addr_2"].GetValue(), "MediaStream");
m_pWindow->SetProperty("Stream_Addr_3", m_dataBaseMap["Stream_Addr_3"].GetValue(), "MediaStream");
m_pWindow->SetProperty("dynamic_text", "", "MediaStream");
m_pWindow->SetProperty("dynamic_backgroundColor", "", "MediaStream");
m_pWindow->SetProperty("dynamic_textColor", "", "MediaStream");
m_pWindow->SetProperty("dynamic_fontSize", "", "MediaStream");
m_pWindow->SetProperty("dynamic_speed", "", "MediaStream");

//DynamicText
m_pWindow->SetProperty("messageCommand", "PROMPT", "DynamicText");

//YTextLabel
SetProperty("record_fontFamily", fontFamily);
SetProperty("record_fontSize", to_string(fontSize));
SetProperty("record_bold", to_string(textBold));
SetProperty("record_italic", to_string(Italic));
SetProperty("contentPixWidth", to_string(contentPixWidth));
SetProperty("record_content", textContent);
SetProperty("record_align", textAlign);
SetProperty("record_textColor", textColor);
SetProperty("textPositionX", to_string(position_x));

//ArrivalInfoModule
m_pWindow->SetProperty("ServerIp", m_dataBaseMap["atsMessageAddr"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("ServerPort", m_dataBaseMap["atsMessagePort"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("stationName", m_dataBaseMap["stationName"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("direction", m_dataBaseMap["direction"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("position", m_dataBaseMap["position"].GetValue(), "ArrivalInfoModule");

//CrowdDegreeModule
m_pWindow->SetProperty("ServerIp", m_dataBaseMap["atsMessageAddr"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("ServerPort", m_dataBaseMap["atsMessagePort"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("stationName", m_dataBaseMap["stationName"].GetValue(), "ArrivalInfoModule");

//TimeScheduleModule
m_pWindow->SetProperty("ServerIp", m_dataBaseMap["atsMessageAddr"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("ServerPort", m_dataBaseMap["atsMessagePort"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("stationName", m_dataBaseMap["stationName"].GetValue(), "ArrivalInfoModule");

//WeatherInfoModule
m_pWindow->SetProperty("ServerIp", m_dataBaseMap["atsMessageAddr"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("ServerPort", m_dataBaseMap["atsMessagePort"].GetValue(), "ArrivalInfoModule");
m_pWindow->SetProperty("stationName", m_dataBaseMap["stationName"].GetValue(), "ArrivalInfoModule");







DateTimeModule
{
	Text：xxxx年xx月xx日 星期x xx : xx:xx
}
MediaPlayerModule
{
	MediaStream
}
DynamicText：尊敬的各位乘客，请按照地面箭头排队候车，先下后上，谢谢合作！
Text：本趟车开往
Text：下一趟车
Text：第三趟车
ArrivalInfoModule
{
	Text：首班车
	Text：龙子湖东站
	Text：99
	Text：分钟
	Text：即将到站
	Text：99
	Text：分钟
	Text：龙子湖东站
	Text：99
	Text：龙子湖东站
	Text：分钟
	Text：末班车
	Text：末班车
}
CrowdDegreeModule
{
	Image
	Image
	Image
	Image
	Image
	Image
	Image
	Image
	Image
	Image
	Image
	Image
}







std::cout << "m_content:" << GetProperty("content") << std::endl;