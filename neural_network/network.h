#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <utility>
#include "layer.h"


class Network {
private:
    int numLayers = 0;
    std::vector<Layer> layers;

public:
    Network();
    ~Network() = default;

    void initializeNetwork(int numInputs, std::vector<LayerInfo> hiddenLayers, int numOutputs);
    void addLayer(Layer layer);
    void setLayer(int index, Layer layer);
    void insertHiddenLayer(LayerInfo layer);
    void removeHiddenLayers(int num);

    std::vector<double> forwardPropagate(std::vector<double> inputs);
    void backwardPropagateError(std::vector<double> expected);
    void updateWeights(std::vector<double> inputs, double learningRate);

    void train(std::vector<std::vector<double>>* trainingData, double learningRate, int numEpochs, int numOutputs);
    int predict(std::vector<double> input);
    double accuracy_metric(std::vector<int> expect, std::vector<int> predict);

    std::vector<Layer> getLayers() { return layers; };
    void setNumLayers() { numLayers = layers.size(); };
    void toString();
    std::string output;

    int getNumLayers() { return numLayers; };
    int getNumNeurons(int index) { return layers[index].getNumNeurons(); };
    Layer* getLayer(int index);
};

#endif // NETWORK_H
