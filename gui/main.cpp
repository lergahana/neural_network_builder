#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <QObject>
#include <QQmlContext>
#include "menu.h"
#include <QQuickStyle>
#include <QuickQanava>
#include <../QuickQanava/samples/style/custom.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);

    QQuickStyle::setStyle("Material");

    QuickQanava::initialize(&engine);

    QQmlContext* context = engine.rootContext();
    //context->setContextProperty("_node", &node);

    MenuObject menu = MenuObject();

    engine.setInitialProperties({
        { "_menu", QVariant::fromValue(&menu) },
    });



    engine.loadFromModule("zadnji", "Main");

    return app.exec();
}
