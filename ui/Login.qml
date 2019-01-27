import QtQuick 2.4
import QtQuick.Controls 2.2

LoginForm {

    btn_login.onClicked: {
        backend.login(tf_email.text, tf_password.text)
    }

    lbl_register_ma.onClicked: {
        lbl_invalid.visible = false
        stackView.push("qrc:/ui/Register.qml")
    }

    Connections  {
        target: backend
        onLoginSuccessChanged: {
            lbl_invalid.visible = !backend.login_success;
            lbl_invalid.text = backend.status_error;

            if( backend.login_success )
                stackView.replace("qrc:/ui/Home.qml")
        }
    }
}
