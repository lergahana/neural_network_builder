#pragma once
#include <iostream>
#include <vector>
#include "layer.h"


class Network {
public:
    Network();
    ~Network();

    void initialize_network(int n_inputs, std::vector<std::pair<int, int>> n_hidden, int n_outputs);

    void add_layer(int n_neurons, int n_weights, int activation_function);
    std::vector<float> forward_propagate(std::vector<float> inputs);
    void backward_propagate_error(std::vector<float> expected);
    void update_weights(std::vector<float> inputs, float l_rate);
    void train(std::vector<std::vector<float>>trainings_data, float l_rate, size_t n_epoch, size_t n_outputs);
    int predict(std::vector<float> input);

    void display_human();

private:
    size_t m_nLayers;
    std::vector<Layer> m_layers;

};
