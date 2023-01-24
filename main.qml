import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    width: 1024
    height: 680
    minimumHeight: 600
    minimumWidth: height
    visible: true
    title: qsTr("Writernote")


    Rectangle {
        anchors.fill: parent
        Text {
            text : "ciao"

        }
    }

    StackView {
        id: stackViewMain
        anchors.fill: parent
        initialItem: "qrc:/ui/pageCanvas/MainWindow.qml"
    }
}
