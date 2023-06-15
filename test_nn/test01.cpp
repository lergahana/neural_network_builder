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


std::vector<std::vector<double>> load_csv_data(std::string filename);
std::vector<double> evaluate_network(std::vector<std::vector<double>> dataset, int n_folds, double l_rate, int n_epoch, int n_hidden);
double accuracy_metric(std::vector<int> expect, std::vector<int> predict);


/*
* This main function will load a csv-dataset and normalize the data. Subsequently, a network
* for this data will be initialized, trained and evaluated using cross-validation.
*
* Feel free to play around with the folds, learning rate, epochs and hidden neurons.
* If you want to modify the network itself (activation function, additional layers, etc.)
* you will want to look at NeuralNetwork.cpp.
*
* (See at the bottom for a second main function that's for displaying and testing a very small network.)
*/
//int main(int argc, char* argv[]) {
//    std::cout << "Neural Network with Backpropagation in C++ from scratch" << std::endl;

//    std::vector<std::vector<double>> csv_data;
//    csv_data = load_csv_data("seeds_dataset.csv");

//    /*
//    * Normalize the last column (turning the outputs into values starting from 0 for the one-hot encoding in the end)
//    */
//    std::map<int, int> lookup = {};
//    int index = 0;
//    for (auto& vec : csv_data) {
//        std::pair<std::map<int, int>::iterator, bool> ret;
//        // insert unique values
//        ret = lookup.insert(std::pair<int, int>(static_cast<int>(vec.back()),index));
//        // update the vector with the new index
//        vec.back() = static_cast<double>(ret.first->second);
//        // if an actual new value was found, increase the index
//        if (ret.second) {
//            index++;
//        }
//    }

//    int n_folds = 5;		// how many folds you want to create from the given dataset
//    double l_rate = 0.3f;	// how much of an impact shall an error have on a weight
//    int n_epoch = 500;		// how many times should weights be updated
//    int n_hidden = 5;		// how many neurons you want in the first layer

//    // test the implemented neural network
//    std::vector<double> scores = evaluate_network(csv_data, n_folds, l_rate, n_epoch, n_hidden);

//    // calculate the mean average of the scores across each cross validation
//    double mean = std::accumulate(scores.begin(), scores.end(), decltype(scores)::value_type(0)) / static_cast<double>(scores.size());

//    std::cout << "Mean accuracy: " << mean << std::endl;

//    return 0;
//}

//std::vector<double> evaluate_network(std::vector<std::vector<double>> dataset, int n_folds, double l_rate, int n_epoch, int n_hidden) {

//    /* Split dataset into k folds */

//    std::vector<std::vector<std::vector<double>>> dataset_splits;
//    // initialize prng
//    std::srand(static_cast<unsigned int>(std::time(nullptr)));

//    std::vector<double> scores;

//    size_t fold_size = static_cast<unsigned int>(dataset.size() / n_folds);
//    for (int f = 0; f < n_folds; f++)
//    {
//        std::vector<std::vector<double>> fold;
//        while (fold.size() < fold_size) {
//            int n = rand() % dataset.size(); // get a random index

//            // add the chosen element to the fold and remove it from the dataset
//            std::swap(dataset[n], dataset.back());
//            fold.push_back(dataset.back());
//            dataset.pop_back();
//        }

//        dataset_splits.push_back(fold);
//    }

//    /* Iterate over folds */
//    // choose one as test and the rest as training sets
//    for (size_t i = 0; i < dataset_splits.size(); i++)
//    {
//        std::vector<std::vector<std::vector<double>>> train_sets = dataset_splits;
//        std::swap(train_sets[i], train_sets.back());
//        std::vector<std::vector<double>> test_set = train_sets.back();
//        train_sets.pop_back();

//        // merge the multiple train_sets into one train set
//        std::vector<std::vector<double>> train_set;
//        for (auto &s: train_sets)
//        {
//            for (auto& row : s) {
//                train_set.push_back(row);
//            }
//        }

//        // store the expected results
//        std::vector<int> expected;
//        for (auto& row: test_set)
//        {
//            expected.push_back(static_cast<int>(row.back()));
//            // just ensure that the actual result is not saved in the test data
//            row.back() = 42;
//        }

//        std::vector<int> predicted;

//        std::set<double> results;
//        for (const auto& r : train_set) {
//            results.insert(r.back());
//        }
//        int n_outputs = results.size();
//        int n_inputs = train_set[0].size() - 1;

//        /* Backpropagation with stochastic gradient descent */
//        Network* network = new Network();
//        network->initialize_network(n_inputs, n_hidden, n_outputs);
//        network->train(train_set, l_rate, n_epoch, n_outputs);

//        for (const auto& row: test_set)
//        {
//            predicted.push_back(network->predict(row));
//        }

//        scores.push_back(accuracy_metric(expected, predicted));
//    }

//    return scores;
//}

/*
*
*/
double accuracy_metric(std::vector<int> expect, std::vector<int> predict) {
    int correct = 0;

    for (size_t i = 0; i < predict.size(); i++)
    {
        if (predict[i] == expect[i]) {
            correct++;
        }
    }
    return static_cast<double>(correct * 100.0f / predict.size());
}

/*
* Load comma separated values from file and normalize the values
*/
std::vector<std::vector<double>> load_csv_data(std::string filename) {
    const std::regex comma(",");

    std::ifstream csv_file(filename);

    std::vector<std::vector<double>> data;

    std::string line;

    std::vector<double> mins;
    std::vector<double> maxs;
    bool first = true;

    while (csv_file && std::getline(csv_file, line)) {
        // split line by commas
        std::vector<std::string> srow{ std::sregex_token_iterator(line.begin(), line.end(), comma, -1), std::sregex_token_iterator() };
        // create double vector
        std::vector<double> row(srow.size());
        // transform the strings to doubles
        std::transform(srow.begin(), srow.end(), row.begin(), [](std::string const& val) {return std::stof(val); });

        // keep track of the min and max value for each column for subsequent normalization
        if (first) {
            mins = row;
            maxs = row;
            first = false;
        }
        else {
            for (size_t t=0; t < row.size(); t++)
            {
                if (row[t] > maxs[t]) {
                    maxs[t] = row[t];
                }
                else if (row[t] < mins[t]) {
                    mins[t] = row[t];
                }
            }
        }

        data.push_back(row);
    }

    // normalize values
    for (auto& vec : data) {
        // ignore the last column (the output)
        for (size_t i = 0; i < vec.size()-1; i++)
        {
            vec[i] = (vec[i] - mins[i]) / (maxs[i] - mins[i]);
        }
    }

    return data;
}


int main(int argc, char* argv[]) {
    std::cout << "NN with Backpropagation in C++" << std::endl;

    // define a set of trainings data
    // each row has two inputs and one result
    // the result is either one or zero (binary classfication)
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
        results.insert(r[r.size() - 1]);
    }
    int n_outputs = results.size();
    int n_inputs = traindata[0].size() - 1;

    // we can experiment with these values
    double learn_rate = 0.4;
    int epochs = 50;

    // initialize a network
    // layers variable consists of pairs: {number of neurons in the layer, activation function for that layer}
    std::vector<std::pair<int, int>> layers = {{5, 1}};
    Network* network = new Network();
    Factory* factory = new AFSigmoid();
    network->initialize_network(n_inputs, layers, n_outputs, factory);
//    network->display_human();

//    network->toString();
//    // train the network (forward propagation, backward propagation and weight updating)
    network->train(traindata, learn_rate, epochs, n_outputs);

//    network->toString();
//    // display the created network (in an understandable format) for visualization purposes
//     network->display_human();

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
