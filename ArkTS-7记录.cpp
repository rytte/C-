

Q: Marquee控件滚动时切换到其它页面会奔溃
A: 切换前暂停滚动，并延时至少7ms再切换

Q: 下载文件时切换页面会奔溃


Q: 重新更新版式会奔溃
A: 更新前暂停滚动和视频播放，并延时至少5ms



//创建空对象
private videoContentJson : ContentItem = Object();
private videoContentJson: ContentItem = Object() as ContentItem;
private videoContentJson: ContentItem = {} as ContentItem;
private videoContentJson: ContentItem | null = null;		// 使用前需要判断null
