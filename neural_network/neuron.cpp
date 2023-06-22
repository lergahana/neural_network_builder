#include "neuron.h"
#include <numeric>

Neuron::Neuron(int numWeights, ActivationFunction* actFunction) : m_numWeights(numWeights), activationFunction(actFunction)
{
    // Generate random weights
    for (int w = 0; w < numWeights; w++) {
        m_weights.push_back(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
    }
}

void Neuron::activate(std::vector<double> inputs) {
    // Bias is stored at m_weights[m_nWeights - 1]
    double activation = m_weights[m_numWeights - 1];
    activation += std::inner_product(m_weights.begin(), m_weights.end() - 1, inputs.begin(), 0.0);
    m_activation = activation;
}

void Neuron::transfer() {
    m_output = activationFunction->activate(m_activation);
}

double Neuron::transferDerivative() {
    return activationFunction->activateDerivative(m_output);
}
