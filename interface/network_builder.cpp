#include "network_builder.h"
#include "custom_node.h"

#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QPainterPath>
#include <QString>
#include <algorithm>


NetworkBuilder::NetworkBuilder(std::vector<std::vector<double>> data, int inputs, int outputs, int epochs, double learnRate)
    : m_data(data), m_numInputs(inputs), m_numOutputs(outputs), m_numEpochs(epochs), m_learningRate(learnRate)
{
    m_network = Network();
    m_network.initializeNetwork(m_numInputs, {Layer()}, m_numOutputs);
    setTestTrainData(m_data);
}


void NetworkBuilder::setNumLayers(int numLayers)
{
    int lastHiddenLayer = m_network.getNumLayers() - 1;

    // If the number of layers increased, add layers
    if (numLayers > lastHiddenLayer)
    {
        for (int i = lastHiddenLayer; i < numLayers; ++i)
        {
            m_network.insertHiddenLayer(Layer());
        }
    }
    // If the number of layers decreased, remove layers
    else
    {
        m_network.removeHiddenLayers(lastHiddenLayer - numLayers);
    }

    emit numLayersChanged(numLayers);
}

void NetworkBuilder::setLayerNeurons(int index, int numCurrentNeurons)
{
    int numInputNeurons = 0;
    // For the input layer, the number of input neurons is numInputs + 1
    if (index == 0) numInputNeurons = m_numInputs + 1;
    // For other layers, the number of input neurons depends on the previous layer
    else numInputNeurons = m_network.getNumNeurons(index - 1);


    m_network.changeLayer(index, numCurrentNeurons, numInputNeurons);

    // Fix the layer after the current one
    m_network.changeLayer(index + 1, m_network.getNumNeurons(index + 1), m_network.getNumNeurons(index) + 1);

    emit numNeuronsChanged(numCurrentNeurons);
}

void NetworkBuilder::setLearningRate(double learningRate)
{
    m_learningRate = learningRate;
    emit learningRateChanged(m_learningRate);
}

void NetworkBuilder::setNumEpochs(int numEpochs)
{
    m_numEpochs = numEpochs;
    emit numEpochsChanged(m_numEpochs);
}



void NetworkBuilder::setTestTrainData(std::vector<std::vector<double>> data)
{
    // 30% of data is for testing
    const int testDataSize = static_cast<int>(data.size() * 0.4);

    // Shuffle the input vector to randomize the order
    std::random_shuffle(data.begin(), data.end());

    // Allocate memory for m_testData and m_trainData
    m_testData = std::vector<std::vector<double>>();
    m_trainData = std::vector<std::vector<double>>();

    // Set test data
    m_testData.assign(data.begin(), data.begin()+testDataSize);

    // Set train data
    m_trainData.assign(data.begin()+testDataSize, data.end());

}


void NetworkBuilder::setLayerFunction(int layer, QString function)
{
    m_network.getLayer(layer).setActivationFunction(ActivationFunction::create(function.toStdString()));
    emit functionChanged(function.toStdString());
}

void NetworkBuilder::handleTrainButtonClick()
{
    emit startTraining();
//    m_network.toString();
    m_network.train(m_trainData, m_learningRate, m_numEpochs, m_numOutputs);
    int x = 0;
    for (auto point: m_network.getPlot()){
        m_chartData.append(QPointF(x, point*10));
        x += 10;
    }

    // Make a prediction on the test data
    std::vector<int> predictions;
    std::vector<int> expected;
    for (const auto& data : m_testData) {
        expected.push_back(data.back());
        predictions.push_back(m_network.predict(data));
    }
    double accuracy = m_network.accuracy_metric(expected, predictions);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << accuracy;
    QString s = QString::fromStdString("Accuracy: " + stream.str() + " %\n" + m_network.output);

    setOutputText(s);
    setTrainingDraw(true);
    emit endTraining();
}


void NetworkBuilder::handleResetButtonClick()
{
    m_outputText = "";
    m_chartData = QVector<QPointF>();
    setTrainingDraw(false);
    emit resetNetworkBuilder();
}

void NetworkBuilder::drawNeuralNetwork(qan::Graph* graph, qan::GraphView* graphView, QQuickItem* networkRect, qan::EdgeStyle* edgeStyle)
{

    graph->clearGraph();
    std::vector<std::vector<qan::Node*>> nodes;

    int numRows = m_network.getNumLayers();
    int circleHeight = 80;
    int spacing = 50;
    int numCircles = 1;

    int startX = 0;

    // Create nodes
    for (int i = 0; i <= numRows; i++)
    {
        std::vector<qan::Node*> nodes_i;

        // After the input layer
        if (i > 0)
        {
            numCircles = m_network.getNumNeurons(i - 1);
            circleHeight = 40;
        }

        int columnHeight = numCircles * circleHeight + (numCircles - 1) * spacing;
        int startY = (networkRect->height() - columnHeight) / 2 - networkRect->height() / 2;

        for (int j = 0; j < numCircles; j++)
        {
            qan::Node* node = graph->insertNode<CustomNodePurple>();

            // After training, neuron color depends on the activation of the neuron
            if (trainingDraw() && i > 0) {
                double activation = m_network.getLayer(i - 1).getNeurons()[j].getActivation();
                if (activation < 0.5) {
                    graph->removeNode(node);
                    node = graph->insertNode<CustomNodeBlue>();
                }
            }

            int circleX = startX + i * (circleHeight + spacing);
            int circleY = startY + j * (circleHeight + spacing);

            // Input and output layers have a different style
            if (i == 0 || i == numRows) node->getItem()->setOpacity(0.2);

            // Input layer
            if (i == 0) node->getItem()->setRect({0, 0, 40, 80});

            node->getItem()->setX(circleX);
            node->getItem()->setY(circleY);
            nodes_i.push_back(node);
        }
        nodes.push_back(nodes_i);
    }

    // Add arrows connecting nodes
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < nodes[i].size(); j++)
        {
            for (int z = 0; z < nodes[i + 1].size(); z++)
            {
                graph->insertEdge(nodes[i][j], nodes[i + 1][z]);
            }
        }
    }

    graphView->fitContentInView(networkRect->width() - 70, networkRect->height() - 150);
}
