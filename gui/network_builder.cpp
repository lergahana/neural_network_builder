#include "network_builder.h"
#include "custom_node.h"

#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QPainterPath>
#include <QString>



NetworkBuilder::NetworkBuilder(int inputs, int outputs)
{
    network = new Network();
    LayerInfo layer;
    std::vector<LayerInfo> hidden;
    hidden.push_back(layer);

    network->initialize_network(inputs, hidden, outputs);
    n_inputs = inputs;
    n_outputs = outputs;
}



void NetworkBuilder::setLayers(int n)
{
    int last_hid_layer = network->get_num_layers()-1;

    // If layer number increased add layers
    if (n > last_hid_layer)
    {
        for (int var = last_hid_layer; var < n; ++var)
        {
            network->insert_hidden_layer(LayerInfo());
        }
    }

    // If layer number decreased remove layers
    else {
        network->remove_hidden_layers(last_hid_layer-n);
    }

    emit layersChanged(m_layers);
}




void NetworkBuilder::setLayerNeurons(int layer, int num_neurons)
{

    // For input layer number of input neurons is n_inputs+1
    if (layer == 0)
    {
        network->set_layer(layer, Layer(num_neurons, n_inputs+1));
    }

    // For other layers numer of input neurons depends on the input layer
    else
    {
        network->set_layer(layer, Layer(num_neurons, network->get_num_neurons(layer-1)));
    }

    // Fix the layer after current
    network->set_layer(layer+1, Layer(network->get_num_neurons(layer+1), network->get_num_neurons(layer)+1));

    emit neuronsChanged(num_neurons);
}

void NetworkBuilder::setLearnRate(double lr)
{
    m_learn_rate = lr;
    emit learnRateChanged(m_learn_rate);
}

void NetworkBuilder::setEpochs(int e)
{
    m_epochs = e;
    emit epochsChanged(m_epochs);
}


void NetworkBuilder::setLayerFunction(int layer, QString function)
{
    network->get_layer(layer)->set_act_function(ActivationFunction::create(function.toStdString()));
    emit functionChanged(function.toStdString());
}

void NetworkBuilder::handleButtonClick()
{
    emit startTraining();
    network->toString();
//    std::cout << "Epochs " << epochs() << " , learning rate " << learn_rate() << std::endl;
    network->train(traindata, learn_rate(), epochs(), n_outputs);
    QString s = QString::fromStdString(network->output);
    setOutputText(s);
    emit endTraining();
}

void NetworkBuilder::setOutputText(QString s){
    m_outputText = s;
    emit textChanged(s);
}

void NetworkBuilder::drawNN(qan::Graph* graph, qan::GraphView *graphView, QQuickItem* network_rect, qan::EdgeStyle* edgeStyle){
    graph->clearGraph();
    std::vector<std::vector<qan::Node*>> nodes;

    int numRows = this->network->get_layers().size();
    int circleWidth = 80;
    int spacing = 50;
    int numCircles = 1;

    // Create nodes
    for(int i = 0; i <= numRows; i++){
        std::vector<qan::Node*> nodes_i;

        // After input layer
        if (i > 0){
            numCircles = network->get_layers()[i-1].get_neurons().size();
            circleWidth = 40;
        }

        int rowWidth = numCircles * circleWidth + (numCircles - 1) * spacing;
        int startX = (network_rect->width() - rowWidth) / 2 - network_rect->width()/2;

        for (int j = 0; j < numCircles; j++){
            qan::Node* node = graph->insertNode<CustomRoundNode>();

            int circleX = startX + j * (circleWidth + spacing);
            int circleY = i * (circleWidth + spacing);

            // Input and output layer different style
            if (i == 0 || i == numRows){
                node->getItem()->setOpacity(0.2);
            }

            // Input layer
            if(i == 0){
                node->getItem()->setRect({0,0,80,40});
            }

            node->getItem()->setX(circleX);
            node->getItem()->setY(circleY);
            nodes_i.push_back(node);
        }
        nodes.push_back(nodes_i);
    }


    // Add arrows connecting nodes
    for(int i = 0; i < numRows; i++){
        for (int j = 0; j < nodes[i].size(); j++){
            for (int z = 0; z < nodes[i+1].size(); z++){
                graph->insertEdge(nodes[i][j], nodes[i+1][z]);
            }
        }
    }

    graphView->fitContentInView(network_rect->width() - 70, network_rect->height() - 70);
}
