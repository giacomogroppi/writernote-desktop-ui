import QtQuick 2.15
import QtQuick.Controls 2.15

Window {
    width: 1024
    height: 680
    minimumHeight: 600
    minimumWidth: height
    visible: true
    title: qsTr("Writernote")

    id: mainRoot

    StackView {
        id: stackViewMain
        anchors.fill: parent
        initialItem: _controller.uiSelected
    }

    function showMain() {
        var newView = Qt.createComponent("qrc:/ui/pageCanvas/MainWindow.qml")
        stackViewMain.push(newView)
    }

    function closeMain() {
        stackViewMain.pop()
        console.log("Call close main")
    }
}
