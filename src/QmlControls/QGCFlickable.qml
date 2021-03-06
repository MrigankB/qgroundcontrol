import QtQuick 2.5

import QGroundControl.Palette 1.0

/// QGC version of Flickable control that shows horizontal/vertial scroll indicators
Flickable {
    id:             root
    boundsBehavior: Flickable.StopAtBounds
    clip:           true

    property color indicatorColor: qgcPal.text

    QGCPalette { id: qgcPal; colorGroupEnabled: enabled }

    Component.onCompleted: {
        var indicatorComponent = Qt.createComponent("QGCFlickableVerticalIndicator.qml")
        indicatorComponent.createObject(root)
        indicatorComponent = Qt.createComponent("QGCFlickableHorizontalIndicator.qml")
        indicatorComponent.createObject(root)
    }
}
