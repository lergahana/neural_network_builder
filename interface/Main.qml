import QtQuick
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2
import QtQuick.Layouts
import QtQuick.Shapes
import QtQml.Models

import CustomChart 1.0
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

    required property NetworkBuilder networkBuilder

    RowLayout {
        width: window.width
        height: window.height

        Rectangle {
            id: menu
            objectName: "menu"
            width: 0.3*parent.width
            height: parent.height
            color: "#E8E9EB"
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            z: 3

            onVisibleChanged: network.width = parent.width*0.7

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
                            networkBuilder.setNumLayers(value)
                            neuronsRepeater.model = value
                            actfuncRepeater.model = value
                            networkBuilder.drawNeuralNetwork(graph, graphView, network, defaultEdgeStyle)
                        }
                    }

                    Repeater {
                        id: neuronsRepeater
                        objectName: "neuronsRepeater"
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
                                objectName: "numNeurons"
                                width: layersText.width
                                topPadding: 2

                                editable: true

                                from: 1
                                to: 10
                                stepSize: 1

                                value: networkBuilder.getNumNeurons(index)
                                onValueChanged: {
                                    networkBuilder.setLayerNeurons(index, value)
                                    networkBuilder.drawNeuralNetwork(graph, graphView, network, defaultEdgeStyle)
                                }
                            }
                        }
                    }

                    Repeater {
                        id: actfuncRepeater
                        objectName: "actfuncRepeater"
                        model: 1

                        Column {
                            id: radioButtons
                            Text {
                                text: "Select activation function for layer " + (index+1)
                                font.pixelSize:  14
                                topPadding: 15
                            }
                            RadioButton {
                                id: defaultFunction
                                text: "sigmoid"
                                checked: true
                                onClicked: networkBuilder.setLayerFunction(index, text)
                            }

                            RadioButton {
                                text: "relu"
                                topPadding: 2
                                onClicked: networkBuilder.setLayerFunction(index, text)
                            }

                            RadioButton {
                                text: "tanh"
                                topPadding: 2
                                onClicked: networkBuilder.setLayerFunction(index, text)
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
                            hyperparameters.visible = false
                            resetButton.visible = true

                            networkBuilder.handleTrainButtonClick()
                            networkBuilder.drawNeuralNetwork(graph, graphView, network, defaultEdgeStyle)
                        }


                    }

                }
            }
        }

        Rectangle {
            id: network
            objectName: "network"
            height: parent.height
            width: parent.width*0.7
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop


            Item {
                z: 2
                id: hyperparameters
                height: 100
                width: network.width - 20
                Layout.alignment: Qt.AlignTop

                RowLayout {
                    id: hyperparametersRow
                    anchors.fill: parent

                    ColumnLayout {
                        spacing: 1
                        Layout.alignment: Qt.AlignLeft

                        Text {
                            id: textLearningRate
                            text: "Learning rate: "
                            leftPadding: 10
                            font.pixelSize: 12
                        }

                        RowLayout {
                            spacing: 10

                            Slider {
                                id: learningRate
                                width: 50
                                from: 0.1
                                value: 0.40
                                to: 1
                                stepSize: 0.1
                                snapMode: Slider.SnapAlways

                                onValueChanged: {
                                    learningRateLabel.text = String(learningRate.value.toFixed(2))
                                    networkBuilder.setLearningRate(value)
                                }
                            }

                            Text {
                                id: learningRateLabel
                                text: String(learningRate.value.toFixed(2))
                                font.pixelSize: 12
                                bottomPadding: 3
                            }
                        }

                    }

                    ColumnLayout {
                        spacing: 1
                        Layout.alignment: Qt.AlignRight

                        Text {
                            text: "Number of epochs: "
                            leftPadding: 10
                            font.pixelSize: 12
                        }

                        RowLayout {
                            spacing: 10

                            Slider {
                                id: epochs
                                width: 50
                                from: 10
                                value: 50
                                to: 100
                                stepSize: 10
                                snapMode: Slider.SnapAlways

                                onValueChanged: {
                                    epochsLabel.text = String(epochs.value)
                                    networkBuilder.setNumEpochs(value)
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
            }

            Qan.GraphView {
                z: 1
                id: graphView
                width: network.width
                height: network.height
                navigable: true
                grid: Qan.AbstractLineGrid

                graph : Qan.Graph {
                    id: graph
                    objectName: "graph"
                    anchors.fill: parent

                    Component.onCompleted: {
                        defaultEdgeStyle.lineWidth = 1.5
                    }
                }
            }

            Pane {
                z: 2
                id: networkOutput
                objectName: "networkOutput"
                width: 250
                height: network.height
                visible: false
                Material.elevation: 10
                opacity: 0.8
                anchors.right: network.right
                anchors.bottom: Qt.BottomEdge

                ScrollView{
                    id: scrollOutput
                    anchors.fill: parent
                    contentHeight: chart.height + networkOutputText.height + textChart.height

                    ColumnLayout{
                        Text {
                            id: textChart
                            text: "Relative validation loss"
                            font.pixelSize: 14
                            leftPadding: 5
                            topPadding: 3
                        }

                        ChartItem {
                            id: chart
                            objectName: "chart"
                            width: 200
                            height: 200
                        }

                        Text {
                            id: networkOutputText
                            objectName: "networkOutputText"
                            font.pixelSize: 14
                            leftPadding: 5
                            topPadding: 3

                        }
                    }
                }

                Component.onCompleted: {
                    networkOutputText.text = networkBuilder.outputText
                }

                onVisibleChanged: {
                    if (window.visibility === Window.Maximized) {
                        height = window.height;
                    }
                }
            }

            Button {
                z: 3
                id: resetButton
                visible: false
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                x: 20; y: 20
                text: "Return"
                onClicked: {
                    resetButton.visible = false
                    hyperparameters.visible = true
                    networkOutput.visible = false
                    menu.visible = true
                    networkBuilder.handleResetButtonClick()
                    networkBuilder.drawNeuralNetwork(graph, graphView, network, defaultEdgeStyle)
                }
            }
        }
    }


    onWindowStateChanged: {
        if (!networkOutput.visible) {
            networkOutput.height = network.height
        }
        networkBuilder.drawNeuralNetwork(graph, graphView, network, defaultEdgeStyle)
    }

}
