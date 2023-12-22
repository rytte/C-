/********************/组件/************************************************************/
QML 可以用基本元素组合成一个复杂的元素，方便以后我们的重用。这种组合元素就被称为组件。

有两种方法创建组件。
1.嵌入式创建，在对象中使用 Component{} 定义一个组件，然后使用 Loader{} 来显示。
2.基于文件的组件。
基于文件的组件将 QML 元素放置在一个单独的文件中，文件名首字母必须大写，之后就可以通过这个名字来使用这个组件。
例如，如果有一个文件名为 MyButton.qml，我们就可以在其它 QML 文件中使用 MyButton{ … } 这个组件。


实例：我们要创建一个“ + ” 按钮，在另一个文件中调用它
import QtQuick 2.0
import QtQuick.Controls 2.4

Button{
        y: 10
        width : 24
        height : 24
        text : "+"
}

我们将这个文件命名为 PlusButton.qml，放在 main.qml 同一目录下。
下面我们在 main.qml 中使用这个组件：

import QtQuick 2.0 

Window{
        visible: true
        width : 640
        height : 480

        Text{
                id: mytext
                text : "1"
        }

        PlusButton {
                id: button
                x : 12
                y : 12
                onClicked : {
                        mytext.text = "2"
                }
        }
}


在 main.qml 中，我们直接使用了 MyButton这个组件，就像 QML 其它元素一样。
如果MyButton.qml 与 main.qml 位于不同目录下，如：
| -QML
| |-main.qml
| -components
| -MyButton.qml
那么，我们就需要在 main.qml 的 import 部分增加一行 import .. / components 才能够找到MyButton组件。


