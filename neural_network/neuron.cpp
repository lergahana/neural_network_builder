#include "neuron.h"
#include <numeric>

Neuron::Neuron(int nWeights, ActivationFunction* act_function)
    : m_nWeights(nWeights), act_function(act_function)
{
    // Generate random weights
    for (int w = 0; w < nWeights; w++) {
        m_weights.push_back(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
    }
}


void Neuron::activate(std::vector<double> inputs) {
    // Bias is stored at m_weights[m_nWeights - 1]
    double activation = m_weights[m_nWeights - 1];
    activation += std::inner_product(m_weights.begin(), m_weights.end() - 1, inputs.begin(), 0.0);
    m_activation = activation;
}

void Neuron::transfer() {
    m_output = act_function->activate(m_activation);
}

double Neuron::transferDerivative() {
    return act_function->activateDerivative(m_output);
}
