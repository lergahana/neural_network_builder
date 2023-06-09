#include "menu.h"
#include <QDebug>

MenuObject::MenuObject(int n, QObject* parent) : QObject(parent),
                        m_layers(n),
                        m_neurons(std::vector<int> (10, 1)),
                        m_functions(std::vector<int> (10, 1))
                        {}

int MenuObject::layers() const { return m_layers; }

void MenuObject::setLayers(int n)
{
    if(m_layers == n)
        return;

    m_layers = n;
    m_neurons.resize(n);
    m_functions.resize(n);
    emit layersChanged(m_layers);
}

std::vector<int> MenuObject::neurons() const { return m_neurons; }

void MenuObject::setNeurons(std::vector<int> neurons)
{
    emit neuronsChanged(neurons);
}

void MenuObject::setLayerNeurons(int layer, int num_neurons)
{
    if(m_neurons.at(layer) == num_neurons)
        return;

    m_neurons.at(layer) = num_neurons;
//    for (int var = 0; var < m_neurons.size(); ++var) {
//        qDebug() << "Layer neurons " << var+1 << ": " << m_neurons.at(var);
//    }
    setNeurons(m_neurons);
}


std::vector<int> MenuObject::functions() const { return m_functions; }

void MenuObject::setFunctions(std::vector<int> functions)
{
    emit functionsChanged(functions);
}

void MenuObject::setLayerFunction(int layer, int num)
{
    if(m_functions.at(layer) == num)
        return;

    m_functions.at(layer) = num;
//    for (int var = 0; var < m_functions.size(); ++var) {
//        qDebug() << "Layer function " << var+1 << ": " << m_functions.at(var);
//    }

    setFunctions(m_functions);
}

