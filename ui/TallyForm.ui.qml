import QtQuick 2.4
import QtQuick.Controls 2.2

Page {
    id: page_tally
    title: qsTr("FlashCat")

    anchors.fill: parent

    ListView {
        id: lv_cards
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: row.top
        clip: true

        model: ListModel {
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
            ListElement {
            }
        }

        delegate: CardDelegate {
        }
    }

    Row {
        id: row
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 64

        Button {
            id: btn_learn
            anchors.left: parent.left
            text: "L"
            width: parent.height
            height: parent.height
            anchors.leftMargin: width / 4
        }

        Item {
            anchors.left: btn_learn.right
            anchors.right: btn_stats.left
            height: parent.height

            Button {
                id: btn_quiz
                anchors.centerIn: parent
                text: "Q"
                width: parent.height
                height: parent.height
            }
        }

        Button {
            id: btn_stats
            anchors.horizontalCenter: parent.horizontalCenter
            text: "S"
            width: parent.height
            height: parent.height
        }

        Item {
            anchors.left: btn_stats.right
            anchors.right: btn_add.left
            height: parent.height

            Button {
                id: btn_options
                anchors.centerIn: parent
                text: "O"
                width: parent.height
                height: parent.height
            }
        }

        Button {
            id: btn_add
            anchors.right: parent.right
            anchors.rightMargin: width / 4
            text: "A"
            width: parent.height
            height: parent.height
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
