/********************/Button/************************************************************/
`contentItem`来改变按钮的文字和背景颜色，可以通过绑定`contentItem`的属性来实现。
`contentItem`是一个按钮的内部元素，可以访问和修改其属性。

//样式1
Button {
        id: myButton
        anchors.centerIn : parent
        text : "Click Me"
                
        contentItem : Rectangle {
                color: myButton.pressed ? "red" : "blue"
                border.color : "black"
                width : parent.width
                height : parent.height
                        
                Text {
                        anchors.centerIn: parent
                        text : myButton.text
                        color : "white"
                }
        }
}

//样式2
Button{
        id: selfBtn
        text : qsTr("Button")

        contentItem : Text {
                text: selfBtn.text
                font : selfBtn.font
                opacity : enabled ? 1.0 : 0.3
                color : selfBtn.down ? "#17a81a" : "#21be2b"
                horizontalAlignment : Text.AlignHCenter
                verticalAlignment : Text.AlignVCenter
                elide : Text.ElideRight
        }

        background: Rectangle {
                implicitWidth: 100
                implicitHeight : 40
                opacity : enabled ? 1 : 0.3
                border.color : selfBtn.down ? "#17a81a" : "#21be2b"
                border.width : 1
                radius : 2
        }
}

//样式3
Button{
        id: selfBtn
        text : qsTr("Button")
        
        contentItem : Text {
                text: selfBtn.text
                font : selfBtn.font
                opacity : enabled ? 1.0 : 0.3
                color : selfBtn.down ? "white" : "#e6f6e7"
                horizontalAlignment : Text.AlignHCenter
                verticalAlignment : Text.AlignVCenter
                elide : Text.ElideRight
        }
        
        background: Rectangle {
                implicitWidth: 100
                implicitHeight : 40
                opacity : enabled ? 1 : 0.3
                border.color : selfBtn.down ? "#17a81a" : "#21be2b"
                color : selfBtn.down ? "#17a81a" : "#21be2b"
                border.width : 1
                radius : 2
        }
}



//布局与图标
GridLayout{
        columns: 3
        rows : 1
        anchors.fill : parent

        Button{
                text:"Cancel"
                Layout.column : 0                                               //顺序序号
                Layout.alignment : Qt.AlignHCenter
        }

        Button{
                icon.name: "image"
                icon.width : 60
                icon.height : 30
                icon.color : "transparent"
                icon.source : "./cat.jpg"
                Layout.column : 1
                Layout.alignment : Qt.AlignHCenter
        }

        Button{
                text:"email"
                icon.name : "email"
                icon.color : "transparent"
                icon.source : "./walk.gif"

                Layout.column : 2
                Layout.alignment : Qt.AlignHCenter
        }
}

//事件处理
canceled()	        当被按下时，鼠标失去了对按钮的抓取，或者当它发出释放信号，但鼠标光标不在按钮内部时，就会发出这个信号。
clicked()	                当用户通过触摸、鼠标或键盘交互式地单击按钮时，就会发出这个信号。
doubleclick()	        当用户通过触摸或鼠标交互式地双击按钮时，就会发出这个信号。
pressAndHold()	当用户通过触摸或鼠标交互式地按下并按住按钮时，就会发出这个信号。当启用autoRepeat时不会触发。
pressed()	                当用户通过触摸、鼠标或键盘交互式地按下按钮时，就会发出这个信号。
released()	                当用户通过触摸、鼠标或键盘交互地释放按钮时，就会发出这个信号。
toggled()	                当用户通过触摸、鼠标或键盘交互切换可检查按钮时，就会发出这个信号。这个信号在QtQuick中引入。对照组2.2 (Qt 5.9)。

用法：
on + 信号首字母大写: 单个函数
on + 信号首字母大写{ 多条语句函数 }

Button{
        text: "Click Me"
        onClicked : {
                console.log("Button clicked")
        }
}


//其他属性
flat: bool
这个属性指示这个按钮是否是 flat 按钮，平面按钮通常不会绘制背景，除非它被按下或选中。默认值为false。

highlighted: bool
这个属性保存按钮是否高亮显示。按钮可以高亮显示以吸引用户的注意力。这里的高亮就是背景变黑的。它对键盘交互没有影响。默认值为false。



/********************/ListView/************************************************************/

/********************/StackView/************************************************************/
StackView
{
    id: stack
    initialItem : mainView
    anchors.fill : parent
}

Component{
    id: mainView

    Row {
        spacing: 10

        Button {
            text: "一个界面进栈"
            onClicked : stack.push(mainView)
        }
        Button {
            text: "一个界面出栈"
            enabled : stack.depth > 1
            onClicked: stack.pop()

        }
        Text {
            text: "当前界面的栈深度：" + stack.depth
        }
    }
}


/********************/SwipeView/************************************************************/





/********************/页眉与页脚/************************************************************/
header
footer


/********************/TabBar 和 TabButton/************************************************************/

/********************/Window与Page与Item/************************************************************/

/********************/ListModel/************************************************************/

/********************/ComboBox/************************************************************/

/********************/Slider/************************************************************/

/********************/TextField 与 TextInput 与TextEdit/************************************************************/

/********************/Label/************************************************************/


