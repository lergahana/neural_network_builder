#ifndef NETWORK_BUILDER_H
#define NETWORK_BUILDER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QDebug>
#include <QuickQanava>
#include "network.h"

#define MAX_NODES 10
#define MAX_LAYERS 10

class NetworkBuilder : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int layers READ layers WRITE setLayers NOTIFY layersChanged)
    Q_PROPERTY(std::vector<int> neurons READ neurons WRITE setNeurons NOTIFY neuronsChanged)
    Q_PROPERTY(std::vector<std::string> functions READ functions WRITE setFunctions NOTIFY functionsChanged)
    Q_PROPERTY(Network* network NOTIFY networkBuilt)
    Q_PROPERTY(QString outputText READ outputText WRITE setOutputText NOTIFY textChanged)

private:
    int m_layers = 1;
    std::vector<int> m_neurons;
    std::vector<std::string> m_functions;
    QString m_outputText = "Training starting...";

public:
    NetworkBuilder(int inputs, int outputs);
    ~NetworkBuilder() = default;

    int layers() const { return m_layers; };
    std::vector<int> neurons()  const { return m_neurons; };
    std::vector<std::string> functions()  const { return m_functions; };
    QString outputText() const { return m_outputText; };
    Network* network;
    std::vector<std::vector<double>> traindata;
    double learn_rate;
    int epochs;
    int n_outputs;


public slots:
    void setLayers(int n);
    void setNeurons(std::vector<int>);
    void setFunctions(std::vector<std::string>);
    void setLayerNeurons(int l, int n);
    void setLayerFunction(int l, std::string n);
    void handleButtonClick();
    void setOutputText(QString);
    void drawNN(qan::Graph *graph, qan::GraphView *graphView, QQuickItem* network, qan::EdgeStyle* edgeStyle);

signals:
    void layersChanged(int);
    void neuronsChanged(std::vector<int>);
    void functionsChanged(std::vector<std::string>);
    void networkBuilt();
    void textChanged(QString);
    void startTraining();
    void endTraining();

};

#endif // NETWORK_BUILDER_H
