import QtQuick 2.6
import QtQuick.Layouts 1.3
import Industrial.Controls 1.0

Rectangle {
    id: root

    property alias opened: popup.visible

    signal colorPicked(color color)

    implicitWidth: Theme.baseSize * 1.5
    implicitHeight: Theme.baseSize * 1.5

    onColorPicked: popup.close()

    Shadow { source: parent }

    MouseArea {
        anchors.fill: parent
        onClicked: opened ? popup.close() : popup.open()
    }

    Popup {
        id: popup
        x: -width
        modal: true
        closePolicy: Popup.CloseOnPressOutsideParent

        onVisibleChanged: if (visible) previewRect.color = root.color

        contentItem: Pane {
            clip: true

            GridLayout {
                columns: 3
                columnSpacing: Theme.spacing
                rowSpacing: Theme.spacing

                Label { text: qsTr("R") }

                Slider {
                    id: rSlider
                    implicitWidth: Theme.baseSize * 5
                    from: 0
                    to: 255
                    onMoved: previewRect.color.r = value / to
                }

                Rectangle {
                    id: previewRect
                    implicitWidth: Theme.baseSize * 3
                    implicitHeight: Theme.baseSize * 3
                    Layout.alignment: Qt.AlignVCenter
                    Layout.rowSpan: 3
                    color: "transparent"
                    onColorChanged: {
                        rSlider.value = color.r * rSlider.to;
                        gSlider.value = color.g * gSlider.to;
                        bSlider.value = color.b * bSlider.to;
                    }

                     Shadow { source: parent }
                }

                Label { text: qsTr("G") }

                Slider {
                    id: gSlider
                    implicitWidth: Theme.baseSize * 5
                    from: 0
                    to: 255
                    onMoved: previewRect.color.g = value / to
                }

                Label { text: qsTr("B") }

                Slider {
                    id: bSlider
                    implicitWidth: Theme.baseSize * 5
                    from: 0
                    to: 255
                    onMoved: previewRect.color.b = value / to
                }

                Button {
                    text: qsTr("Assign")
                    onClicked: {
                        root.color = previewRect.color;
                        root.colorPicked(previewRect.color);
                    }
                    Layout.fillWidth: true
                    Layout.columnSpan: 3
                }
            }
        }
    }
}
