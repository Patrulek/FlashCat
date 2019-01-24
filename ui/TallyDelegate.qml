import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    id: tallydelegate
    height: 64
    width: parent.width
    Row {
        anchors.fill: parent

        Image {
            id: image
            height: parent.height
            width: parent.height
            source: "qrc:/assets/placeholders/cards.png"
        }

        Column {
            id: column
            width: parent.width - image.width
            height: parent.height

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
}





