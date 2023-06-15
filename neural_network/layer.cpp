#include "layer.h"


Layer::Layer(int n_neurons, int n_weights, ActivationFunction* act_function)
{
    m_neurons.clear();
    m_neurons.reserve(n_neurons);
    std::generate_n(std::back_inserter(m_neurons), n_neurons, [n_weights, act_function]() {
        return Neuron(n_weights, act_function);
    });
}
