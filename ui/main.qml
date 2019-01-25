import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 480
    height: 720

    header: ToolBar {
            id: toolbar

            ToolButton {
                id: toolButton
                text: stackView.depth > 1 ? "\u25C0" : "\u2630"
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    } else {
                        nav_drawer.open()
                    }
                }
            }

            ToolButton {
                id: toolButton2
                icon.source: "qrc:/assets/placeholders/options.png"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                anchors.right: parent.right
                anchors.rightMargin: 0
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    } else {
                        opt_drawer.open()
                    }
                }
            }

            Label {
                text: stackView.currentItem.title
                anchors.centerIn: parent
            }
        }

    Drawer {
        id: nav_drawer
        width: window.width * 0.66
        height: window.height

        Column {
            id: col
            height: parent.height
            width: parent.width
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            TextField {
                id: search
                width: col.width
                height: 64
                placeholderText: "search..."
            }

            ListView {
                id: lv_tallies
                clip: true
                width: parent.width
                height: parent.height - search.height
                anchors.top: search.bottom
                anchors.topMargin: 0

                spacing: 16
                cacheBuffer: 64
                model: talls.model

                delegate: TallyDelegate {}
            }
        }
    }

    Drawer {
        id: opt_drawer
        width: window.width * 0.66
        height: window.height
        edge: Qt.RightEdge
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Login{}
    }
}
