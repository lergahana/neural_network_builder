#include "network.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

Network::Network() {
    // Needed for rand
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Network::initializeNetwork(int numInputs, std::vector<Layer*> hiddenLayers, int numOutputs) {
    // First layer
    Layer* firstLayer = new Layer(hiddenLayers[0]->getNumNeurons(), numInputs + 1, hiddenLayers[0]->getActivationFunction());
    addLayer(firstLayer);

    // Hidden layers
    for (int i = 0; i < hiddenLayers.size() - 1; i++) {
        Layer* hiddenLayer = new Layer(hiddenLayers[i + 1]->getNumNeurons(), hiddenLayers[i]->getNumNeurons() + 1, hiddenLayers[i + 1]->getActivationFunction());
        addLayer(hiddenLayer);
    }

    // Last layer
    Layer* lastLayer = new Layer(numOutputs, hiddenLayers.back()->getNumNeurons() + 1, hiddenLayers.back()->getActivationFunction());
    addLayer(lastLayer);

    // Clear from memory
    hiddenLayers.clear();

    setNumLayers();
}

void Network::addLayer(Layer* layer) {
    layers.push_back(layer);
}

void Network::setLayer(int index, Layer* layer) {
    layers[index] = layer;
}

Layer* Network::getLayer(int index) {
    return layers[index];
}

int Network::getNumNeurons(int index) {
    if (index < 0 || index > layers.size()) return 0;
    return layers[index]->getNumNeurons();
}

void Network::insertHiddenLayer(Layer* layer) {
    Layer* output = layers.back();
    // Remove output layer
    layers.pop_back();
    // Add hidden layer
    layers.push_back(new Layer(layer->getNumNeurons(), layers.back()->getNumNeurons() + 1, layer->getActivationFunction()));
    // Add output layer
    layers.push_back(new Layer(output->getNumNeurons(), layers.back()->getNumNeurons() + 1, output->getActivationFunction()));
    setNumLayers();
}

void Network::removeHiddenLayers(int num) {
    std::vector<Layer*> newLayers;
    Layer* output = layers.back();
    int lastHiddenLayer = layers.size() - num - 1;

    for (int i = 0; i < lastHiddenLayer; i++) {
        newLayers.push_back(layers[i]);
    }

    newLayers.push_back(new Layer(output->getNumNeurons(), layers[lastHiddenLayer]->getNumNeurons() + 1, output->getActivationFunction()));

    layers.clear();
    layers = newLayers;
    newLayers.clear();
    setNumLayers();
}

std::vector<double> Network::forwardPropagate(std::vector<double> inputs) {
    std::vector<double> newInputs;
    for (int i = 0; i < numLayers; i++) {
        newInputs.clear();
        std::vector<Neuron>& layerNeurons = layers[i]->getNeurons();

        for (int n = 0; n < layerNeurons.size(); n++) {
            layerNeurons[n].activate(inputs);
            layerNeurons[n].transfer();
            newInputs.push_back(layerNeurons[n].getOutput());
        }
        inputs = newInputs;
    }
    return inputs;
}

void Network::backwardPropagateError(std::vector<double> expected) {
    // Start from last layer and propagate error to the first layer
    for (int i = numLayers - 1; i >= 0; i--) {
        std::vector<Neuron>& layerNeurons = layers[i]->getNeurons();
        // Iterate over each neuron in this layer
        for (int n = 0; n < layerNeurons.size(); n++) {
            double error = 0.0;
            // Last layer
            if (i == numLayers - 1) {
                error = expected[n] - layerNeurons[n].getOutput();
            }
            // All other layers
            else {
                for (auto& neuron : layers[i + 1]->getNeurons()) {
                    error += (neuron.getWeights()[n] * neuron.getDelta());
                }
            }
            layerNeurons[n].setDelta(error * layerNeurons[n].transferDerivative());
        }
    }
}

void Network::updateWeights(std::vector<double> inputs, double learningRate) {
    std::vector<double> newInputs;
    for (int i = 0; i < numLayers; i++) {
        newInputs.clear();
        if (i != 0) {
            for (auto& neuron : layers[i - 1]->getNeurons()) {
                newInputs.push_back(neuron.getOutput());
            }
        }
        else {
            newInputs = std::vector<double>(inputs.begin(), inputs.end() - 1);
        }

        std::vector<Neuron>& layerNeurons = layers[i]->getNeurons();

        for (int n = 0; n < layerNeurons.size(); n++) {
            std::vector<double>& weights = layerNeurons[n].getWeights();

            for (int j = 0; j < newInputs.size(); j++) {
                weights[j] += learningRate * layerNeurons[n].getDelta() * newInputs[j];
            }
            // Update bias
            weights.back() += learningRate * layerNeurons[n].getDelta();
        }
    }
}

void Network::train(std::vector<std::vector<double>>* trainingData, double learningRate, int numEpochs, int numOutputs) {
    for (int e = 0; e < numEpochs; e++) {
        double sumError = 0;

        for (const auto& row : *trainingData) {
            std::vector<double> outputs = forwardPropagate(row);
            std::vector<double> expected(numOutputs, 0.0);
            // The index corresponding to the expected output class is set to 1.0, while all other elements remain 0.0
            expected[static_cast<int>(row.back())] = 1.0;
            for (int x = 0; x < numOutputs; x++) {
                sumError += static_cast<double>(std::pow((expected[x] - outputs[x]), 2));
            }
            backwardPropagateError(expected);
            updateWeights(row, learningRate);
        }
        sumError = std::round(sumError * 10000) / 10000.0;
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(4) << "[>] Epoch " << (e + 1) << ": error = " << sumError << std::endl;
        output += stream.str();

        // Uncomment to print to std output
        // std::cout << "[>] Epoch " << (e + 1) << ": error = " << sumError << std::endl;
    }
}

int Network::predict(std::vector<double> input) {
    std::vector<double> outputs = forwardPropagate(input);
    return std::max_element(outputs.begin(), outputs.end()) - outputs.begin();
}

double Network::accuracy_metric(std::vector<int> expect, std::vector<int> predict) {
    int correct = 0;

    for (int i = 0; i < predict.size(); i++){
        if (predict[i] == expect[i]) correct++;
    }
    return static_cast<double>(correct * 100.0f / predict.size());
}

void Network::toString() {
    std::cout << "Network: " << std::endl;
    std::cout << "Number of layers: " << layers.size() << std::endl;
    for (int i = 0; i < layers.size(); i++) {
        std::string line(100, '-');
        std::cout << line << std::endl;
        std::cout << "Number of neurons in layer: " << i + 1 << ": " << layers[i]->getNumNeurons() << std::endl;
        std::cout << "Activation function in layer: " << i + 1 << ": " << layers[i]->getActivationFunction()->getName() << std::endl;
        for (int j = 0; j < layers[i]->getNeurons().size(); j++) {
            std::cout << "Neuron " << (j + 1) << "\n   weights: ";
            std::vector<double> weights = layers[i]->getNeurons()[j].getWeights();
            for (size_t w = 0; w < weights.size(); ++w) {
                std::cout << weights[w];
                if (w < weights.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "\t delta: " << layers[i]->getNeurons()[j].getDelta();
            std::cout << "\t output: " << layers[i]->getNeurons()[j].getOutput();
            std::cout << "\t activation: " << layers[i]->getNeurons()[j].getActivation();
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
