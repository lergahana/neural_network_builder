#ifndef LAYER_H
#define LAYER_H

#pragma once
#include <iostream>
#include <vector>
#include "neuron.h"


class Layer {
public:
    Layer(int n_neurons, int n_weights, int activation_function);
    ~Layer();

    // return mutable reference to the neurons
    std::vector<Neuron>& get_neurons(void) { return m_neurons; };

    // return mutable reference to the neurons
    std::string get_function(void);

private:
    void initNeurons(int n_neurons, int n_weights, int activation_function);

    std::vector<Neuron> m_neurons;
    int m_activation_function;
};

#endif // LAYER_H
