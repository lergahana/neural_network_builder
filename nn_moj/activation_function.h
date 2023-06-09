
#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <vector>

class ActivationFunction {
public:
    ActivationFunction(int m_function);

    ~ActivationFunction();

    // Sigmoid activation function
    float sigmoid(float x);

    // ReLU activation function
    float relu(float x);

    // Leaky ReLU activation function
    float leaky_relu(float x, float alpha);

    // Tanh activation function
    float tanh(float x);

    // Softmax activation function
    std::vector<float> softmax(std::vector<float> x);

    // Derivatives of functions
    float der_sigmoid(float x);
    float der_relu(float x);
    float der_leaky_relu(float x, float alpha);
    float der_tanh(float x);
    //std::vector<float> der_softmax(std::vector<float> x);


private:
    int m_function;

};

#endif // ACTIVATION_FUNCTIONS_H
