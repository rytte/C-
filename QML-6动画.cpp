/********************/图形动画基础（一）/************************************************************/
QML元素对象通常能够被平移，旋转，缩放。
简单的位移是通过改变x, y坐标来完成的。
旋转是改变rotation（旋转）属性来完成的，这个值使用角度作为单位（0~360）。
缩放是通过改变scale（比例）的属性来完成的，小于1意味着缩小，大于1意味着放大。


一、图形动画基础
1.颜色
有多种表示方式

SVG：“red”
十六进制：#RRGGBB
Qt函数：Qt.rgba(1, 0, 0, 1)
2.渐变（Gradient）
使用渐变开销较大，建议只在静态项目中使用。

二、图片
1.图片
Image{
        id: image
        width : 200; height: 200
        fillMode : Image.Stretch
        //实际保存在内存中图片大小为100 * 100像素，可以提高性能。可以应对加载大图片时，内存过大的问题
        sourceSize.width : 100; sourceSize.height: 100
        source : "http://www.baidu.com/img/baidu_85beaf5496f291521eb75ba38eacbd87.svg"

        //可以获取到图片的进度状态，加载完，正在加载
        onStatusChanged : {
                if (image.status == = Image.Ready)
                        console.log("ready")
                else if (image.status == = Image.Loading)
                        console.log("loading")
        }
        //图片翻转，镜像
        mirror: true
}

2.边界图片
利用图片创建边框，BorderImage会将原图片分成九个区域。四个角不进行缩放，其他区域可以进行缩放或者平铺。

3.动态图片
AnimatedImage类型，用来播放一系列帧的图片动画，如GIF

当前帧：currentFrame
动画总长度：frameCount ，返回帧的总个数
开始：playing
暂停： paused

三、缩放、旋转、平移变换
1.使用属性
scale：缩放，值小于1缩小，值大于1放大，值负数镜像显示，值默认是1正常显示
rotation：顺时针旋转的度数，默认值为0，负值则会逆时针旋转。旋转也是transformOrigin指定中心点

Rectangle{
        width : 100; height: 100
        color : "lightgrey"

        Rectangle {
                width : 25; height: 25
                color : "red"
        }

        Rectangle{
                width : 25; height: 25
                color : "yellow"
                x : 25; y: 25
                //scal: 控制缩放
                scale : 1.8
                transformOrigin : "TopLeft"
                //rotation控制旋转
                //rotation: 90
        }
}

2.高级变换 （Transform）
可以Rotation、Scale、Translate，例如，以Y轴旋转45度

Row{
        x : 10; y : 10; spacing: 10

        Image {
                id: name; source: "cat.jpg"
        }

        Image {
                id: name1; source: "cat.jpg"
                transform : Rotation {
                        //指定原点
                        origin.x: 30; origin.y: 30
                        //代表X轴 Y轴 Z轴，可实现3D效果
                        axis {
                                x : 0; y : 1; z: 0
                        }
                        //旋转角度
                        angle: 45
                }
        }

        //将图片在X轴方向放大2倍，平移使用Translate，提供了x和y属性
        Image{
                x : 20; y : 10; source: "cat.jpg"
                transform : Scale {
                        origin.x: 25; origin.y: 25
                        xScale : 2
                }
        }
}

四、状态改变使用过渡
一个button在按压和释放时，背景颜色进行变换
Rectangle{
        width : 75; height: 75
        id : button
        state : "RELEASED"

        MouseArea {
                anchors.fill: parent
                //按压状态
                onPressed : button.state = "PRESSED"
                //释放状态
                onReleased : button.state = "RELEASED"
        }

        //states属性是一个包含了该项目所有状态的列表
        states: [
                State {
                        name: "PRESSED"
                        PropertyChanges { target: button; color: "lightblue"}
                },
                State {
                        name: "RELEASED"
                        PropertyChanges { target: button; color: "lightsteelblue"}
                }
        ]
        
        //transitions：可以在不同状态间切换时进行过渡动画
        transitions: [
                Transition {
                        from: "PRESSED"
                        to : "RELEASED"
                        ColorAnimation { target: button; duration: 100}
                },
                Transition {
                        from: "RELEASED"
                        to : "PRESSED"
                        ColorAnimation { target: button; duration: 100}
                }
        ]
}

五、使用默认行为动画
每点击一次，矩形的长宽增大50
Rectangle{
        id: rect
        width : 100; height: 100
        color : "red"
        
        //Behavior：当width这个属性变化时，就会应用这个动画
        Behavior on width {
                NumberAnimation { id: anim1; duration: 1000 }
        }
        
        Behavior on height {
                NumberAnimation { id: anim2; duration: 1000 }
        }
        
        MouseArea {
                anchors.fill: parent
                onClicked : {
                        rect.width += 50; rect.height += 50
                }
        }
}

六、并行或顺序动画组
SequentialAnimation可以保证动画组顺序执行，ParallelAnimation并行执行
Rectangle{
        id: rect
        width : 100; height: 100
        color : "red"
        
        SequentialAnimation {
                running: true
                //顺序执行：先变小宽，在变小高。这两个独立动画加入到动画组后，必须作为一个整体，开始或停止
                NumberAnimation { target: rect; property: "width"; to : 30; duration: 1000 }
                NumberAnimation { target: rect; property: "height"; to : 30; duration: 1000 }
        }
}

七、动画师动画
不同于上面的普通动画类型，有几个特殊的动画类型，只不过很类似。如ColorAnimation、ScaleAnimator、ScaleAnimator等。如下图的并行动画，不仅颜色变，缩放也同时变。
ParallelAnimation{
        ColorAnimation {
                target: mixBox
                property : "color"
                from : "forestgreen"
                to : "lightsteelblue";
                duration: 1000
        }
        ScaleAnimator {
                target: mixBox
                from : 2
                to : 1
                duration : 1000
        }
        running: true
}

八、控制动画的执行
1.动画回放
Animation类型包含了start、stop、resume（恢复）、pause（暂停）、resart（重新开始）、complete（完毕）。
需要注意的是stop是从当前位置停下来，complete是将动画执行完毕。

//宽从100增加到500，设置定时器，使其在500毫秒时暂停，此时宽应该增加至300处，实现了动画的暂停
Rectangle{
        width : 100; height: 300
        color : "red"
        NumberAnimation on width{
                id: an
                to : 500; duration: 1000
        }
        
        Timer {
                interval : 500; running: true
                onTriggered : {
                        an.pause()
                }
        }
}

2.缓和曲线
使用它，可以有效简化动画效果的创建过程，如反弹效果、加速、减速、循环动画。QT中有示例，Easing Curves.它包含了几十种效果图，如下图这个，斜率先高后平然后在高。速度在变化。

九、精灵动画
Sprite 精灵引擎是一个随机状态机，如果一张图片包含了多个帧，精灵引擎就可以使用该图片来创建动画。
就像QQ飞车中的休闲区，人物有时站立，有时坐着，有时跑，并且可以控制动作时间比例，以至于人物会一直移动，不会看起来很呆板。

十、拖拽和弹动（Flickable）
通过这个弹动效果类型，可以在规定的区域显示更多的内容。回弹的效果也可以单独设置，可以通过flickableDirection来控制弹动的方向。flickDeceleration可设置弹动速度。
Flickable{
        width : 200; height: 200
        contentWidth : image.width; contentHeight: image.height
        
        Image {
                id: image
                source : "cat.jpg"
        }
}

contentWidth，contentHeight设置可以进行拖拽的大小，也是在Flickable中显示的内容。
Flickable不会自动裁剪它的内容，你可以自己设置clip属性，将其裁剪，不显示设置以外的区域。如下图，只在200, 200的范围内拖拽弹动。

Rectangle{
        width : 360; height: 360
        color : "blue"
        
        Flickable {
                width : 200; height: 200
                contentWidth : image.width; contentHeight: image.height
                clip : true
                
                Image {
                        id: image
                        source : "cat.jpg"
                }
        }
}

十一、翻转效果（Flipable）
通过使用Rotation、State、Transition实现翻转。如下图，设置正面和反面图片，正面图片平铺，点击后，会翻转，再点击，就会初始化为正面。

Flipable{
        id: flipable
        width : 240
        height : 240
        
        property bool flipped : false
        
        front : Image { source: "cat.jpg"; anchors.centerIn: parent }
        back: Image { source: "walk.gif"; anchors.centerIn: parent }
        
        transform: Rotation {
                id: rotation
                origin.x : flipable.width / 2
                origin.y : flipable.height / 2
                //绕Y轴旋转
                axis.x : 0; axis.y: 1; axis.z: 0
                angle : 0    // 默认初始化角度
        }
                
        states: State {
                name: "back"
                PropertyChanges { target: rotation; angle: 180 }
                //属性值变为true后，触发翻转180度
                when: flipable.flipped
        }
        
        transitions: Transition {
                //翻转持续4秒中
                NumberAnimation { target: rotation; property: "angle"; duration: 4000 }
        }

        MouseArea {
                anchors.fill: parent
                //每点一次，flipped属性值变化
                onClicked : flipable.flipped = !flipable.flipped
        }
}

/********************/图形动画基础（二）/************************************************************/
上文的动画比较简单，通过颜色，渐变，平移，旋转，缩放，过渡，翻转实现简单动画。这章学习混合，遮罩，模糊，染色等特效。使用Qt图形效果模块，需要导入一下模块
import QtGraphicalEffects 1.12

一、混合效果
总共两张图，一张覆盖到另一张的上面，类似于混合。通过Blend类型
Item{
        width: 300
        height : 300

        Image {
                id: cat
                source : "cat.jpg"
                sourceSize : Qt.size(parent.width, parent.height)
                smooth : true
                visible : false
        }

        Image {
                id: ball
                source : "ball.gif"
                sourceSize : Qt.size(parent.width, parent.height)
                smooth : true
                visible : false
        }

        Blend {
                anchors.fill: cat
                source : cat
                //需要混合的项目
                foregroundSource : ball
                //定义混合的方式，有22种不同的模式
                mode : "color"
        }
}

二、颜色效果
调整图片的亮度、对比度、着色、饱和度、伽玛调整等
Item{
        width: 300
        height : 300

        Image {
                id: bug
                source : "cat.jpg"
                sourceSize : Qt.size(parent.width, parent.height)
                smooth : true
                visible : false
        }

        BrightnessContrast {
                anchors.fill: bug
                source : bug
                //以下两个属性取值范围都是-1.0到1.0，默认为0
                //亮度，如果值-1将会是一张黑图
                brightness : -0.8
                //对比度
                contrast : 0.5
        }
}

2.颜色叠加
有一张图片，然后给这张图片再添加上一层颜色。

ColorOverlay{
        anchors.fill: bug; source: bug; color: "#80800000"
}

3.着色
与颜色叠加类似，只不过通过单独增减色调、亮度、饱和度来给图片上色。

4.饱和度
Desaturate类型。其属性desaturation控制颜色饱和度的程度，取值0.0到1.0 默认值为0.0，即没有变化。

三、渐变效果 （Gradient）
包含三种渐变类型
锥形渐变（ConicalGradient）
线性渐变（LinearGradient）
辐射渐变（RadialGradient）

四、阴影效果
DropShadow（投影）
InnerShadow（内阴影）

五、模糊效果
FastBlur（快速模糊），模糊质量较低，但渲染速度较快
GaussianBlur（高斯模糊），通过模糊图像算法实现，质量比第一种高，但慢
RecursiveBlur（递归模糊），也使用算法，多次模糊，比上两种更加模糊
MaskBlur（遮罩模糊），可以控制每一个像素进行模糊，相当于可以进行局部模糊

六、动感模糊
上面四种属于发散模糊。但是还可以指定特殊模糊

方向模糊（我们经常看到的抓拍图一辆正在高速行驶的摩托，DirectionalBlur）
径向模糊（相当于旋转模糊，RadiaBlur）
缩放模糊（ZoomBlur）

七、发光效果
发光（Glow）
矩形发光（RectangularGlow）



常用动画：
PropertyAnimation（属性动画） - 使用属性值改变播放的动画
NumberAnimation（数字动画） - 使用数字改变播放的动画
ColorAnimation（颜色动画） - 使用颜色改变播放的动画
RotationAnimation（旋转动画） - 使用旋转改变播放的动画

其他动画：
PauseAnimation（停止动画） - 运行暂停一个动画
SequentialAnimation（顺序动画） - 允许动画有序播放
ParallelAnimation（并行动画） - 允许动画同时播放
AnchorAnimation（锚定动画） - 使用锚定改变播放的动画
ParentAnimation（父元素动画） - 使用父对象改变播放的动画
SmotthedAnimation（平滑动画） - 跟踪一个平滑值播放的动画
SpringAnimation（弹簧动画） - 跟踪一个弹簧变换的值播放的动画
PathAnimation（路径动画） - 跟踪一个元素对象的路径的动画
Vector3dAnimation（3D容器动画） - 使用QVector3d值改变播放的动画

动画元素：
PropertyAction（属性动作） - 在播放动画时改变属性
ScriptAction（脚本动作） - 在播放动画时运行脚本

每一个动画都有start()，stop()，resume()，restart()函数。

Rectangle {
        id: root
        width: 150
        height: 400
    //自定义属性 property <type> <name>:<value>
        property color black: '#1f1f21'
        property color red: '#fc3d39'
        property color green: '#53d769'
        property color yellow: '#ffff37'

    //颜色渐变
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#2ed5fa" }
            GradientStop { position: 1.0; color: "#2467ec" }
        }



        Rectangle {
            id: light1
            x: 25; y: 15
            width: 100; height: width
            radius: width/2
            color: root.black
            border.color: Qt.lighter(color, 1.1)
        }

        Rectangle {
            id: light2
            x: 25; y: 135
            width: 100; height: width
            radius: width/2
            color: root.black
            border.color: Qt.lighter(color, 1.1)
        }
        Rectangle {
            id: light3
            x: 25; y: 255
            width: 100; height: width
            radius: width/2
            color: root.black
            border.color: Qt.lighter(color, 1.1)
        }


        // 默认状态为“stop”
        state: "stop"

        states: [
            State {
                name: "stop"
                PropertyChanges { target: light1; color: root.red }
                PropertyChanges { target: light2; color: root.black }
            },
            State {
                name: "go"
                PropertyChanges { target: light1; color: root.black }
                PropertyChanges { target: light2; color: root.green }
            },
            State {
                name: "wait"
                PropertyChanges { target: light1; color: root.black }
                PropertyChanges { target: light2; color: root.black }
                PropertyChanges { target: light3; color: root.yellow }
            }
        ]
    //注意：在一个状态中，只需要描述属性如何从它们的默认状态改变（而不是前一个状态的改变）

        // 设置鼠标区域为全局
        MouseArea {
            anchors.fill: parent
            onClicked: {
                    if(parent.state == "stop")
                    parent.state = "wait";
                    else if(parent.state == "wait")
                    parent.state = "go";
                    else
                    parent.state = "stop"
                    }
        }


        // 添加过渡
        transitions: [
            Transition {
                from: "stop"; to: "go"
    //            from: "*"; to: "*"
                ColorAnimation { target: light1; properties: "color"; duration: 2000 }
                ColorAnimation { target: light2; properties: "color"; duration: 2000 }
            },
            Transition {
                from: "wait"; to: "go"
                ColorAnimation { target: light2; properties: "color"; duration: 2000 }
                ColorAnimation { target: light3; properties: "color"; duration: 2000 }
            }
        ]
}






