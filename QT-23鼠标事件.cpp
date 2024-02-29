/********************/鼠标事件/************************************************************/

#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>

class MyLabel : public QLabel
{
	Q_OBJECT
public:
	explicit MyLabel(QWidget* parent = 0);

protected:
	//重写虚函数
	//鼠标移动事件
	void mouseMoveEvent(QMouseEvent* ev);
	//鼠标按下事件
	void mousePressEvent(QMouseEvent* ev);
	//鼠标释放事件
	void mouseReleaseEvent(QMouseEvent* ev);
	//进入窗口区域
	void enterEvent(QEvent*);
	//离开窗口区域
	void leaveEvent(QEvent*);
signals:

public slots:

};

#endif // MYLABEL_H




#include "mylabel.h"
#include <QMouseEvent>
#include <QLabel>
MyLabel::MyLabel(QWidget* parent) :
	QLabel(parent)
{
	//设置默认追踪鼠标，否则在触发鼠标移动时，必须先点一下才有效
	this->setMouseTracking(true);
}
//重写虚函数
//鼠标移动触发
void MyLabel::mouseMoveEvent(QMouseEvent* ev) {
	int i = ev->x();
	int j = ev->y();
	QString text = QString("<center><h1>Mouse Move：(%1,%2)</h1></center>").arg(i).arg(j);
	// this->setText(text);
}
//鼠标按下触发
void MyLabel::mousePressEvent(QMouseEvent* ev) {
	//代表鼠标左键按下
	if (ev->button() == Qt::LeftButton) {
		int i = ev->x();
		int j = ev->y();
		QString text = QString("<center><h1>Mouse Press：(%1,%2)</h1></center>").arg(i).arg(j);
		this->setText(text);
	}
}
//鼠标释放触发
void MyLabel::mouseReleaseEvent(QMouseEvent* ev) {
	//代表鼠标右键按下
	if (ev->button() == Qt::RightButton) {
		int i = ev->x();
		int j = ev->y();
		QString text = QString("<center><h1>Mouse Release：(%1,%2)</h1></center>").arg(i).arg(j);
		this->setText(text);
	}
}
//进入窗口区域
void MyLabel::enterEvent(QEvent*) {
	QString text = QString("<center><h1>Mouse enter</h1></center>");
	this->setText(text);
}

//离开窗口区域
void MyLabel::leaveEvent(QEvent*) {
	QString text = QString("<center><h1>Mouse leave</h1></center>");
	this->setText(text);
}



