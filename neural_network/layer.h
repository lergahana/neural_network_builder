#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "neuron.h"
#include "activation_function.h"

class Layer {
private:
    std::vector<Neuron> m_neurons;
    ActivationFunction* m_actFunction;

public:
    Layer(int numNeurons = 1, int numWeights = 1, ActivationFunction* actFunction = new Sigmoid());
    ~Layer() = default;

    std::vector<Neuron>& getNeurons() { return m_neurons; };
    ActivationFunction* getActivationFunction() { return m_actFunction; };
    void setActivationFunction(ActivationFunction* activationFunction) { m_actFunction = activationFunction; };

    int getNumNeurons() { return m_neurons.size(); };
};


#endif // LAYER_H
