import QtQuick 2.4

RegisterForm {

    btn_register.onClicked: {
        backend.reg(tf_email.text, tf_password.text, tf_firstname.text, tf_lastname.text)
    }

    lbl_login_ma.onClicked: {
        stackView.pop()
    }

    Connections {
        target: backend
        onRegisterSuccessChanged: {
            if(backend.register_success)
                stackView.pop();
        }
    }
}
