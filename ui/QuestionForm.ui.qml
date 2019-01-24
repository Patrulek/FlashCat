import QtQuick 2.4
import QtQuick.Controls 2.2

Page {
    id: page_question
    title: qsTr("FlashCat")
    property alias tf_question: tf_question

    anchors.fill: parent

    Column {
        id: column
        anchors.fill: parent

        Column {
            id: column1
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height / 4
            spacing: 32

            Label {
                id: lbl_question
                color: "#397eeb"
                text: "Question"
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: false
                font.pointSize: 24
                horizontalAlignment: Text.AlignHCenter
            }

            ScrollView {
                width: parent.width / 1.2
                clip: true
                anchors.top: lbl_question.bottom
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: height / 8
                background: Rectangle {
                    color: "#19aae1"
                    opacity: 0.2
                }

                TextArea {
                    id: tf_question
                    placeholderText: "Question..."
                    focus: true
                    selectByMouse: true

                    wrapMode: Text.WordWrap
                }
            }
        }

        Column {
            id: column2
            anchors.bottom: parent.bottom
            anchors.top: column1.bottom
            anchors.topMargin: height / 4
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 32

            Row {
                id: row
                height: lbl_answers.height
                width: parent.width

                Button {
                    id: btn_remove
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: lbl_answers.left
                    anchors.rightMargin: width / 2
                    text: "R"
                    height: 32
                    width: 32
                }

                Label {
                    id: lbl_answers
                    color: "#397eeb"
                    text: "Answers"
                    font.bold: false
                    font.pointSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    anchors.centerIn: parent
                }

                Button {
                    id: btn_add
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: lbl_answers.right
                    anchors.leftMargin: width / 2
                    text: "A"
                    height: 32
                    width: 32
                }
            }

            SwipeView {
                id: swipe
                anchors {
                    top: row.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

                Column {
                    id: column3

                    Label {
                        id: lbl_answer
                        text: "1/1"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: height / 4
                        anchors.top: parent.top
                    }

                    ScrollView {
                        width: parent.width / 1.2
                        clip: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: lbl_answer.bottom
                        anchors.topMargin: height / 8
                        anchors.bottom: row2.top
                        background: Rectangle {
                            color: "#19aae1"
                            opacity: 0.2
                        }

                        TextArea {
                            id: tf_answer
                            wrapMode: Text.WordWrap
                            placeholderText: "Answer..."
                            focus: true
                            clip: true
                            selectByMouse: true
                        }
                    }

                    Row {
                        id: row2
                        height: 64

                        anchors {
                            bottom: parent.bottom
                            left: parent.left
                            right: parent.right
                        }

                        Button {
                            id: btn_text
                            text: "T"
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.horizontalCenterOffset: -width / 1.5
                        }

                        Button {
                            id: btn_img
                            text: "I"
                            anchors.horizontalCenterOffset: width / 1.5
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:720;width:480}
}
 ##^##*/
