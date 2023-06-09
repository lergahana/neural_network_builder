#ifndef NEURON_H
#define NEURON_H

#pragma once
#include <iostream>
#include <vector>

class Neuron {
public:
    Neuron(int n_weights, int activation_function);
    ~Neuron()= default;

    void activate(std::vector<float> inputs);
    void transfer();
    float transfer_derivative();

    // return mutable reference to the neuron weights
    std::vector<float>& get_weights(void) { return m_weights; };

    float get_output(void) { return m_output; };
    float get_activation(void) { return m_activation; };
    float get_delta(void) { return m_delta; };

    void set_delta(float delta) { m_delta = delta; };

private:
    size_t m_nWeights;
    std::vector<float> m_weights;
    float m_activation=0;
    float m_output;
    float m_delta;
    int m_activation_function;

private:
    void initWeights(int n_weights);
};

#endif // NEURON_H
