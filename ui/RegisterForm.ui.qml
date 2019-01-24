import QtQuick 2.4
import QtQuick.Controls 2.2

Page {
    id: page_register
    title: qsTr("FlashCat")

    anchors.fill: parent

    Column {
        id: column
        anchors.fill: parent

        Label {
            id: lbl_register
            color: "#397eeb"
            text: "Register"
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
            anchors.left: tf_password_confirm.left
            anchors.bottom: tf_password_confirm.top
            anchors.bottomMargin: height
        }

        TextField {
            id: tf_password_confirm
            placeholderText: "Confirm password..."
            width: parent.width / 2
            anchors.centerIn: parent
        }

        TextField {
            id: tf_firstname
            placeholderText: "First name..."
            width: parent.width / 2
            anchors.left: tf_password_confirm.left
            anchors.top: tf_password_confirm.bottom
            anchors.topMargin: height
        }

        TextField {
            id: tf_lastname
            placeholderText: "Last name..."
            width: parent.width / 2
            anchors.left: tf_firstname.left
            anchors.top: tf_firstname.bottom
            anchors.topMargin: height
        }

        Button {
            id: btn_register
            text: "Register"
            anchors.topMargin: height
            anchors.top: tf_lastname.bottom
            anchors.left: tf_lastname.left
            anchors.right: tf_lastname.right
        }

        Label {
            id: lbl_login
            color: "#397eeb"
            text: "Log in"
            horizontalAlignment: Text.AlignHCenter
            anchors.left: btn_register.left
            anchors.right: btn_register.right
            anchors.top: btn_register.bottom
            anchors.topMargin: height / 2
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
