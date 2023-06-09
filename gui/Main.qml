import QtQuick
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts
import QtQuick.Shapes
import QtQml.Models

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava"   as Qan

Window {
    id: window
    width: 1000
    height: 700
    visible: true
    title: qsTr("Neural network builder")

    Material.theme: Material.Light
    Material.accent: Material.color(Material.Purple)

    required property MenuObject _menu
    property var nodes: []

    RowLayout {
        width: window.width
        height: window.height

        Rectangle {
            id: menu
            width: 0.3*parent.width
            height: parent.height

            ScrollView{
                anchors.fill: parent

                Column {
                id: column
                anchors.fill: parent
                padding: 20

                    Text {
                        id: layersText
                        text: "Select number of hidden layers"
                        font.pixelSize: 14
                    }

                    SpinBox {
                        id: layers
                        width: layersText.width
                        height: 36
                        topPadding: 2

                        from: 1
                        to: 10
                        stepSize: 1

                        value: 1
                        onValueChanged: {
                            _menu.setLayers(value);
                            for (var i = 0; i < value; i++){
                                if(_menu.neurons[i] === 0){
                                   _menu.setLayerNeurons(i, 1);
                                   _menu.setLayerFunction(i, 1);
                                }
                            }
                            neuronsRepeater.model = value;
                            actfuncRepeater.model = value;
                            drawNN();
                        }
                    }

                    Repeater {
                        id: neuronsRepeater
                        model: 1

                        Column {
                            Text {
                                text: "Select number of neurons in layer " + (index+1)
                                font.pixelSize: 14
                                topPadding: 15
                            }

                            SpinBox {
                                id: numNeurons
                                width: layersText.width
                                height: 36
                                topPadding: 2

                                from: 1
                                to: 10
                                stepSize: 1

                                value: _menu.neurons[index]
                                onValueChanged: {
                                    _menu.setLayerNeurons(index, value);
                                    drawNN();
                                }
                            }
                        }
                    }

                    Repeater {
                        id: actfuncRepeater
                        model: 1

                        Column {
                            id: radioButtons
                            Text {
                                text: "Select activation function for layer " + (index+1)
                                font.pixelSize:  14
                                topPadding: 15
                            }
                            RadioButton {
                                text: "sigmoid"
                                checked: true
                                onClicked: _menu.setLayerFunction(index, 1);
                            }

                            RadioButton {
                                text: "relu"
                                topPadding: 2
                                onClicked: _menu.setLayerFunction(index, 2);
                            }

                            RadioButton {
                                text: "tanh"
                                topPadding: 2
                                onClicked: _menu.setLayerFunction(index, 3);
                            }
                        }
                    }

                    Button {
                        text: "Start training"
                        onClicked: {
                            menu.visible = false
                            network.width = window.width
                            networkOutput.visible = true
                        }

                    }

                }
            }
        }

        Rectangle {
            id: network
            height: parent.height
            width: 0.7 * parent.width
            Layout.fillWidth: true

            Qan.GraphView {
                anchors.fill: parent
                graph : Qan.Graph {
                    id: moj_graf
                    objectName: "graph"
                    anchors.fill: parent

                    Component.onCompleted: {
                        drawNN()
                        defaultEdgeStyle.lineWidth = 1.5
                        defaultEdgeStyle.lineType = Qan.EdgeStyle.Straight
                    }
                }
            }

            Pane {
                id: networkOutput
                width: 0.4 * parent.width
                height: 0.5 * parent.height
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                visible: false
                Material.elevation: 10
                Text {
                    text: qsTr("Network output: ")
                    font.pixelSize: 14
                    leftPadding: 5
                    topPadding: 3
                }
            }

        }

    }


    function updateAllMenusSelected() {
        allMenusSelected = true;
        for (var i = 0; i < neuronsRepeater.count; i++){
            if (!neuronsRepeater.itemAt(i).isSelected) {
                allMenusSelected = false;
                break;
            }
        }

        for (var j = 0; j < actfuncRepeater.count; j++) {
            if (!actfuncRepeater.itemAt(j).isSelected) {
                allMenusSelected = false;
                break;
            }
        }
    }


    function drawNN(){
        moj_graf.clearGraph();
        nodes = [];

        // Create nodes
        for(var i = 0; i < _menu.layers; i++){
            nodes.push([]);
            for (var j = 0; j < _menu.neurons[i]; j++){
                var node = moj_graf.insertNode(Qt.createComponent("CustomNode.qml"));
                node.item.y = (i+1)*120;
                node.item.x = (j+1)*80;
                nodes[i].push(node);
            }
        }

        // Add lines connecting nodes
        for(i = 0; i < _menu.layers-1; i++){
            for (j = 0; j < _menu.neurons[i]; j++){
                for (var z = 0; z < _menu.neurons[i+1]; z++){
                   moj_graf.insertEdge(nodes[i][j], nodes[i+1][z]);
                }
            }
        }

    }



}

