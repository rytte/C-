/********************/布局管理器/************************************************************/
使用布局管理器后相关控件的geometry失效，只能通过策略模式来适应布局管理器。


1、水平布局管理器 QHBoxLayout		头文件 < QHBoxLayout>
2、垂直布局管理器 QVBoxLayout		头文件 < QVBoxLayout>
3、栅栏布局管理器 QGridLayout		头文件 < QGridLayout>
4、弹簧spacer						头文件 < QSpacerItem>

优先级：minimumSize / maximumSize > 弹簧spacer > 策略模式sizepolicy


布局管理器对象成员：
addWidget(控件对象)						//添加控件
addSpacerItem(弹簧对象)					//添加弹簧

//实例：
QSpacerItem * p = new QSpacerItem(40, 40, Expanding, Expanding);			//创建弹簧指针，构造函数传参
QHBoxLayout* hbox = new QHBoxLayout[2];
hbox[0]->addSpacerItem(p);								//向水平布局管理器中添加弹簧对象
hbox[0]->addWidget(&bt1);							//向水平布局管理器中添加控件对象
hbox[0]->addSpacerItem(p);
hbox[0]->addWidget(&bt2);
hbox[0]->addSpacerItem(p);
hbox[1]->addSpacerItem(p);
hbox[1]->addWidget(&bt3);
hbox[1]->addSpacerItem(p);
hbox[1]->addWidget(&bt4);
hbox[1]->addSpacerItem(p);
QVBoxLayout* vbox = new QVBoxLayout;
vbox->addLayout(&hbox[0]);							//将水平布局管理器添加到垂直布局管理器中
vbox->addLayout(&hbox[1]);
ui->centralwidget->setLayout(&vbox);				//将垂直布局管理器加入到当前窗口


void setSizePolicy(水平策略, 垂直策略)				//控件的策略模式设置方法
void setMaximumSize(最大长度，最大宽度)				//设置最大尺寸
void setMinimumSize(最小长度，最小宽度)				//设置最小尺寸


//栅栏布局管理器实例：
G = new QGridLayout;                    //创建栅栏布局管理器

for (int x = 0; x < 4; x++)             //加入到栅栏布局管理器中
{
        for (int y = 0; y < 4; y++)
        {
                G->addWidget(&bt[4 * y + x], y, x);
                bt[4 * y + x].setText(QString("%1").arg(4 * y + x));                            //设置按钮文本

                bt[4 * y + x].setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);        //设置按钮的策略模式
                bt[4 * y + x].setMaximumSize(100, 100);

                QFont f;                                //把文字字体设置
                f.setPointSize(16);
                bt[4 * y + x].setFont(f);

                connect(&bt[4 * y + x], &QPushButton::clicked, this, &MainWindow::myshow);      //设置关联的槽函数
        }
        ui->centralWidget->setLayout(G);            //把布局管理器加入到窗口
}

void MainWindow::myshow()                       //打印按钮对应的数字
{
        QPushButton* ptr = dynamic_cast<QPushButton*>(sender());        //获取信号发送对象的指针
        qDebug() << ptr->text();
}


