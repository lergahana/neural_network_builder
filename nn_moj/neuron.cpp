#include "neuron.h"
#include "activation_function.h"
#include <cmath>
#include <numeric>

/* NEURON */

/*
* Neuron Constructor
*/
Neuron::Neuron(int n_weights, int activation_function, Factory* act_function_factory) : m_nWeights(n_weights)
{
    this->initWeights(n_weights);
    m_activation_function = activation_function;
    act_function_factory = act_function_factory;
    m_nWeights = n_weights;
    m_activation = 0;
    m_output = 0;
    m_delta = 0;
}

/*
* Initialize weights
*/
void Neuron::initWeights(int n_weights) {
    // add random small weights (between 0 and 1)
    for (int w = 0; w < n_weights; w++) {
        m_weights.push_back(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
    }
}

/*
* Calculate the activation of a neuron for a given input
*/
void Neuron::activate(std::vector<double> inputs) {
    // the last weight is assumed to be the bias
    m_activation = m_weights[m_nWeights-1];

    // accumulate all weighted inputs
//    for (size_t i = 0; i < m_nWeights-1; i++)
//    {
//        m_activation += m_weights[i] * inputs[i];
//    }
    m_activation += std::inner_product(m_weights.begin(), m_weights.end() - 1, inputs.begin(), 0.0);


}

/*
* Transfer the activation of the neuron to an actual output
*/
void Neuron::transfer() {
    // Set activation function based on input integer
//    Sigmoid* activationFunc = static_cast<Sigmoid*>(act_function_factory->createFunction());
//    m_output = activationFunc->activate(m_activation);

    ActivationFunction af(m_activation_function);
    switch (m_activation_function) {
        case 1:
            m_output = af.sigmoid(m_activation);
            break;
        case 2:
            m_output = af.relu(m_activation);
            break;
        case 3:
            m_output = af.tanh(m_activation);
            break;
        default:
            m_output = af.sigmoid(m_activation);
            break;
    }
    // m_output = 1.0f / (1.0f + std::exp(-m_activation));
}

double Neuron::transfer_derivative() {
    Sigmoid* activationFunc = static_cast<Sigmoid*>(act_function_factory->createFunction());
    return activationFunc->activateDerivative(m_output);
//    ActivationFunction af(m_activation_function);
//    switch (m_activation_function) {
//    case 1:
//            return af.der_sigmoid(m_output);
//            break;
//    case 2:
//            return af.der_relu(m_output);
//            break;
//    case 3:
//            return af.der_tanh(m_output);
//            break;
//    default:
//            return af.der_sigmoid(m_output);
//            break;
//    }
//    // return static_cast<double>(m_output * (1.0 - m_output));
}


