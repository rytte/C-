/********************/QT介绍/************************************************************/

//Qt工具
Qt Designer 被称为Qt设计师，可视化 UI 设计器。
Qt Linguist 被称为Qt语言家。翻译工具，用于国际化（i18n）
Qt Assistant 被称为Qt助手（也就是帮助模式），Qt 帮助文档查看器。


//QT库主要模块
模块名称			简介									主要功能																	常见类 / 组件示例
Qt Core			Qt 的核心模块，提供基本非 GUI 功能		包括事件循环、信号槽机制、时间、文件、线程、JSON / XML、数据结构、国际化等	QObject, QTimer, QFile, QThread, QDateTime
Qt GUI			提供与图形界面相关的底层功能			包括图像处理、字体、颜色、OpenGL、2D绘图、图形视图等						QImage, QPainter, QFont, QColor
Qt Widgets		提供传统的窗口部件和控件				包括按钮、标签、文本框、表格、布局、对话框等 GUI 控件						QPushButton, QLabel, QLineEdit, QTableWidget
Qt Network		提供网络通信能力						包括 TCP / UDP 套接字、HTTP 请求、FTP、主机解析、网络会话管理等				QTcpSocket, QUdpSocket, QNetworkAccessManager
Qt SQL			提供数据库访问接口					支持 SQLite、MySQL、PostgreSQL 等数据库，支持模型视图、事务等				QSqlDatabase, QSqlQuery, QSqlTableModel
Qt Multimedia	提供音视频播放与录制、摄像头访问等功能	支持音视频播放、音频录制、摄像头、媒体控制等								QMediaPlayer, QAudioOutput, QCamera
Qt Quick		基于 QML 的现代界面开发模块			提供声明式 UI 设计、动画、状态、交互等，适合快速开发跨平台现代界面			QQuickView, QQmlApplicationEngine, QML 语言元素（如 Rectangle, Text, ListView）




