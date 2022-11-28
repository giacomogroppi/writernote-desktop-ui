import QtQuick 2.0
import QtQuick.Controls 6.3

Rectangle {
    property string backColor: "#00248f"
    property int hAll: 50
    property int wButton: 30

    id: root
    width: parent.width
    height: hAll

    color: backColor

    ButtonToolInstruments {
        id: buttonBack
        buttonImageSource: ":/prefix_1/icon-hide-left.png"
        anchors {
            left: parent.left
        }
        Text {
            text: qsTr("back")
        }
    }

    ButtonToolInstruments {
        id: undoButton
        buttonImageSource: ""
        anchors {
            left: buttonBack.right
        }
        Text {
            text: qsTr("undo")
        }
    }

    Rectangle {
        id: containerCenter
        anchors.centerIn: parent

        height: parent.height
        width: wButton * 5
        color: backColor

        ButtonToolInstruments {
            id: penButton
            buttonImageSource: ":/prefix_1/images/pen_option.png"
            anchors {
                left: parent.left
            }
            Text {
                text: qsTr("1")
            }
        }

        ButtonToolInstruments {
            id: rubberButton
            buttonImageSource: ":/prefix_1/images/rubber_option.png"
            anchors {
                left: penButton.right
            }
            Text {
                text: qsTr("2")
            }
        }

        ButtonToolInstruments {
            id: highlighterButton
            buttonImageSource: ":/prefix_1/images/highlighter_option.png"
            anchors {
                left: rubberButton.right
            }
            Text {
                text: qsTr("3")
            }
        }

        ButtonToolInstruments {
            id: cutButton
            buttonImageSource: ":/prefix_1/images/cut_option.png"
            anchors {
                left: highlighterButton.right
            }
            Text {
                text: qsTr("4")
            }
        }

        ButtonToolInstruments {
            id: handButton
            buttonImageSource: ":/prefix_1/images/cut_option.png"
            anchors {
                left: cutButton.right
            }
            Text {
                text: qsTr("5")
            }
        }
    }

    ButtonToolInstruments {
        id: recordingButton
        buttonImageSource: ":/prefix_1/images/cut_option.png"
        width: wButton
        height: parent.height

        x: parent.width * (3/4)

        Text {
            text: qsTr("rec")
        }
    }

}