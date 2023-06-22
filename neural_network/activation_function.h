#ifndef ACTIVATION_FUNCTION_H
#define ACTIVATION_FUNCTION_H

#include <cmath>
#include <iostream>

class ActivationFunction {
protected:
    std::string m_name="";
public:
    virtual double activate(double x)=0;
    virtual double activateDerivative(double x)=0;

    std::string getName(){ return m_name; };

    static ActivationFunction* create(std::string functionName);
};


// Add more activation functions as needed
class Sigmoid : public ActivationFunction {
public:
    Sigmoid() { m_name = "sigmoid"; };
    double activate(double x) override;
    double activateDerivative(double x) override;
};


class Relu : public ActivationFunction {
public:
    Relu() { m_name = "relu"; };
    double activate(double x) override;
    double activateDerivative(double x) override;
};

class Tanh : public ActivationFunction {
public:
    Tanh() { m_name = "tanh"; };
    double activate(double x) override;
    double activateDerivative(double x) override;
};



#endif // ACTIVATION_FUNCTION_H
