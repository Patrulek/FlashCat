import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page_login
    property alias btn_login: btn_login
    property alias tf_email: tf_email
    property alias tf_password: tf_password
    title: qsTr("FlashCat")

    anchors.fill: parent

    Column {
        id: column
        anchors.fill: parent

        Label {
            id: lbl_login
            color: "#397eeb"
            text: "Log in"
            font.bold: false
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            anchors.bottom: tf_email.top
            anchors.left: tf_email.left
            anchors.right: tf_email.right
            anchors.bottomMargin: height
        }

        TextField {
            id: tf_email
            placeholderText: "Email..."
            anchors.bottomMargin: height
            anchors.bottom: tf_password.top
            anchors.left: tf_password.left
            anchors.right: tf_password.right
            width: parent.width / 2
        }

        TextField {
            id: tf_password
            placeholderText: "Password..."
            width: parent.width / 2
            anchors.centerIn: parent
        }

        Button {
            id: btn_login
            text: "Login"
            anchors.topMargin: height
            anchors.top: tf_password.bottom
            anchors.left: tf_password.left
            anchors.right: tf_password.right
        }

        Label {
            id: lbl_register
            color: "#397eeb"
            text: "Register"
            horizontalAlignment: Text.AlignHCenter
            anchors.left: btn_login.left
            anchors.right: btn_login.right
            anchors.top: btn_login.bottom
            anchors.topMargin: height / 2
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
