#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <QObject>
#include <QQmlContext>
#include "menu.h"
#include <QQuickStyle>
#include <QuickQanava>
#include <../QuickQanava/samples/style/custom.h>
#include "network.h"


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
    menu.n_inputs = 5;
    menu.n_outputs = 2;

    engine.setInitialProperties({
        { "_menu", QVariant::fromValue(&menu) }

    });

    engine.loadFromModule("zadnji", "Main");

    QObject* rootObject = engine.rootObjects().value(0);
    QObject* trainButton = rootObject->findChild<QObject*>("startTraining");
    QObject* outputPane = rootObject->findChild<QObject*>("networkOutput");

    if (trainButton){
        std::cout << "Nasli smo button " << trainButton << std::endl;

        QObject::connect(trainButton, SIGNAL(clicked()),
                         &menu, SLOT(handleButtonClick()));

        std::cout << "Zavrsio loop" << std::endl;
        menu.network->toString();
        outputPane->children()[0]->setProperty("text", "New text value");
    }

    return app.exec();
}
