/********************/列表/************************************************************/
//QListView类
头文件<QListView>
virtual void setModel(QAbstractItemModel* model);		//在QListView列表中添加模型，模型的基类是QAbstractItemModel。

QAbstractItemModel是 QAbstractListModel, QAbstractProxyModel, QAbstractTableModel 这三个类的基类
QAbstractListModel 是 QStringListModel 的基类
所以向QListView添加模型时，可以添加 QStringListModel 的对象。这个对象保存的是 QStringList 字符串链表的对象。

void QStringListModel::setStringList(const QStringList& strings)	//向QListView列表中添加字符串列表


//QListWidget类
头文件<QListWidget>
void addItem(const QString& label)				//添加字符串
void addItem(QListWidgetItem* item)				//添加另一对象
void addItems(const QStringList& labels)		//添加字符串列表

实例：添加按钮到窗口中
QPushButton* bt = new QPushButton("按钮")		//创建新按钮
QListWidgetItem * item = new QListWidgetItem()	//创建一个模型
ui->listWidget->addItem(item)					//把模型加入到窗口中
ui->listWidget->setItemWidget(item, bt) 		//把按钮放入到窗口中

实例：添加新窗口到窗口中
form * ptr = new form							//创建自定义窗口
QListWidgetItem * item = new QListWidgetItem()	//创建一个模型
ui->listWidget->addItem(item)					//把模型放入窗口
item->setSizeHint(ptr->sizeHint())  			//把模型设置为和窗口一样的大小
ui->listWidget->setItemWidget(item, ptr)		//把按钮加入到窗口中