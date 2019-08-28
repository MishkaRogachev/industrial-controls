import QtQuick 2.6
import QtQuick.Layouts 1.3
import Industrial.Controls 1.0
import Industrial.Widgets 1.0

Popup {
    id: root
    width: Theme.baseSize * 8
    closePolicy: Popup.CloseOnPressOutsideParent

    ThemeConfigurator
    {
        id: configurator
        theme: Theme
    }

    ColumnLayout{
        width: parent.width
        spacing: Theme.spacing

        Slider {
            from: 0
            to: 8
            text: qsTr("Rounding")
            value: Theme.rounding
            onMoved: configurator.setRounding(value)
            Layout.fillWidth: true
        }

        Slider {
            from: 16
            to: 60
            stepSize: 4
            text: qsTr("Base size")
            value: Theme.baseSize
            onPressedChanged: if (!pressed) configurator.setBaseSize(value)
            Layout.fillWidth: true
        }
    }
}
