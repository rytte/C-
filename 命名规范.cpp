/********************/命名规范/************************************************************/

// github
1、用户名大写
2、仓库名大驼峰

// 项目
1、项目名大驼峰		// TrailLog
2、项目目录大驼峰		// TrailLog
3、项目内部目录小写   // utils
3、项目文件大驼峰		// TrailLog.cpp TrailLog.h

// 代码
类名大驼峰				// TrailLog
类方法小驼峰				// setLogLevel()
类属性m_ + 小驼峰			// m_logLevel
类静态属性s_ + 小驼峰    // s_logLevel
类静态方法小驼峰         //

局部变量小驼峰           // logLevel
全局变量大驼峰           // Buffer
全局函数小驼峰           // getCurrentTime()

宏定义全大写 + 下划线	    // ENABLE_PYBIND
enum
enum MediaQueueCapacity
{
    MAX_AUDIO_FRAMES = 30,
    MAX_VIDEO_FRAMES = 20,
    MAX_AUDIO_PACKETS = 30,
    MAX_VIDEO_PACKETS = 20
};
enum class
enum class ThreadType {
    MediaRead,   
    VideoDecode, 
    AudioDecode, 
    VideoDisplay,
    AudioDisplay 
};

普通文件名小写
日志输出句首单词首字母大写

