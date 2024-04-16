/********************/元素/************************************************************/
QML的元素分为可视化元素和非可视化元素，常用的可视化元素如下表所示：

//基本元素
基本元素对象(item)
矩形元素对象(Rectangle)
文本元素(Text)
图像元素(Image)
鼠标区域元素(MouseArea)

//输入元素
文本输入(TextInput)
焦点区域(FocusScope)
文本编辑器(TextEdit)
按键元素(Key)

//布局元素
锚定位(Anchor)

//布局元素
Row(行)
Column(列)
Grid(栅格)
Flow(流)
Repeater(重复元素)


非可视元素（动画元素）
所有在QtQuick中的动画都由同一个计时器来控制，因此他们始终都保持同步，这也提高了动画的性能和显示效果



/********************/一、基本元素/************************************************************/
//颜色属性
color: 单引号 或 双引号 加颜色名或 #十六进制颜色代码 。
这里的颜色名字同SVG 颜色定义一致，具体可以参见https://www.w3.org/TR/css-color-3/#svg-color

//1、Item
Item是所有可视元素中最基本的一个。它是所有其它可视元素的父元素。Item本身没有任何绘制，它的作用是定义所有可视元素的通用属性。
除了定义通用属性，Item另外一个重要作用是作为其它可视元素的容器。从这一点来说，Item非常类似于 HTML 中 div 标签的作用。

//2、Rectangle
Rectangle在 Item的基础之上增加了 border边框、color颜色、gradient渐变色、radius圆角 属性。
Rectangle { 
        width: 100  
        height: 150 
        color: "lightsteelblue" 
        border { 
                color: "#FF0000" 
                width: 4 
        } 
        radius: 8 
}

gradient 属性用于定义使用渐变色填充。例如：
Rectangle { 
        width: 100 
        height: 150 
        gradient: Gradient { 
                GradientStop { position: 0.0; color: "red" } 
                GradientStop { position: 0.33; color: "yellow" } 
                GradientStop { position: 1.0; color: "green" } 
        } 
        border.color: "slategray"
}

gradient 要求一个 Gradient 对象。该对象需要一个 GradientStop 的列表。所谓渐变，就是我们指定在某个位置必须是某种颜色，这期间的过渡色则由计算而得。
GradientStop 对象就是用于这种指定，它需要两个属性：position和 color。前者是一个 0.0 到 1.0 的浮点数，说明 y 轴方向的位置，例如元素的最顶部是 0.0，最底部是 1.0，
介于最顶和最底之间的位置可以用这么一个浮点数表示，也就是一个比例；后者是这个位置的颜色值。例如上面的 GradientStop { position: 0.33; color: “yellow” }说明在从上往下三分之一处是黄色。
需要注意的是，Rectangle 必须同时指定（显式地或隐式地）宽和高，否则的话是不能在屏幕上面显示出来的。这通常是一个常见的错误。


//3、Text
Text 元素最重要的属性当然就是 text 属性。这个属性类型是 string。Text还拥有text、color、font、style、wrapMode等属性，text支持html格式的字符串解析。例如text : "<b>Hello</b> <i>World!</i>"
字体可以通过字体属性组设置（例如 font.family、font.pixelSize 等）。如果要设置文本颜色，只需要设置 color 属性。
Text { 
    text: "The quick brown fox" 
    color: "#303030" 
    font.family: "Century" 
    font.pixelSize: 28 
}

horizontalAlignment 和 verticalAlignment 属性指定对齐方式。
style 和 styleColor。这两个属允许我们指定文本的显示样式和这些样式的颜色以及外框效果，浮雕效果或者凹陷效果。
对于很长的文本，通常我们会选择在文末尾使用 … ，此时我们需要使用 elide 属性，并可以指定 ... 的显示位置。
我们还可以选择通过 wrapMode 属性指定换行模式（这个属性只在明确设置了宽度后才生效）。
Text { 
        width: 160 
        height: 120 
        text: "A very very long text" 
        elide: Text.ElideMiddle 
        style: Text.Sunken 
        styleColor: '#FF4444' 
        verticalAlignment: Text.AlignTop
        font { 
                pixelSize: 24 
        } 
}

这里的 Text 元素的文本省略号位置这一行文本的中部；具有一个 #FF4444 颜色的样式 Sunken。


//4、Image
Image 元素用于显示图像。目前 QML 支持的图像格式有 PNG、 JPG、 GIF 和 BMP 等。
除此之外，我们也可以直接给 source 属性一个 URL 来自动从网络加载图片，也可以通过fillMode 属性设置改变大小的行为。
这里的 URL，可以是本地路径，也可以使网络路径（http://example.org/home.png），此时会自动从这个地址加载对应的资源。这也是 QML 的一大特色：网络透明。
Image { 
        x: 12; 
        y: 12 
        // width: 48 
        // height: 118 
        source: "assets/rocket.png" 
} 

Image { 
        x: 112; 
        y: 12 
        width: 48 
        height: 118/2 
        source: "assets/rocket.png" 
        fillMode: Image.PreserveAspectCrop              //填充模式：等比例切割。此时需要同时设置 clip 属性，避免所要渲染的对象超出元素范围。
        clip: true 
} 


//5、MouseArea
顾名思义，这个元素用于用户交互。这是一个不可见的矩形区域，用于捕获鼠标事件。
通常会将这个元素与一个可视元素结合起来使用，以便这个可视元素能够与用户交互。

可以通过MouseArea，表明需要监视对象的范围，在通过onClicked : {} 来执行想要进行的操作。

MouseArea 是 QtQuick 的重要组成部分，它将可视化展示与用户输入控制解耦。
输入处理与可视化显示分开，这样你的交互区域可以比你显示的区域大很多。

MouseArea{
        anchors.fill: parent 
        onClicked : {
                console.debug("colorRect: ", parent.color)
        }
}


/********************/二、锚布局（anchors）/************************************************************/
QML使用anchors（锚）对元素进行布局。anchoring（锚定）是基础元素对象的基本属性，可以被所有的可视化QML元素使用。

anchors.fill:    parent                                         //元素填充它的父元素。
anchors.left : parent.left                                   //元素左对齐它的父元素。
anchors.left : parent.right                                //元素的左边与它父元素的右边对齐。
id : blue1;   anchors.horizontalCenter: parent.horizontalCenter                 //Blue1与它的父元素水平中间对齐。
id : blue2;   anchors.horizontalCenter: blue1.horizontalCenter                  //Blue2与Blue1中间对齐，并且它的顶部对齐Blue1的底部。
anchors.centerIn : parent                               //元素在它的父元素中居中。
anchors.leftMargin : 20                                  //元素左边距20
//元素水平方向居中对齐父元素并向后偏移12像素，垂直方向居中对齐。
anchors.horizontalCenter : parent.horizontalCenter
anchors.horizontalCenterOffset : -12
anchors.verticalCenter : parent.verticalCenter



/********************/三、定位元素/************************************************************/
有一些QML元素被用于放置元素对象，它们被称作定位器，QtQuick模块提供了Row，Column，Grid，Flow用来作为定位器。
spacing属性用来设置每个元素之间的间隔大小。

1、Column（列）元素将它的子对象通过顶部对齐的列方式进行排列。
2、Row（行）元素将它的子对象从左到右，或者从右到左依次排列，排列方式取决于 layoutDirection 属性。
3、Grid（栅格）元素通过设置 rows（行数）和 columns（列数）将子对象排列在一个栅格中。可以只限制行数或者列数。
如果没有设置它们中的任意一个，栅格元素会自动计算子项目总数来获得配置，例如，设置rows（行数）为3，添加了6个子项目到元素中，那么会自动计算columns（列数）为2。
属性flow（流）与layoutDirection（布局方向）用来控制子元素的加入顺序。
4、Flow（流）。通过flow（流）属性和layoutDirection（布局方向）属性来控制流的方向。它能够从头到底的横向布局，也可以从左到右或者从右到左进行布局。
作为加入流中的子对象，它们在需要时可以被包装成新的行或者列。为了让一个流可以工作，必须指定一个宽度或者高度，可以通过属性直接设定，或者通过anchor（锚定）布局设置。

Column{
        id: column
        anchors.centerIn : parent
        spacing : 8                                             //像素间隔
        RedSquare   {   }
        GreenSquare {   width:  96  }
        BlueSquare  {   }
}

Row{
        id: row
        anchors.centerIn : parent
        spacing : 20
        BlueSquare  {   }
        GreenSquare {   }
        RedSquare   {   }
}

Grid{
        id: grid
        rows : 2
        columns : 2
        anchors.centerIn : parent
        spacing : 8
        RedSquare   {   }
        RedSquare   {   }
        RedSquare   {   }
        RedSquare   {   }
}

Flow{
        anchors.fill:   parent
        anchors.margins : 20
        spacing : 20
        RedSquare   {   }
        BlueSquare  {   }
        GreenSquare {   }
}

5、Repeater（重复元素），通常与定位器一起使用。它的工作方式就像for循环与迭代器的模式一样。在这个最简单的例子中，仅仅提供了一个循环的例子。
Grid{
        anchors.fill:   parent
        anchors.margins : 8
        spacing : 4
        Repeater   {
                model:  16
                Rectangle   {
                        width : 56; height: 56
                        property    int colorIndex : Math.floor(Math.random() * 3)
                        color : root.colorArray[colorIndex]
                        border.color : Qt.lighter(color)
                        Text    {
                                anchors.centerIn:   parent
                                color : "#909090"
                                text : "Cell   " + index
                        }
                }
        }
}



/********************/四、键盘交互/************************************************************/
有些属性可以附加到元素本身，其语法是<Element>.<property> : <value>。 每一个属性都可以发出信号，因而都可以关联信号处理函数。这个处理函数将在属性值变化时调用。
这种值变化的信号槽命名为 on + 属性名 + Changed，其中属性名要首字母大写。例如上面的例子中，height 属性变化时对应的槽函数名字就是 onHeightChanged。
一般情况下，我们处理了某个按键事件时，就会设置其event.accepted属性为true，这样做的目的是防止它的父对象稍后也处理同一个按键事件，即使父对象的focus没有设置为ture。

Keys有三个属性：enabled、forwardTo、prioriry。

enabled属性默认为true，为false时不能响应按键事件，影响的只是当前QML对象。
Keys的enabled不同于Item的enabled，后者默认为true，为false时按键事件和鼠标事件都不能响应，影响的是当前对象及所有孩子对象，这一点在使用是需要特别注意。

forwardTo是个列表属性list<Object>，设置按键事件传递的顺序，某个QML对象在这个列表属性中时，
即使没有设置focus为true也能响应按键事件，如果某个按键事件被列表属性中前面的Item处理了，后面的Item就不会再收到这个按键信号。

priority属性用来设置处理按键事件时的优先级，默认是Keys.BeforeItem，也就是说优先处理Keys附加属性的按键事件，
然后才是Item本身的按键事件，但Keys已经处理过的按键事件就不会再传递到当前Item了，反之Keys.afterItem亦然。


QML 和 JavaScript 关系密切，下面是简单示例：

Text{
        id: label
        x : 24; y: 24
        property int spacePresses : 0                                                        // 自定义属性，表示空格按下的次数  
        text : "Space pressed: " + spacePresses + " times"
        onTextChanged : console.log("text changed to:", text)                // (1) 文本变化的响应函数，使用控制台输出信息 
        focus : true                                                                                    // 接收键盘事件，需要设置 focus 属性 

        Keys.onSpacePressed : {                                                                // (2) 调用 JavaScript 函数
                increment()
        }

        Keys.onEscapePressed : {                                                              // 按下 Esc 键清空文本 
                label.text = ''
        }

        function increment() {                                                                  // (3) 一个 JavaScript 函数 
                spacePresses = spacePresses + 1
        }
}



/********************/五、文本输入/************************************************************/
//1、文本输入
文本输入允许用户输入一行文本。这个元素支持使用正则表达式验证器来限制输入和输入掩码的模式设置。
用户可以通过focus设置初始焦点。为了支持键盘改变焦点，我们可以使用 KeyNavigation（按键向导） 这个附加属性。
TextInput {
        id: input1
        x : 8; y: 8
        width : 96; height: 20
        focus : true                                               //focus：设置输入焦点
        text : "Text Input 1"
        KeyNavigation.tab : input2                      //KeyNavigation：通过按下该按键改变焦点
}
TextInput {
        id: input2
        x : 8; y: 36
        width : 96; height: 20
        text : "Text Input 2"
        KeyNavigation.tab : input1                      //KeyNavigation：通过按下该按键改变焦点
}

一个文本输入元素（text input element） 只显示一个闪烁符和已经输入的文本。
用户需要一些可见的修饰来鉴别这是一个输入元素，例如一个简单的矩形框。
当你放置一个TextInput（文本输入） 在一个元素中时，你需要确保其它的元素能够访问它导出的大多数属性。
提取代码作为组件：
Rectangle{
        width : 96; height: input.height + 8
        color : "lightsteelblue"
        border.color : "gray"
        property alias text : input.text
        property alias input : input
        TextInput {
                id: input
                anchors.fill : parent
                anchors.margins : 4
                focus : true
        }
}
如果想要完整的导出TextInput元素，可以使用property alias input : input来导出这个元素。第一个input是属性名字，第二个input是元素id。

//2、焦点区域（FocusScope）
一个焦点区域（focus scope） 定义了如果焦点区域接收到焦点，
它的最后一个使用focus : true的子元素接收焦点，它将会把焦点传递给最后申请焦点的子元素。
FocusScope{
        width : 96; height: input.height + 8
        Rectangle {
            anchors.fill: parent
            color : "lightsteelblue"
            border.color : "gray"
        }
        property alias text : input.text
        property alias input : input
        TextInput {
            id: input
            anchors.fill : parent
            anchors.margins : 4
            focus : true
        }
}

//3、文本编辑（TextEdit）
文本编辑（TextEdit） 元素与文本输入（TextInput） 非常类似，它支持多行文本编辑。它不再支持文本输入的限制，但是提供了已绘制文本的大小查询
FocusScope{
        width : 96; height: 96
        Rectangle {
            anchors.fill: parent
            color : "lightsteelblue"
            border.color : "gray"
        }
        property alias text : input.text
        property alias input : input
        TextEdit {
            id: input
            anchors.fill : parent
            anchors.margins : 4
            focus : true
        }
}

//4、按键元素 （Key Element）
附加属性key允许你基于某个按键的点击来执行代码。例如使用up，down按键来移动一个方块，left，right按键来旋转一个元素，plus，minus按键来缩放一个元素。
Rectangle{
        Rectangle{
                id: square
                x : 8; y: 8
                width : 48
                height : 48
                color : "#666666"
                border.color : Qt.darker(color)
        }
        focus: true
        Keys.onLeftPressed : square.x -= 8
        Keys.onRightPressed : square.x += 8
        Keys.onUpPressed : square.y -= 8
        Keys.onDownPressed : square.y += 8
        Keys.onPressed : {
                switch (event.key) {
                case Qt.Key_Plus:
                        square.scale += 0.2
                                break;
                case Qt.Key_Minus:
                        square.scale -= 0.2
                                break;
                }
        }
}




