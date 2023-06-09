#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class MenuObject : public QObject
{
    QML_ELEMENT
    Q_OBJECT

    Q_PROPERTY(int layers READ layers WRITE setLayers NOTIFY layersChanged)
    Q_PROPERTY(std::vector<int> neurons READ neurons WRITE setNeurons NOTIFY neuronsChanged)
    Q_PROPERTY(std::vector<int> functions READ functions WRITE setFunctions NOTIFY functionsChanged)

public:
    MenuObject(int n = 1, QObject* parent=nullptr);

    int layers() const;
    std::vector<int> neurons() const;
    std::vector<int> functions() const;

public slots:
    void setLayers(int n);
    void setNeurons(std::vector<int>);
    void setFunctions(std::vector<int>);
    void setLayerNeurons(int l, int n);
    void setLayerFunction(int l, int n);

signals:
    void layersChanged(int);
    void neuronsChanged(std::vector<int>);
    void functionsChanged(std::vector<int>);

private:
    int m_layers=1;
    std::vector<int> m_neurons;
    std::vector<int> m_functions;

};

#endif // MENU_H
