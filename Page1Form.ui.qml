import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 480
    height: 720

    title: qsTr("Page 1")

    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }
}
