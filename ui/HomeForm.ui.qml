import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    property alias btn: btn
    property alias btn_accept_add: btn_accept_add
    property alias btn_cancel_add: btn_cancel_add
    property alias popup: popup
    property alias tf_name: tf_name
    property alias lbl_status: lbl_status
    title: qsTr("FlashCat")

    anchors.fill: parent

    Popup {
        id: popup
        modal: true
        focus: true
        anchors.centerIn: parent
        width: parent.width * 0.8
        height: width * 0.4
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        TextField {
            id: tf_name
            anchors.centerIn: parent
            width: parent.width * 0.6
            anchors.verticalCenterOffset: -height
            placeholderText: "tally_name"
        }

        Label {
            id: lbl_status
            text: "Need to provide name"
            horizontalAlignment: Text.AlignHCenter
            color: "#c02323"
            visible: false
            anchors {
                left: tf_name.left
                right: tf_name.right
                top: tf_name.bottom
            }
        }

        Button {
            id: btn_accept_add
            text: "Add"
            anchors.topMargin: tf_name.height / 2
            anchors {
                left: lbl_status.left
                top: lbl_status.bottom
            }
            width: lbl_status.width * 0.4
        }

        Button {
            id: btn_cancel_add
            text: "Cancel"
            anchors.topMargin: tf_name.height / 2
            anchors {
                right: lbl_status.right
                top: lbl_status.bottom
            }
            width: lbl_status.width * 0.4
        }
    }

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
