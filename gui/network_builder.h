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

    Q_PROPERTY(int numLayers READ numLayers WRITE setNumLayers NOTIFY numLayersChanged)
    Q_PROPERTY(QString outputText READ outputText WRITE setOutputText NOTIFY outputTextChanged)
    Q_PROPERTY(QString testText READ testText WRITE setTestText NOTIFY testTextChanged)
    Q_PROPERTY(double learningRate READ learningRate WRITE setLearningRate NOTIFY learningRateChanged)
    Q_PROPERTY(int numEpochs READ numEpochs WRITE setNumEpochs NOTIFY numEpochsChanged)

private:
    int m_numLayers = 1;
    QString m_outputText = "";
    QString m_testText = "";
    double m_learningRate;
    int m_numEpochs;
    Network* m_network;
    std::vector<std::vector<double>>* m_data;
    std::vector<std::vector<double>>* m_trainData;
    std::vector<std::vector<double>>* m_testData;
    int m_numOutputs;
    int m_numInputs;

public:
    NetworkBuilder(std::vector<std::vector<double>>* data, int inputs, int outputs, int epochs, double learnRate);
    ~NetworkBuilder() = default;

    int numLayers() const { return m_numLayers; };
    QString outputText() const { return m_outputText; };
    QString testText() const { return m_testText; };
    double learningRate() const { return m_learningRate; };
    int numEpochs() const { return m_numEpochs; };

    void setTestTrainData(std::vector<std::vector<double>>* data);
    void setNumOutputs(int num) { m_numOutputs = num; };
    void setNumInputs(int num) { m_numInputs = num; };

    int numOutputs() { return m_numOutputs; };
    int numInputs() { return m_numInputs; };
    Network* network() { return m_network; };

    Q_INVOKABLE int getNumNeurons(int index) { return m_network->getNumNeurons(index); };
    Q_INVOKABLE void setLayerFunction(int layer, QString name);
    Q_INVOKABLE void setLayerNeurons(int layer, int numNeurons);


public slots:
    void setNumLayers(int numLayers);
    void setLearningRate(double learningRate);
    void setNumEpochs(int numEpochs);
    void setOutputText(QString);
    void setTestText(QString);
    void handleTrainButtonClick();
    void handleTestButtonClick();
    void drawNeuralNetwork(qan::Graph *graph, qan::GraphView *graphView, QQuickItem* network, qan::EdgeStyle* edgeStyle);

signals:
    void numLayersChanged(int);
    void numNeuronsChanged(int);
    void functionChanged(std::string);
    void learningRateChanged(double);
    void numEpochsChanged(int);
    void networkBuilt();
    void outputTextChanged(QString);
    void testTextChanged(QString);
    void startTraining();
    void endTraining();
    void endTest();

};

#endif // NETWORK_BUILDER_H
