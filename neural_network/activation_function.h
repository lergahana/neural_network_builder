#ifndef ACTIVATION_FUNCTION_H
#define ACTIVATION_FUNCTION_H

#include <cmath>
#include <iostream>

class ActivationFunction {

public:
    virtual double activate(double x)=0;
    virtual double activateDerivative(double x)=0;
};


// Add more activation functions as needed
class Sigmoid : public ActivationFunction {

public:
    double activate(double x) override;
    double activateDerivative(double x) override;

};


#endif // ACTIVATION_FUNCTION_H
