import QtQuick 2.12							//导入模块，模块包含各种qml类型。也可以是一个 JavaScript 文件或者另外的 QML 文件
import QtQuick.Window 2.12						//QtQuick.Window模块，Window类型可以创建一个顶级窗口，所以一般作为根对象

Window{                                                                         //对象实例化
        width: 640                                                              
        height : 480
        visible : true
        title : qsTr("Hello World")

        Text{
                id: name                                                        //对象id
                text : qsTr("你好，世界！")
                color : "red"                                                   //设置文字颜色
                anchors.centerIn : parent                              //anchors：锚点，即该对象的操作句柄

                Rectangle {
                        id: colorRect
                        width : 20 * 2
                        height : width
                        radius : 20
                        color : "green"                                         //设置区域颜色

                        anchors.left : name.right                                                               //在name对象的右边
                        anchors.leftMargin : 10                                                                 //绿色圆形左侧的边距为10
                        anchors.verticalCenter : name.verticalCenter                                //name对象的垂直中心

                        MouseArea {
                                anchors.fill: parent                                                                 //MouseArea填充整个父对象(绿色圆形)
                                onClicked : {
                                        console.debug("colorRect: ", parent.color)                    //绿色圆形点击后，输出控制台
                                }
                        }
                }
        }

        Text {
                id: thisLabel                                                                   // (1) 标识符
                x : 24; y: 16                                                                    // (2) x、y 坐标
                height : 2 * width                                                          // (3) 绑定：会自动更新值
                property int times : 24                                                  // (4) 自定义属性
                property alias anotherTimes : times                             // (5) 属性别名
                text : "Greetings " + times                                            // (6) 文本和值
                font.family : "Ubuntu"                                                   // (7) 字体属性组，等价于font { family: "Ubuntu"; pixelSize: 24 }
                font.pixelSize : 24
                KeyNavigation.tab : otherLabel                                    // (8) 附加属性 KeyNavigation
                onHeightChanged : console.log('height:', height)       // (9) 属性值改变的信号处理回调
                focus : true                                                                    // 接收键盘事件需要设置 focus
                color : focus ? "red" : "black"                                        // 根据 focus 值改变颜色
        }
}



/********************/类型与对象/************************************************************/
有以下三种类型
（1）基本类型
（2）QML 对象类型
Window 和 Text 都是对象类型：
* Item：是所有可视化类型的基类型，叫做根对象或者根项目。常用于对项目进行分组。其有一个堆叠属性z，默认值为0，值越大，就是在最上面绘制。如果子对象z属性是负数，则会绘制在父对象的下面。
* Component对象类型，内部只能包含一个根对象，根对象也不会直接显示，在需要时才会加载，这个类型一般用于为视图提供图形组件
（3）JavaScript 类型

注释：注释方法与C++相同

对象类型后面添加{} 表示实例化，就被称为对象。对象包含好多个特性，如id、属性、信号、信号处理器、方法、附加属性和附加信号处理器、子对象。


//调试输出
将需要的信息输出到控制台。注意需要将console写在函数里面或者信号处理器里面。
console.log、console.debug、console.info、console.warn、console.error
console.log("one ", "two ", three, " four")


/********************/一、ID/************************************************************/
id：可以通过id值在其他对象中引用该对象，id 值必须使用小写字母或者下划线开头，并且不能使用字母、数字和下划线以外的字符，其值在一个组件的作用域中必须是唯一的。
id 应该在 QML 文档中是唯一的。实际上，QML 提供了一种动态作用域（dynamic - scoping）的机制，后加载的文档会覆盖掉前面加载的文档的相同 id。
id 不是一个属性。例如上文代码中Text 对象的 id 为 name，所以可以在其他对象中通过 name.text 来获取 Text 对象中的 text 属性的值， 但无法通过name.id 来获取 id 的值。



/********************/二、属性/************************************************************/
属性（property）： 属性可以是一个静态值或者是一个动态表达式。可以自定义属性，int 类型的属性会自动转换成字符串。在值变化时，绑定依然成立。
//几何属性
x : 100                               //横坐标
y : 100                               //纵坐标
z : 1                                  //堆叠等级
width : 200                       //宽度
height : 200                      //高度

//布局操作
Margin : 10                      //边距
anchor（包含left、right、top、bottom、centerIn、verticalCenter、horizontalCenter等位置属性）   //锚点

//按键操作
Keys                                //附加按键
KeyNavigation                //按键定位
focus : true                     //本对象设置为输入焦点

//转换
scale\rotate                    //缩放和选择
transformorigin              //旋转基点
transform                       //通用x.y.z属性列表转换

//可视化
visible: true                    //是否可见
opacity : 0.5                  //透明度，会被继承。使用color:"#50000000"不会被继承
clip : true                       //子项超出父项范围后自动裁剪
smooth : true                //抗锯齿

//状态定义
state : "stop"                 //states列表对象中的默认一个
states : [                        //自定义状态对象列表
        State{
                name: "stop"
                PropertyChanges { target: light1; color: root.red }
                PropertyChanges { target: light2; color: root.black }
        },
        State{
            name: "go"
            PropertyChanges { target: light1; color: root.black }
            PropertyChanges { target: light2; color: root.green }
        }
]

//自定义属性
property int someNumber                                    //定义整型属性
property var someNumber : 1.5                            //var可以当做任意属性类型，是一种通用的占用符
property var someBool : true                                //使用var定义布尔型属性
property var someList : [1, 2, "three"]                   //使用var定义数组型属性
property Rectangle someRectangle                      //对象类型作为属性类型
readonly property var someNumber : 1.5             //readonly只读属性，必须初始化，不允许为默认属性，不允许有别名

property list <Rectangle> myRect                        //对象列表属性；只声明，不初始化
property list <Rectangle> myRect: [                     //声明并初始化
        Rectangle{ color: "red" },
        Rectangle{ color: "blue" },
]

property alias color : otherObject.color                //属性别名，可以与现有属性同名，但是会被覆盖。作用：子对象设置属性别名后，组件使用者可以在外部使用，从而解决了子对象的封装问题，又将有用的属性暴露出来。
color : "red"

//default属性
Text{
        default property var defaultText
        text : "Hello, " + defaultText.text
}
*一个对象有且只有一个default属性
*在对象中定义一个不是属性的对象时，会把该对象赋值给默认属性。

//属性别名
property alias myLabel : label
myLabel.text : "error" // 错误！此时组件还没有初始化
property  alias myLabelText : myLabel.text  // 错误！不能为属性别名的属性创建别名



/********************/三、信号和信号处理器特性/************************************************************/
信号定义：//小括号可以省略
        signal hovered()
        signal actionPer(string action, var actionResult)


信号处理器：  对应信号发射时，信号处理器会被QML引擎自动调用
QML中使用on + 信号的方式作为信号处理器，来处理所所发送的信号。比如相应按钮的点击事件，代码如下：
Button{
        text: '退出'
        anchors.centerIn : parent
        onClicked : {
                Qt.quit()
        }
}



/********************/四、方法特性 function/************************************************************/
自定义函数：function + 函数名 (参数列表)，并可以 return 一个返回值
Rectangle{
        id: rect
        function calculateHeight() {
                console.log("进入函数")
                return rect.width / 2
        }
        width : 200; height: calculateHeight() 
}



/********************/五、附加属性和附加信号处理器/************************************************************/
附加属性，即非item中继承来的额外属性。在QML中默认提供了常用的Keys、Component等附加属性
例如ListView类型包含一个附加属性ListView.isCurrentItem，可以附加到ListView的每一个委托对象。
delegate 关键字通过定义其修饰的子控件而控制所有子控件的规格。

ListView{
        model : 3;
        delegate: Rectangle {
                id: delegateItem
                width : 100; height: 100
                color : ListView.isCurrentItem ? "red" : "yellow"
        
                Rectangle {
                        id: rect
                        width : 100; height: 100
                        //附加属性只是附加到了根委托对象，而不使委托对象的子对象，所以可以用根委托对象去访问
                        //color: ListView.isCurrentItem ? "red" : "yellow"   错误
                        color : delegateItem.ListView.isCurrentItem ? "red" : "yellow" //正确
                }
        }
}
附加信号处理器，即额外定义的机制。例如，Component，用于在组件创建完成时，执行一些JS代码
Component.onCompleted: {
        console.log("构建完成")
}



/********************/六、枚举/************************************************************/
Rectangle{
        width: 50
        height: 5
        enum Fruit {
                Apple = 5,
                Banana,
                Orange
        }
        
        Component.onCompleted: {
                console.log(TestEnum.Fruit.Apple)
                console.log(TestEnum.Fruit.Banana)
                console.log(TestEnum.Fruit.Orange)
        }
}

外部qml文件调用枚举量
Item {
        property int orange: TestEnum.Fruit.Orange
        Component.onCompleted: {
                console.log("orange", orange)
                console.log(TestEnum.Fruit.Apple)
                console.log(TestEnum.Fruit.Banana)
                console.log(TestEnum.Fruit.Orange)
        }
}

