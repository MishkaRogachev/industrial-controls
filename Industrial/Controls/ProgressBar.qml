import QtQuick 2.6
import QtQuick.Templates 2.2 as T

T.ProgressBar {
    id: control

    property bool round: false

    implicitWidth: Industrial.baseSize * 4
    implicitHeight: Industrial.baseSize

    background: BackgroundItem {}

    contentItem: Item {
        anchors.fill: parent
        clip: true
        anchors.margins: 1

        Rectangle {
            width: control.visualPosition * (background.width - parent.anchors.margins * 2)
            height: parent.height
            radius: control.round ? Math.min(width, height) / 2 : Industrial.rounding
            color: Industrial.colors.selection
        }
    }

    Hatch {
        anchors.fill: parent
        color: Industrial.colors.raised
        visible: !enabled
        z: 10
    }
}
