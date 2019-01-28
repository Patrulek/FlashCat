import QtQuick 2.9

HomeForm {
    btn.onClicked: {
        popup.open()
    }

    btn_cancel_add.onClicked: {
        popup.close()
    }

    btn_accept_add.onClicked: {
        if( tf_name.text !== "" ) {
            lbl_status.visible = false
            backend.addTally(tf_name.text)
            popup.close()
        } else {
            lbl_status.visible = true
        }
    }
}
