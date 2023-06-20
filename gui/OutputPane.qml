import QtQuick 2.7
import QtQuick.Controls

Pane {
    id: networkOutput
    objectName: "networkOutput"
    width: 0.4 * parent.width
    height: 0.5 * parent.height
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    visible: false
    Material.elevation: 100
    opacity: 0.8
    Text {
        id: networkOutputText
        objectName: "networkOutputText"
        text: _menu.outputText
        font.pixelSize: 14
        leftPadding: 5
        topPadding: 3
    }
}
