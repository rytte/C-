
QPixmap类方法
头文件<QPixmap>
bool QPixmap::loadFromData(const QByteArray& data, const char* format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor)
//导入图片数据，参数一：数据     参数二：数据大小（若不是指针类型则不用填此参数）
QPixmap QPixmap::scaled(int width, int height) const  //设置图片大小，返回修改后的图片对象。例：对象名=对象名.scaled(ui->label->size())
