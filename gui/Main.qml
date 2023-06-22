import QtQuick
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2
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

    required property NetworkBuilder _menu
    property var nodes: []
    //property int MAXNODES: 10

    RowLayout {
        width: window.width
        height: window.height

        Rectangle {
            id: menu
            width: 0.3*parent.width
            height: parent.height
            anchors.top: window.top
            color: "#E8E9EB"

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
                        bottomPadding: 5
                    }

                    SpinBox {
                        id: layers
                        width: layersText.width
                        topPadding: 2

                        editable: true

                        from: 1
                        to: 10
                        stepSize: 1

                        value: 1
                        onValueChanged: {
                            _menu.setLayers(value);
                            neuronsRepeater.model = value;
                            actfuncRepeater.model = value;
                            _menu.drawNN(graph, graphView, network, defaultEdgeStyle);
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
                                bottomPadding: 5
                            }

                            SpinBox {
                                id: numNeurons
                                width: layersText.width
                                topPadding: 2

                                editable: true

                                from: 1
                                to: 10
                                stepSize: 1

                                value: _menu.get_num_neurons(index);
                                onValueChanged: {
                                    _menu.setLayerNeurons(index, value);
                                    _menu.drawNN(graph, graphView, network, defaultEdgeStyle);
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
                                onClicked: _menu.setLayerFunction(index, text);
                            }

                            RadioButton {
                                text: "relu"
                                topPadding: 2
                                onClicked: _menu.setLayerFunction(index, text);
                            }

                            RadioButton {
                                text: "tanh"
                                topPadding: 2
                                onClicked: _menu.setLayerFunction(index, text);
                            }
                        }
                    }

                    Button {
                        objectName: "startTraining"
                        text: "Start training"
                        onClicked: {
                            menu.visible = false
                            network.width = window.width
                            networkOutput.visible = true
                            hyperparameters.visible = false;

                            _menu.handleButtonClick()
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
            Layout.alignment: Qt.AlignTop

            Item {
                z: 2
                id: hyperparameters

                ColumnLayout {
                    spacing: 3

                    Text {
                        text: "Learning rate: "
                        leftPadding: 10
                        font.pixelSize: 12
                    }

                    RowLayout {
                        spacing: 10

                        Slider {
                            id: learningRate
                            from: 0.1
                            value: 0.40
                            to: 1
                            stepSize: 0.1
                            snapMode: Slider.SnapAlways

                            onValueChanged: {
                                learningRateLabel.text = String(learningRate.value.toFixed(2));
                                _menu.learn_rate = value;
                            }
                        }

                        Text {
                            id: learningRateLabel
                            text: String(learningRate.value.toFixed(2))
                            font.pixelSize: 12
                            bottomPadding: 3
                        }
                    }

                    Text {
                        text: "Number of epochs: "
                        leftPadding: 10
                        font.pixelSize: 12
                    }

                    RowLayout {
                        spacing: 10

                        Slider {
                            id: epochs
                            from: 10
                            value: 50
                            to: 100
                            stepSize: 10
                            snapMode: Slider.SnapAlways

                            onValueChanged: {
                                epochsLabel.text = String(epochs.value);
                                _menu.epochs = value;
                            }
                        }

                        Text {
                            id: epochsLabel
                            text: String(epochs.value)
                            font.pixelSize: 12
                            bottomPadding: 3
                        }
                    }
                }
            }


            Qan.GraphView {
                z: 1
                id: graphView
                anchors.fill: network
                navigable: true
                grid: Qan.AbstractLineGrid

                graph : Qan.Graph {
                    id: graph
                    objectName: "graph"
                    anchors.fill: parent

                    Component.onCompleted: {
                        _menu.drawNN(graph, graphView, network, defaultEdgeStyle);
                        defaultEdgeStyle.lineWidth = 1.5;
                    }
                }
            }



            Pane {
                z: 2
                id: networkOutput
                objectName: "networkOutput"
                width: 0.25 * network.width
                height: network.height
                anchors.right: network.right
                anchors.bottom: network.bottom
                visible: false
                Material.elevation: 100
                opacity: 0.8

                ScrollView{
                    id: scrollOutput
                    anchors.fill: parent
                    Text {
                        id: networkOutputText
                        objectName: "networkOutputText"
                        font.pixelSize: 14
                        leftPadding: 5
                        topPadding: 3
                    }
                }

                Component.onCompleted: {
                    networkOutputText.text = _menu.outputText
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

    onWindowStateChanged: _menu.drawNN(graph, graphView, network, defaultEdgeStyle)

}
