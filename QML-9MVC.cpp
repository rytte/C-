//********************//main.qml
import QtQuick 2.12
import QtQuick.Window 2.12

Window{
        width: 640
        height : 480
        visible : true
        title : qsTr("Hello World")

        Item {
                MyModel {
                        id: model
                }

                MyView {
                        //MyModel: model
                }

                MyController {
                        onClicked: model.increment()
                }
        }
}


//********************//MyModel.qml
import QtQuick 2.12

Item{
        property int data : 0

        function increment() {
                data++
        }
}


//********************//MyView.qml
import QtQuick 2.12

Rectangle{
        width: 200
        height : 200
        color : "#999999"

        Text {
                anchors.centerIn: parent
                text : model.data
                font.pixelSize : 24
        }

        MouseArea {
                anchors.fill: parent
                onClicked : model.increment()
        }
}


//********************//MyController.qml
import QtQuick 2.12

Item{
        signal clicked()

        function handleClick() {
                clicked()
        }
}

