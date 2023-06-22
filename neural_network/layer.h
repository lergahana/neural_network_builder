#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "neuron.h"
#include "activation_function.h"

class Layer {
private:
    std::vector<Neuron> neurons;
    ActivationFunction* actFunction;

public:
    Layer(int numNeurons, int numWeights, ActivationFunction* actFunction = new Sigmoid());
    ~Layer() = default;

    std::vector<Neuron>& getNeurons() { return neurons; };
    ActivationFunction* getActivationFunction() { return actFunction; };
    void setActivationFunction(ActivationFunction* activationFunction);

    int getNumNeurons() { return neurons.size(); };
};

struct LayerInfo {
    int numNeurons = 1;
    ActivationFunction* activationFunction = new Sigmoid();
};

#endif // LAYER_H
