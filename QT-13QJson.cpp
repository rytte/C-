/********************/QJSON/************************************************************/
#include <QJsonDocument>
static QJsonDocument QJsonDocument::fromJson(const QByteArray& json, QJsonParseError* error = nullptr)
					//用于检查数据是否符合json格式	  参数一：传入数据		参数二：错误管理类对象
QJsonObject object()const		//将json数据转换成json对象返回。
QByteArray toJson()const		//把文本内容转换成字符串返回。


#include <QJsonObject>
QJsonValue value(const QString& key) const			//通过键查找json值返回。
QJsonObject::iterator 	insert(const QString& key, const QJsonValue& value)		//加入一组键值对

#include <QJsonValue>
QJsonObject toObject() const						//转换为json对象返回
QString toString() const							//转换为字符串
QJsonArray toArray() const							//转换为json数组

#include <QJsonArray>
QJonValue at(int i)const							//下标索引对应元素
int count()const									//获取数组的成员数
void insert(int i, const QJsonValue& value)			//在下标i的位置插入元素


/************************************************************/
//实例
QByteArray arr = reply->readAll();

QJsonDocument doc;						//创建Json文本类对象

QJsonParseError err;					//创建Json错误管理结构体

doc = QJsonDocument::fromJson(arr, &err);		//向文本对象中导入数据,需要赋值
if (err.error != QJsonParseError::NoError)		//判断数据是否符合json格式
{
    ui->textBrowser->setText("json数据不匹配");
    return;
}

//具体解析转换的格式，必须与你所直到的格式是相同的
//在Json数据匹配的情况下，开始解析。先文本转换成Json对象
QJsonObject obj = doc.object();

//已知键值"time",获取它所在的对组
QJsonValue time_value = obj.value("time");
ui->textBrowser->append(time_value.toString());


//已知键值"cityInfo"对应的是多个对组，那么实值应该是一个Json对象
QJsonValue cityInfo_value = obj.value("cityInfo");			//先拿到实值
QJsonObject cityInfo_obj = cityInfo_value.toObject();		//把实值转换成一个对象
QJsonValue  city_value = cityInfo_obj.value("city");		//再在对象中通过键值获取数值
ui->textBrowser->append(city_value.toString());

//QJsonValue  parent_value = cityInfo_obj.value("parent");
ui->textBrowser->append(cityInfo_obj.value("parent").toString());

//已知data键值下有forecast键值，再往下是一个数组，每个数组又是一个对象

//拿到data键值下的对象
QJsonObject data_obj = obj.value("data").toObject();
//再拿到forecast键值下的数组
QJsonArray  forecast_arr = data_obj.value("forecast").toArray();

//遍历数组
int i;
QJsonObject  temp;
QString high, low;
//====for循环====
//    for(i = 0; i < forecast_arr.count(); i++)
//    {
//        temp = forecast_arr.at(i).toObject();

//        high = temp.value("high").toString();
//        low  = temp.value("low").toString();

//        ui->textBrowser->append(high + low);
//    }

//=====迭代器====
for (QJsonArray::const_iterator it = forecast_arr.begin(); it != forecast_arr.end(); it++)
{
    temp = it->toObject();

    high = temp.value("high").toString();
    low = temp.value("low").toString();

    ui->textBrowser->append(high + low);
}







