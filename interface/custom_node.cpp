#include <QQmlEngine>
#include <QQmlComponent>
#include <QuickQanava>
#include <QQuickStyle>

#include "custom_node.h"

QQmlComponent*  CustomNodePurple::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   customRoundNode_delegate;
    if ( !customRoundNode_delegate )
        customRoundNode_delegate = std::make_unique<QQmlComponent>(&engine, ":/CustomNodePurple.qml");
    return customRoundNode_delegate.get();
}

qan::NodeStyle* CustomNodePurple::style(QObject* parent) noexcept
{
    Q_UNUSED(parent)
    static std::unique_ptr<qan::NodeStyle>  customRoundNode_style;
    if ( !customRoundNode_style ) {
        customRoundNode_style = std::make_unique<qan::NodeStyle>();
        customRoundNode_style->setBackColor(QColor(103, 58, 183));
    }
    return customRoundNode_style.get();
}

QQmlComponent*  CustomNodeBlue::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   customRoundNode_delegate;
    if ( !customRoundNode_delegate )
        customRoundNode_delegate = std::make_unique<QQmlComponent>(&engine, ":/CustomNodeBlue.qml");
    return customRoundNode_delegate.get();
}

qan::NodeStyle* CustomNodeBlue::style(QObject* parent) noexcept
{
    Q_UNUSED(parent)
    static std::unique_ptr<qan::NodeStyle>  customRoundNode_style;
    if ( !customRoundNode_style ) {
        customRoundNode_style = std::make_unique<qan::NodeStyle>();
        customRoundNode_style->setBackColor(QColor(156, 39, 176));
    }
    return customRoundNode_style.get();
}
