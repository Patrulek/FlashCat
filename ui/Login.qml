import QtQuick 2.4
import QtQuick.Controls 2.2

LoginForm {

    btn_login.onClicked: {
        backend.login(tf_email.text, tf_password.text)
    }
}
