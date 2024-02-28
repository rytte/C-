

QPicture, QImage, QBitmap, 和 QPixmap 是 Qt 框架中用于图像处理和显示的四个重要类。每个类都有其特定的用途和特性。

QImage :
*QImage 是一个在内存中存储图像数据的类。它可以包含任意类型的图像数据，包括彩色、灰度、单色等。
* QImage 主要用于图像处理和分析。你可以使用它来加载、保存、转换、裁剪、旋转、缩放等图像。
* QImage 支持多种图像格式，如 PNG、JPG、BMP 等。
* 它不直接用于屏幕显示，但可以作为 QPixmap 的数据源。

QPixmap :
*QPixmap 是用于在屏幕上显示图像的类。与 QImage 不同，QPixmap 是在屏幕设备的内存中存储的，这意味着它更适合于屏幕显示。
* QPixmap 支持图像缓存，这意味着相同的图像只需要加载一次，即使它在屏幕上多次显示。
* QPixmap 主要用于 GUI 编程，特别是在绘制窗口、控件和图像时。
* QPixmap 可以从 QImage 创建，但一旦创建，它就不能再转换为 QImage。

QBitmap :
*QBitmap 是 QPixmap 的一个子类，专门用于处理位图图像。
* 位图图像通常用于简单的图形和图标，它们只包含黑色和白色（或单色）的像素。
* 由于位图图像相对简单，它们通常比彩色图像更快地加载和显示。
* QBitmap 主要用于创建简单的 GUI 元素，如按钮、复选框等。

QPicture :
*QPicture 是一个用于存储绘图命令的类。它不像 QImage 或 QPixmap 那样存储像素数据，而是存储了创建图像所需的所有绘图命令。
* QPicture 允许你保存绘图的状态，并在以后的时间点重新播放这些命令以重建图像。
* QPicture 主要用于创建复杂的绘图，这些绘图可能由多个步骤和图层组成。
* 你可以使用 QPainter 在 QPicture 上绘制，然后使用 QPixmap 或 QPainter 将其显示在屏幕上。

总的来说，这四个类提供了 Qt 中图像处理和显示的完整功能。QImage 和 QPixmap 是最常用的类，而 QBitmap 和 QPicture 则提供了更专业的功能，用于特定的应用场景。




QPixmap：用于在屏幕上显示图像。
QImage：用于在内存中处理图像，支持多种图像格式。
QBitmap：用于处理位图图像（单色图像）。
QPicture：用于记录绘图命令，可以重复播放以重建图像。





QPixmap类方法
头文件<QPixmap>
bool QPixmap::loadFromData(const QByteArray& data, const char* format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor)
//导入图片数据，参数一：数据     参数二：数据大小（若不是指针类型则不用填此参数）
QPixmap QPixmap::scaled(int width, int height) const  //设置图片大小，返回修改后的图片对象。例：对象名=对象名.scaled(ui->label->size())
