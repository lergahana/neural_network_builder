
#ifndef CUSTOM_EDGE_H
#define CUSTOM_EDGE_H

#include <QObject>
#include <QQmlEngine>
#include <QuickQanava>

#include "custom_node.h"

class CustomEdge : public qan::Edge
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit CustomEdge(QObject* parent = nullptr) : qan::Edge{parent} { }
    virtual ~CustomEdge() override = default;
    CustomEdge(const CustomEdge&) = delete;

public:
    static  QQmlComponent*  delegate(QQmlEngine& engine, QObject* parent = nullptr) noexcept;
    static  qan::EdgeStyle* style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomEdge)

#endif // CUSTOM_EDGE_H
