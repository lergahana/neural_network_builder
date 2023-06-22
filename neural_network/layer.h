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
    ActivationFunction* act_function;

public:
    Layer(int n_neurons, int n_weights, ActivationFunction* act_function = new Sigmoid());
    ~Layer()=default;

    std::vector<Neuron>& get_neurons() { return m_neurons; };
    ActivationFunction* get_act_function() { return act_function; };
    void set_act_function(ActivationFunction* a);

    int get_num_neurons() { return m_neurons.size(); };
};

struct LayerInfo{
    int n_neurons = 1;
    ActivationFunction* act_function = new Sigmoid();
};

#endif // LAYER_H
