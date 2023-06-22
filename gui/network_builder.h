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
    Q_PROPERTY(QString outputText READ outputText WRITE setOutputText NOTIFY textChanged)
    Q_PROPERTY(double learn_rate READ learn_rate WRITE setLearnRate NOTIFY learnRateChanged)
    Q_PROPERTY(int epochs READ epochs WRITE setEpochs NOTIFY epochsChanged)

private:
    int m_layers = 1;
    QString m_outputText = "Training starting...";
    double m_learn_rate;
    int m_epochs;

public:
    NetworkBuilder(int inputs, int outputs);
    ~NetworkBuilder() = default;

    int layers() const { return m_layers; };
    QString outputText() const { return m_outputText; };
    double learn_rate() const { return m_learn_rate; };
    int epochs() const { return m_epochs; };

    Network* network;
    std::vector<std::vector<double>> traindata;
    int n_outputs;
    int n_inputs;

    Q_INVOKABLE int get_num_neurons(int index) { return network->get_num_neurons(index); };
    Q_INVOKABLE void setLayerFunction(int l, QString n);
    Q_INVOKABLE void setLayerNeurons(int l, int n);


public slots:
    void setLayers(int n);
    void setLearnRate(double lr);
    void setEpochs(int e);
    void setOutputText(QString);
    void handleButtonClick();
    void drawNN(qan::Graph *graph, qan::GraphView *graphView, QQuickItem* network, qan::EdgeStyle* edgeStyle);

signals:
    void layersChanged(int);
    void neuronsChanged(int);
    void functionChanged(std::string);
    void learnRateChanged(double);
    void epochsChanged(int);
    void networkBuilt();
    void textChanged(QString);
    void startTraining();
    void endTraining();

};

#endif // NETWORK_BUILDER_H
