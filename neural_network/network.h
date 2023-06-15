#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <utility>
#include "layer.h"


class Network {
private:
    int m_nLayers = 0;
    std::vector<Layer> m_layers;

public:
    Network();
    ~Network() = default;

    void initialize_network(int n_inputs, std::vector<LayerInfo> m_hidden, int n_outputs);
    void add_layer(Layer l);

    std::vector<double> forward_propagate(std::vector<double> inputs);
    void backward_propagate_error(std::vector<double> expected);
    void update_weights(std::vector<double> inputs, double l_rate);

    void train(std::vector<std::vector<double>> training_data, double l_rate, int n_epoch, int n_outputs);
    int predict(std::vector<double> input);

    std::vector<Layer> get_layers() { return m_layers; };
    void setNLayers() { m_nLayers = m_layers.size(); };
    void toString();

};

#endif // NETWORK_H
