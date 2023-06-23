#ifndef CUSTOM_NODE_H
#define CUSTOM_NODE_H

#include <QQuickItem>
#include <QuickQanava>

class CustomNodePurple : public qan::Node
{
    Q_OBJECT

public:
    explicit CustomNodePurple(QObject* parent=nullptr) : qan::Node{parent} { }
    virtual ~CustomNodePurple() override = default;
    CustomNodePurple( const CustomNodePurple& ) = delete;

public:
    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;
    static  qan::NodeStyle* style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomNodePurple)

class CustomNodeBlue : public qan::Node
{
    Q_OBJECT

public:
    explicit CustomNodeBlue(QObject* parent=nullptr) : qan::Node{parent} { }
    virtual ~CustomNodeBlue() override = default;
    CustomNodeBlue( const CustomNodeBlue& ) = delete;

public:
    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;
    static  qan::NodeStyle* style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomNodeBlue)


#endif // CUSTOM_NODE_H
