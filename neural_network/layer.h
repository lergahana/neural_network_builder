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

public:
    Layer(int n_neurons, int n_weights, ActivationFunction* act_function);
    ~Layer()=default;

    std::vector<Neuron>& get_neurons() { return m_neurons; };

};

struct LayerInfo{
    int n_neurons;
    ActivationFunction* act_function;
};

#endif // LAYER_H
