
//添加库文件
"调试 >> 调试属性"  进入属性页
"C/C++ >> 常规 >> 附加包含目录" 填写头文件目录路径
"链接器 >> 常规 >> 附加库目录" 填写库文件目录路径
"链接器 >> 输入 >> 附加依赖项" 填写所有所需的库文件名，包含后缀


//常见问题
"调试模式下应该使用debug库，而项目中添加的是release库"
1 > SoundTouch_x64.lib(SoundTouch.obj) : error LNK2038 : 检测到“_ITERATOR_DEBUG_LEVEL”的不匹配项: 值“0”不匹配值“2”(main.obj 中)
1 > SoundTouch_x64.lib(SoundTouch.obj) : error LNK2038 : 检测到“RuntimeLibrary”的不匹配项: 值“MT_StaticRelease”不匹配值“MTd_StaticDebug”(main.obj 中)

R"(链接不到库：
1、库文件位数于系统位数不一致
2、库文件架构与系统架构不一致
3、库文件路径添加错误
4、库文件编译器与项目编译器不一致
)"
1 > main.obj : error LNK2019 : 无法解析的外部符号 "public: __cdecl soundtouch::SoundTouch::SoundTouch(void)" (? ? 0SoundTouch@soundtouch@@QEAA@XZ)，函数 main 中引用了该符号


