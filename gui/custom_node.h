#ifndef CUSTOM_NODE_H
#define CUSTOM_NODE_H

#include <QQuickItem>
#include <QuickQanava>

class CustomRoundNode : public qan::Node
{
    Q_OBJECT
public:
    explicit CustomRoundNode(QObject* parent=nullptr) : qan::Node{parent} { }
    virtual ~CustomRoundNode() override = default;
    CustomRoundNode( const CustomRoundNode& ) = delete;

public:
    static  QQmlComponent*  delegate(QQmlEngine& engine) noexcept;
    static  qan::NodeStyle* style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomRoundNode)


#endif // CUSTOM_NODE_H
