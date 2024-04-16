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

