import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    id: tallydelegate
    height: 64
    width: parent.width

    Row {
        id: par_row
        anchors.fill: parent

        Image {
            id: image
            anchors { left: parent.left; top: parent.top; bottom: parent.bottom}
            width: parent.height
            source: "qrc:/assets/placeholders/cards.png"
        }

        Column {
            id: column
            anchors{left: image.right; top:parent.top; bottom:parent.bottom; right:parent.right}

            Text {
                id: tally_name
                text: edit.name
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                id: row
                anchors.left: parent.left
                anchors.leftMargin: 6
                anchors.top: tally_name.bottom
                anchors.topMargin: 16
                width: column.width
                height: column.height / 2
                spacing: 10

                Text {
                    text: edit.size

                }

                Text {
                    text: "New"

                }

                Text {
                    text: "LearnAgain"

                }

                Text {
                    text: "ToRepeat"

                }
            }
        }
    }


    MouseArea {
        id: tallydelegate_ma
        anchors.fill: parent

        onClicked: {
            backend.getTallyCards(talls.model.data(index))
            stackView.push("qrc:/ui/Tally.qml")
        }
    }
}





