/********************/命名规范/************************************************************/

// github
1、用户名小写
2、仓库名小写 + 连字符

// 项目
1、项目名小写 + 连字符		// trail-log
2、项目目录小写 + 连字符		// trail-log
//3、项目文件小写 + 下划线		// traillog.cpp traillog.h
3、项目文件大驼峰				// TrailLog.cpp TrailLog.h

// 代码
1、类名大驼峰					// TrailLog
2、类方法小驼峰				// setLogLevel()
3、类属性m_ + 小驼峰			// m_logLevel
4、静态成员变量s_ + 小驼峰    // s_logLevel
5、局部变量小驼峰            // logLevel
6、宏定义大写 + 下划线		// ENABLE_PYBIND
7、 enum
enum MediaQueueCapacity
{
    MAX_AUDIO_FRAMES = 30,
    MAX_VIDEO_FRAMES = 20,
    MAX_AUDIO_PACKETS = 30,
    MAX_VIDEO_PACKETS = 20
};
8、 enum class
enum class ThreadType {
    MediaRead,   
    VideoDecode, 
    AudioDecode, 
    VideoDisplay,
    AudioDisplay 
};
9、全局函数小驼峰

