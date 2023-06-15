#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <regex>
#include <iterator>
#include <map>
#include <numeric>
#include <cmath>
#include "network.h"
#include "activation_function.h"


double accuracy_metric(std::vector<int> expect, std::vector<int> predict) {
    int correct = 0;

    for (int i = 0; i < predict.size(); i++){
        if (predict[i] == expect[i]) correct++;
    }
    return static_cast<double>(correct * 100.0f / predict.size());
}

int main(int argc, char* argv[]) {
    std::cout << "NN with Backpropagation in C++" << std::endl;

    std::vector<std::vector<double>> traindata {
        {2.7810836,		2.550537003,	0},
        {1.465489372,	2.362125076,	0},
        {3.396561688,	4.400293529,	0},
        {6.922596716,	1.77106367,		1},
        {8.675418651,	-0.242068655,	1},
        {7.673756466,	3.508563011,	1}
    };

    std::vector<std::vector<double>> testdata {
        {1.38807019,	1.850220317,	0},
         {3.06407232,	3.005305973,	0},
         {7.627531214,	2.759262235,	1},
         {5.332441248,	2.088626775,	1},
    };

    // binary classification
    std::set<double> results;
    for (const auto& r : traindata) {
        results.insert(r.back());
    }
    int n_outputs = results.size();
    int n_inputs = traindata[0].size() - 1;

    // we can experiment with these values
    double learn_rate = 0.4;
    int epochs = 50;

    Network* network = new Network();

    ActivationFunction* act_function = new Sigmoid();
    LayerInfo hidden;
    hidden.n_neurons = 5;
    hidden.act_function = act_function;


    // initialize a network
    std::vector<LayerInfo> layers;
    layers.push_back(hidden);

    network->initialize_network(n_inputs, layers, n_outputs);
    network->toString();

    // train the network (forward propagation, backward propagation and weight updating)
    network->train(traindata, learn_rate, epochs, n_outputs);

    // make a prediction on the test data
    std::cout << "[Prediction]" << std::endl;

    std::vector<int> predictions;
    std::vector<int> expected;
    for (const auto& data : testdata) {
        expected.push_back(data.back());

        int prediction = network->predict(data);
        predictions.push_back(prediction);

        std::cout << "\t[>] Expected=" << data.back() << ", Got=" << prediction << std::endl;
    }


    // accuracy metric
    std::cout << "Accuracy: " << accuracy_metric(expected, predictions) << "%" << std::endl;

    return 0;
}

