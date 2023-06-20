#include "network_builder.h"
#include "custom_node.h"
#include "custom_edge.h"

#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QPainterPath>



NetworkBuilder::NetworkBuilder(int inputs, int outputs) : m_neurons(MAX_LAYERS,1)
{
    network = new Network();
    LayerInfo layer;
    ActivationFunction* act_function = new Sigmoid();
    std::vector<LayerInfo> hidden;
    layer.n_neurons = 1;
    layer.act_function = act_function;
    hidden.push_back(layer);
    network->initialize_network(inputs, hidden, outputs);
}



void NetworkBuilder::setLayers(int n)
{
    if(m_layers == n)
        return;

    m_layers = n;
    m_neurons.resize(n);
    m_functions.resize(n);
    ActivationFunction* act_function = new Sigmoid();
    for (int var = 0; var < n; ++var) {
        LayerInfo l;
        l.n_neurons = 1;
        l.act_function = act_function;
        network->insert_hidden_layer(l);
    }

    emit layersChanged(m_layers);
}



void NetworkBuilder::setNeurons(std::vector<int> neurons)
{

    emit neuronsChanged(neurons);
}

void NetworkBuilder::setLayerNeurons(int layer, int num_neurons)
{
    if(m_neurons.at(layer) == num_neurons)
        return;

    ActivationFunction* act_function = new Sigmoid();
    m_neurons.at(layer) = num_neurons;
    network->get_layers().at(layer) = Layer(num_neurons, network->get_layers()[layer - 1].get_neurons().size()+1, act_function);
    if (layer + 1 <= m_layers){
        network->get_layers().at(layer+1) = Layer(network->get_layers().at(layer+1).get_neurons().size(), network->get_layers()[layer].get_neurons().size()+1, act_function);
    }
//    for (int var = 0; var < m_neurons.size(); ++var) {
//        qDebug() << "Layer neurons " << var+1 << ": " << m_neurons.at(var);
//    }
    setNeurons(m_neurons);
}


void NetworkBuilder::setFunctions(std::vector<int> functions)
{
    emit functionsChanged(functions);
}

void NetworkBuilder::setLayerFunction(int layer, int num)
{
    if(m_functions.at(layer) == num)
        return;

    m_functions.at(layer) = num;
//    for (int var = 0; var < m_functions.size(); ++var) {
//        qDebug() << "Layer function " << var+1 << ": " << m_functions.at(var);
//    }

    setFunctions(m_functions);
}

void NetworkBuilder::handleButtonClick()
{
    emit startTraining();
    network->toString();
    network->train(traindata, learn_rate, epochs, n_outputs);
    QString s = QString::fromStdString(network->output);
    setOutputText(s);
    emit endTraining();
}

void NetworkBuilder::setOutputText(QString s){
    emit textChanged(s);
}

void NetworkBuilder::drawNN(qan::Graph* graph, qan::GraphView *graphView, QQuickItem* network, qan::EdgeStyle* edgeStyle){
    graph->clearGraph();
    std::vector<std::vector<qan::Node*>> nodes;

    int numRows = m_layers;
    int circleSize = 40;
    int spacing = 80;


    // Create nodes
    for(int i = 0; i < numRows; i++){
        std::vector<qan::Node*> nodes_i;
        int numCircles = m_neurons[i];
        int rowWidth = numCircles * circleSize + (numCircles - 1) * spacing;
        int startX = (network->width() - rowWidth) / 2 - network->width()/2;


        for (int j = 0; j < m_neurons[i]; j++){
            qan::Node* node = graph->insertNode<CustomRoundNode>();

            int circleX = startX + j * (circleSize + spacing);
            int circleY = i * (circleSize + spacing);

            node->getItem()->setX(circleX);
            node->getItem()->setY(circleY);

            nodes_i.push_back(node);
        }
        nodes.push_back(nodes_i);
    }


    // Add arrows connecting nodes
    for(int i = 0; i < numRows-1; i++){
        for (int j = 0; j < m_neurons[i]; j++){
            for (int z = 0; z < m_neurons[i+1]; z++){
                graph->insertEdge(nodes[i][j], nodes[i+1][z]);
            }
        }
    }

    graphView->fitContentInView(network->width() - 70, network->height() - 70);
}
