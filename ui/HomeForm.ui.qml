import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    property alias btn: btn
    title: qsTr("FlashCat")

    anchors.fill: parent

    Column {
        id: column
        anchors.fill: parent

        Button {
            id: btn
            text: "Add tally"
            width: parent.width
            height: 32
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }

        ListView {
            id: listView
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            anchors {
                bottom: btn.top
                top: parent.top
                left: parent.left
                right: parent.right
            }
            spacing: 16
            cacheBuffer: 64
            model: talls.model
            delegate: TallyDelegate {
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
