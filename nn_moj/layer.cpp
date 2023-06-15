#include "layer.h"
#include <algorithm>

/* LAYER */

/*
* Layer Constructor
*/
Layer::Layer(int n_neurons, int n_weights, int activation_function, Factory* act_function_factory) {
    this->initNeurons(n_neurons, n_weights, activation_function, act_function_factory);
    m_activation_function = activation_function;
    act_function_factory = act_function_factory;
}

/*
* Layer Destructor
*/
Layer::~Layer() {
    /*pass*/
}

void Layer::initNeurons(int n_neurons, int n_weights, int activation_function, Factory* act_function_factory) {
//    m_neurons.clear();
//    //m_neurons.res
//    for (int n = 0; n < n_neurons; n++) {
//        m_neurons.push_back(Neuron(n_weights, activation_function));
//    }

    m_neurons.clear();
    m_neurons.reserve(n_neurons);

    std::generate_n(std::back_inserter(m_neurons), n_neurons, [n_weights, activation_function, act_function_factory]() {
        return Neuron(n_weights, activation_function, act_function_factory);
    });
}

std::string Layer::get_function() {
    switch (m_activation_function) {
    case 1:
        return "sigmoid";
        break;
    case 2:
        return "relu";
        break;
    case 3:
        return "tanh";
        break;
    default:
        return "sigmoid";
        break;
    }
}

