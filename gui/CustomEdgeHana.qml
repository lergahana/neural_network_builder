import QtQuick                      2.7
import QtQuick.Controls.Material    2.1

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava"   as Qan

Qan.EdgeItem {
    id: edgeItem
    property color  color: Qt.rgba(0,0,0,1)
    Qan.EdgeTemplate {
        anchors.fill: parent
        edgeItem: parent
        color: Material.foreground          // HERE
    }
}
