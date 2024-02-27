/********************/绘图系统/************************************************************/


Qt中绘制2D图形最核心的一个类是QPainter。
类QPainter是在设备类QPaintDevice上绘制几何图形（包括直线、曲线、圆形、弧形、矩形等等），
其中设备类QPaintDevice的子类又有QWidget、QImage、QPictrue、QPixmap、QOpenGLPaintDevice等，
也即是说，我们可以继承这些类，通过重写QPaintEvent事件进行重绘，或者用事件过滤器捕获QPaintEvent事件信息进行响应重绘也行。


QPen：绘制几何图形边缘的线段颜色、线段宽度、线段各种类型（点画线、虚线、solid实体线段）等等；
QBrush：填充几何图形的调色板，由颜色和填充风格组成。
QPixmap：加载图片资源，一般是较小的图片。如果图片很大，可以用QImage，然后通过QPixmap::fromImage(QImage*)进行加载；



QPainter 用于执行绘图操作，其提供的 API 在 GUI 或 QImage、QOpenGLPaintDevice、QWidget 和QPaintDevice 显示图形（线、形状、渐变等）、文本和图像。
QPaintDevice 不直接绘制物理显示画面，而利用逻辑界面的中间媒介。例如，绘制矩形图形时，为了将对象绘制到 QWidget、QGLPixelBuffer、QImage、QPixmap、QPicture 等多种界面中间，必须使用 QPaintDevice。
QPaintEngine 提供了一些接口，可用于 QPainter 在不同的设备上进行绘制。



//绘制直线
void QCustomWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPen pen;
	pen.setColor(QColor(255, 0, 0, 255));				//设置颜色
	pen.setWidth(20);								//设置线段粗细

	QPainter painter(this);
	painter.setPen(pen);							//设置画笔
	painter.setRenderHint(QPainter::Antialiasing, true);	// 反走样
	painter.drawLine(QPoint，QPoint);					//绘制直线，同时指定位置
}

//绘制图形
void QCustomWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	//绘图前准备画笔、画刷
	QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
	pen.setColor(QColor(255, 0, 0, 255));
	QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
	brush.setColor(QColor(0, 255, 0, 120));
	brush.setStyle(Qt::SolidPattern);
	QPainter painter(this);   //可在QPaintDevice上绘制各种图形。QPaintDevice有之类QWidget、QImage、QOpenGLPaintDevice等
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.drawRect(50, 50, 200, 100);
}

//绘制图像
void QCustomWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);   //可在QPaintDevice上绘制各种图形。QPaintDevice有之类QWidget、QImage、QOpenGLPaintDevice等

	//绘制图片
	QPixmap pixmap;
	pixmap.load((QString(":/resource/image/向右箭头.jpg")));
	painter.drawPixmap(rect().width() - 50, 0, 50, 50, pixmap);
}



//绘制文本（QFont）
void MainWindow::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	// 设置画笔颜色
	painter.setPen(QColor(0, 160, 230));

	// 设置字体：微软雅黑、点大小50、斜体
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(50);
	font.setItalic(true);
	painter.setFont(font);

	// 绘制文本
	painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

//绘制弧形
void MainWindow::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	// 矩形
	QRectF rect(90.0, 90.0, 80.0, 90.0);
	// 起始角度
	int startAngle = 30 * 16;
	// 跨越度数
	int spanAngle = 120 * 16;

	QPainter painter(this);

	// 反走样
	painter.setRenderHint(QPainter::Antialiasing, true);

	// 设置画笔颜色、宽度
	painter.setPen(QPen(QColor(0, 160, 230), 2));

	// 绘制弧线
	painter.drawArc(rect, startAngle, spanAngle);
}


//绘制椭圆
void MainWindow::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	// 反走样
	painter.setRenderHint(QPainter::Antialiasing, true);

	// 设置画笔颜色、宽度
	painter.setPen(QPen(QColor(0, 160, 230), 2));

	// 绘制椭圆
	painter.drawEllipse(QPointF(120, 60), 50, 20);

	// 设置画刷颜色
	painter.setBrush(QColor(255, 160, 90));

	// 绘制圆
	painter.drawEllipse(QPointF(120, 140), 40, 40);
}


//绘制多边形
void MainWindow::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	// 反走样
	painter.setRenderHint(QPainter::Antialiasing, true);

	// 设置画笔颜色
	painter.setPen(QColor(0, 160, 230));

	// 各个点的坐标
	static const QPointF points[4] = { QPointF(30, 40), QPointF(60, 150), QPointF(150, 160), QPointF(220, 100) };

	// 绘制多边形
	painter.drawPolygon(points, 4);
}









/********************/绘图系统/************************************************************/

一.基本绘图属性：

1.基本绘图类：

Qt的绘图功能基于QPainter、QPainterDevice和QPainterEngine三个类。

QPaintDevice类表示QPainter的绘图设备，QPainter能在QPaintDevice的子类上进行图形绘制，
QpaintDevice子类包含QImage、QOpenGLPaintDevice、QWidget、QPixmap、PixelBuffer、
QGLFramebufferObject、QPicture、QPrinter。

2.绘图事件：

void wiget::paintEvent(QPaintEvent * event) {}

QPainter只能在paintEvent中进行绘图。paintEvent事件在窗口刷新时触发，如最大化最小化，拖动窗口边缘时也会触发。

3.主要属性：

(1) QPen：控制线条颜色宽度线性。

(2) QBrush：设置一个区域的填充特性。

(3) QFont：用于绘制文字。

(4) QPixmap: 绘制图片，适合小图片。

(5) QImage: 绘制图片，适合大图片。

(6) QBitmap: QPixmap的一个子类，单通道图。

(7) QPicture: 一张画布，可以用于保存、读取Qpainter的绘图。

(8)QPrinter类是一个在打印机上绘制的绘图设备。它允许你将图形输出到打印机，生成打印预览，或者直接生成PDF文件。

4.基本图形绘制函数：

drawPoint()       //画点

drawLine()       //画直线

drawRect()       //画矩形

drawArc()         //画圆弧

drawEllipse()      //画椭圆

drawPie()          //画扇形

drawPolygon()      //画多边形

drawChord()        //画弦

drawRoundedRect()   //画圆角矩形

drawPolyline()       //画折线

drawConvexPolygon()   //画凸多边形


二．重点绘图属性类介绍

1.QFont的一些属性与功能：

QFont是Qt框架中用于描述字体属性的工具类。

设置属性：

void setFamily(const QString & family);

void setPointSize(int size);

void setWeight(int weight);

void setItalic(bool italic);

void setUnderline(bool underline);

获取属性：

QString family() const;

int pointSize() const;

int weight() const;

bool italic() const;

bool underline() const;

2.QPen的一些属性与功能：

主要函数：

//函数原型                                功能

void setColor(QColor & color)             //设置画笔颜色

void setWidth(int width)                 //设置线条宽度

void setStyle(Qt::PenStyle style)        //设置线条样式，参数为Qt::PenStyle枚举类型

void setCapStyle(Qt::PenCapStyle style)  //设置线条端点样式，参数为Qt::PenCapStyle枚举类型

void setJoinStyle(Qt::PenJoinStyle style)//设置连接样式，参数为Qt::PenJoinStyle枚举类型

属性修改后，需要使用setPen()来应用于绘图。

（1）线条样式：

Qt::NoPen  //没有画笔，设置此属性时，用画笔不会画出任何东西。但是画刷仍然有效，表现出来就是无边界，但有填充。

Qt::SolidLine   //实线

Qt::DashLine    //虚线

Qt::DotLine     //点状线

Qt::DashDotLine   //虚线和点交替

Qt::DashDotDotLine   //虚线和双点交替

Qt::CustomDashLine   //自定义样式

（2）线条端点样式：

Qt::FlatCap      //平顶端点

Qt::SquareCap    //方形端点

Qt::RoundCap     //圆形端点

（3）线条连接样式：

Qt::BevelJoin      //斜切连接

Qt::MiterJoin      //直角连接

Qt::RoundJoin      //圆连接

3.QBrush的一些属性与功能：

主要函数：

//函数原型                                     功能

void setColor(QColor & color)                       //设置画刷颜色

void setStyle(Qt::BrushStyle style)                   //设置画刷样式

void setTexture(QPixmap & pixmap)                   //设置一个QPixmap图片作为画刷的图片

void setTextureImage(QImage & image)                //设置一个QImage类型的图片作为画刷的图片

（1）基本填充和线性填充：

//枚举常量                            描述

Qt::NoBrush                          //不填充

Qt::SolidPattern                    //单一颜色填充

Qt::HorPattern                      //水平线填充

Qt::VerPattern                      //垂直线填充

（2）渐变填充：

Qt::LinearGradientPattern     //线性渐变，需要使用QLinearGradient类对象作为Brush

Qt::RadialGradientPattern     //辐射渐变，需要使用QRadialGradient类对象作为Brush

Qt::ConicalGradientPattern    //圆锥型渐变，需要使用QConicalGradient类对象作为Brush

Qt::TexturePattern          //材质填充，需要指定texture或textureImage图片

QPrinter用法
（1）QPrinter printer;

printer.setOutputFormat(QPrinter::PdfFormat); // 设置输出格式为PDF，也可以其他格式

printer.setOutputFileName("output.pdf"); // 设置输出文件名

QPainter painter1(&printer);

painter1.drawText(100, 100, "Hello, PDF1!");

painter1.end(); // 结束绘制，内容将被发送到打印机

注意：
用QPrinter需要添加QT += printsupport；

当设置QPainter painter1(&printer)后，绘制图形输出到pdf文件，就不会再输出到ui页面上了。




//实例
#include <QPainter>
#include <QPrinter>
#include <QBitmap>
#include <QPixmap>
#include <QPicture>

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawLine(QPoint(0,0),QPoint(100,100));

    QPen pen(Qt::green,5,Qt::DotLine,Qt::RoundCap,Qt::RoundJoin);

    painter.setPen(pen);

    QRectF rectangle(70.0,40.0,80.0,60.0);

    int startAngle=30*16;

    int spanAngle=120*16;

    painter.drawArc(rectangle,startAngle,spanAngle);

    pen.setWidth(1);

    pen.setStyle(Qt::SolidLine);

    painter.setPen(pen);

    //绘制一个矩形

    painter.drawRect(160,20,50,40);

    //创建画刷

    QBrush brush(QColor(0,0,255),Qt::Dense4Pattern);

    //使用画刷

    painter.setBrush(brush);

    //绘制画刷

    painter.drawEllipse(220,20,50,50);

    //设置纹理

    brush.setTexture(QPixmap("abc.png"));

    //重新使用画刷

    painter.setBrush(brush);

    //定义四个点

    static const QPointF points[4]={
        QPointF(270.0,80.0),
        QPointF(290.0,10),
        QPointF(350.0,30),
        QPointF(390.0,50)
    };

    painter.drawPolygon(points,4);

    painter.fillRect(QRect(10,100,150,20),QBrush(Qt::darkYellow));

    painter.eraseRect(QRect(50,0,50,120));

    //线性渐变

    QLinearGradient linearGradient(QPointF(40,190),QPointF(70,190));

    //插入颜色

    linearGradient.setColorAt(0,Qt::yellow);

    linearGradient.setColorAt(0.5,Qt::red);

    linearGradient.setColorAt(1.0,Qt::green);

    //指定渐变区域以外的区域的扩散方式

    linearGradient.setSpread(QGradient::RepeatSpread);

    //使用渐变作为画刷

    painter.setBrush(linearGradient);

    painter.drawRect(10,170,90,40);

    //辐射渐变

    QRadialGradient radialGradient(QPointF(200,190),50,QPointF(275,200));

    radialGradient.setColorAt(0,QColor(255,255,100,150));

    radialGradient.setColorAt(1,QColor(0,0,0,50));

    painter.setBrush(radialGradient);

    painter.drawEllipse(QPointF(200,190),50,50);

    //锥形渐变

    QConicalGradient conicalGradient(QPointF(350,190),60);

    conicalGradient.setColorAt(0.2,Qt::cyan);

    conicalGradient.setColorAt(0.9,Qt::black);

    painter.setBrush(conicalGradient);

    painter.drawEllipse(QPointF(350,190),50,50);

    //画笔使用线性渐变来绘制直线和文字

    painter.setPen(QPen(linearGradient,2));

    painter.drawLine(0,280,100,280);

    painter.drawText(150,280,tr("helloQt"));

    //添加文字

     QFont font1;

     font1.setPixelSize(24); //设置字体像素大小为12

     QString text="hello"; //设置显示的文本

     QFontMetrics metrics(font1);   //获取文字宽度对象

     int w=metrics.width(text); //获取显示文本的宽度

     int h=metrics.height(); //获取显示文本的高度

     painter.setFont(font1);

     painter.setPen(Qt::blue);

     painter.drawText(QRect(this->width()/2-w,this->height()/2-h,w,h),text);

    //绘图打印功能

    QPrinter printer;

    printer.setOutputFormat(QPrinter::PdfFormat); // 设置输出格式为PDF，也可以设置为其他格式

    printer.setOutputFileName("output.pdf"); // 设置输出文件名

    QPainter painter1(&printer);

    painter1.drawText(100, 100, "Hello, PDF1!");

    painter1.end(); // 结束绘制，内容将被发送到打印机

}







QRect::right()和QRect::bottom()的返回值并不是矩形右下角点的真实坐标值：
QRect::right()返回的是 left() + width() – 1；QRect::bottom()则返回 top() + height() – 1。

为避免这个问题，我们建议是使用QRectF。QRectF使用浮点值，而不是整数值，来描述坐标。
这个类的两个函数QRectF::right()和QRectF::bottom()是正确的。
如果你不得不使用QRect，那么可以利用 x() + width() 和 y() + height() 来替代 right() 和 bottom() 函数。




//保存和恢复状态：save()与restore() 
QPainter是一个状态机。那么，有时我想保存下当前的状态：当我临时绘制某些图像时，就可能想这么做。
当然，我们有最原始的办法：将可能改变的状态，比如画笔颜色、粗细等，在临时绘制结束之后再全部恢复。
对此，QPainter提供了内置的函数：save()和restore()。save()就是保存下当前状态；restore()则恢复上一次保存的结果。
这两个函数必须成对出现：QPainter使用栈来保存数据，每一次save()，将当前状态压入栈顶，restore()则弹出栈顶进行恢复。
void PaintDemo::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.fillRect(10, 10, 50, 100, Qt::red);
	painter.save();
	painter.translate(100, 0); // 向右平移 100px
	painter.fillRect(10, 10, 50, 100, Qt::yellow);
	painter.restore();
	painter.save();
	painter.translate(300, 0); // 向右平移 300px
	painter.rotate(30); // 顺时针旋转 30 度
	painter.fillRect(10, 10, 50, 100, Qt::green);
	painter.restore();
	painter.save();
	painter.translate(400, 0); // 向右平移 400px
	painter.scale(2, 3); // 横坐标单位放大 2 倍，纵坐标放大 3 倍
	painter.fillRect(10, 10, 50, 100, Qt::blue);
	painter.restore();
	painter.save();
	painter.translate(600, 0); // 向右平移 600px
	painter.shear(0, 1); // 横向不变，纵向扭曲 1 倍
	painter.fillRect(10, 10, 50, 100, Qt::cyan);
	painter.restore();
}
Qt 提供了四种坐标变换：平移 translate，旋转 rotate，缩放 scale 和扭曲 shear。
在这段代码中，我们首先在(10, 10) 点绘制一个红色的 50×100 矩形。保存当前状态，将坐标系平移到(100, 0)，绘制一个黄色的矩形。
注意，translate()操作平移的是坐标系，不是矩形。因此，我们还是在(10, 10) 点绘制一个 50×100 矩形，现在，它跑到了右侧的位置。
然后恢复先前状态，也就是把坐标系重新设为默认坐标系（相当于进行translate(-100, 0)），再进行下面的操作。
之后也是类似的。由于我们只是保存了默认坐标系的状态，因此我们之后的translate()横坐标值必须增加，否则就会覆盖掉前面的图形。
所有这些操作都是针对坐标系的，因此在绘制时，我们提供的矩形的坐标参数都是不变的。

