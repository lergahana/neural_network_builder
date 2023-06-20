#include <QQmlEngine>
#include <QQmlComponent>
#include <QuickQanava>

#include "custom_node.h"

QQmlComponent*  CustomRoundNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   customRoundNode_delegate;
    if ( !customRoundNode_delegate )
        customRoundNode_delegate = std::make_unique<QQmlComponent>(&engine, "../../zadnji/gui/CustomNodeHana.qml");
    return customRoundNode_delegate.get();
}

qan::NodeStyle* CustomRoundNode::style(QObject* parent) noexcept
{
    Q_UNUSED(parent)
    static std::unique_ptr<qan::NodeStyle>  customRoundNode_style;
    if ( !customRoundNode_style ) {
        customRoundNode_style = std::make_unique<qan::NodeStyle>();
        customRoundNode_style->setBackColor(QColor("#0770ff"));
    }
    return customRoundNode_style.get();
}
