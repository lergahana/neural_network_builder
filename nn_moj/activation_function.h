#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <vector>
#include <iostream>

class ActivationFunction {

public:
    ActivationFunction(int m_function);

    ~ActivationFunction();

//    virtual double activate(double x)=0;
//    virtual double activateDerivative(double x)=0;

    // Sigmoid activation function
    double sigmoid(double x);

    // ReLU activation function
    double relu(double x);

    // Leaky ReLU activation function
    double leaky_relu(double x, double alpha);

    // Tanh activation function
    double tanh(double x);

    // Softmax activation function
    std::vector<double> softmax(std::vector<double> x);

    // Derivatives of functions
    double der_sigmoid(double x);
    double der_relu(double x);
    double der_leaky_relu(double x, double alpha);
    double der_tanh(double x);
    //std::vector<double> der_softmax(std::vector<double> x);


private:
    int m_function;

};

// Add more activation functions as needed
class Sigmoid : public ActivationFunction {

public:
    Sigmoid();
    double activate(double x);
    double activateDerivative(double x);

};

// Abstract factory class
class Factory {
public:
    ActivationFunction* createFunction() {
        return new ActivationFunction(1);
    };
};

// Concrete factory class
class AFSigmoid : public Factory {
public:
//    ActivationFunction* createFunction() override {
//        std::cout << "sigmoid napravljen" << std::endl;
//        return new Sigmoid();
//    }
};

#endif // ACTIVATION_FUNCTIONS_H

//#ifndef ACTIVATION_FUNCTION_H
//#define ACTIVATION_FUNCTION_H

//#include <cmath>
//#include <iostream>

//class ActivationFunction {

//public:
//    virtual double activate(double x)=0;
//    virtual double activateDerivative(double x)=0;
//};


//// Add more activation functions as needed
//class Sigmoid : public ActivationFunction {

//public:
//    double activate(double x) override;
//    double activateDerivative(double x) override;

//};

//// Abstract factory class
//class Factory {
//public:
//    ActivationFunction* createFunction() {
//        return new Sigmoid();
//    };
//};

//// Concrete factory class
//class AFSigmoid : public Factory {
//public:
////    ActivationFunction* createFunction() override {
////        std::cout << "sigmoid napravljen" << std::endl;
////        return new Sigmoid();
////    }
//};


//#endif // ACTIVATION_FUNCTION_H

