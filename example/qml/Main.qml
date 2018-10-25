import QtQuick 2.6
import QtQuick.Layouts 1.3
import Industrial.Controls 1.0

ApplicationWindow {
    id: main

    visible: true
    title: qsTr("Industrial demo")
    width: theme.baseSize * 24
    height: theme.baseSize * 12

    Loader {
        id: loader
        anchors.fill: parent
        anchors.margins: theme.margins
        source: "Controls.qml"
    }

    Button {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: theme.margins
        iconSource: "qrc:/icons/configure.svg"
        tipText: qsTr("Configure")
        flat: true
        onClicked: popup.visible = !popup.visible

        Popup {
            id: popup
            x: parent.width - width
            y: parent.height
            width: theme.baseSize * 8
            closePolicy: Popup.CloseOnPressOutsideParent

            ColumnLayout{
                width: parent.width
                spacing: theme.spacing

                Label {
                    text: qsTr("Lightness")
                    Layout.alignment: Qt.AlignHCenter
                }

                Slider {
                    from: 50
                    to: 150
                    Binding on value { value: themeConfigurator.lightness }
                    onMoved: themeConfigurator.setLightness(value)
                    Layout.fillWidth: true
                }
            }
        }
    }
}
