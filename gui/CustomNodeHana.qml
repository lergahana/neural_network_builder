import QtQuick
import QtQuick.Controls.Material 2.3

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava" as Qan

Qan.NodeItem {
    id: roundNode
    width: 40; height: 40
    minimumSize: Qt.size(30,30)

    Rectangle {
        anchors.fill: parent
        radius: width / 2;
        border.width: 1;
        border.color: "black"
        color: Material.accent;
    }

}