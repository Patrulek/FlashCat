import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 480
    height: 720
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            id: col
            width: drawer.width
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            TextField {
                id: search
                width: col.width
                placeholderText: "search..."

            }

            Button {
                id: btn
                text: "Add tally"
                width: col.width
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: search.bottom
                anchors.topMargin: 0
                onClicked: {
                    talls.addTally("New tally")
                }
            }

            ListView {
                id: listView
                clip: true
                width: col.width
                height: drawer.height
                spacing: 16
                cacheBuffer: 64
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: btn.bottom
                anchors.topMargin: 0
                model: talls.model

                Component {
                    id: delegate
                    TallyDelegate {
                    }
                }
                delegate: delegate
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }
}
