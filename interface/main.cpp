#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include <QObject>
#include <QQmlContext>
#include "network_builder.h"
#include <QQuickStyle>
#include <QuickQanava>
#include <../QuickQanava/samples/style/custom.h>

#include <set>



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


    std::vector<std::vector<double>> data {
        {2.7810836,     2.550537003,    0},
        {1.465489372,   2.362125076,    0},
        {3.396561688,   4.400293529,    0},
        {6.922596716,   1.77106367,     1},
        {8.675418651,   -0.242068655,   1},
        {7.673756466,   3.508563011,    1},
        {1.38807019,	1.850220317,	0},
        {3.06407232,	3.005305973,	0},
        {7.627531214,	2.759262235,	1},
        {5.332441248,	2.088626775,	1},
    };


    // binary classification
    std::set<float> results;
    for (const auto& r : data) {
        results.insert(r[r.size() - 1]);
    }
    int n_outputs = results.size();
    int n_inputs = data[0].size() - 1;

    // we can experiment with these values
    double learnRate = 0.4;
    int epochs = 50;



    NetworkBuilder* network_builder = new NetworkBuilder(&data, n_inputs, n_outputs, epochs, learnRate);

    engine.setInitialProperties({
        { "_menu", QVariant::fromValue(network_builder) }

    });

    engine.loadFromModule("zadnji", "Main");

    QObject* rootObject = engine.rootObjects().value(0);
    QObject* trainButton = rootObject->findChild<QObject*>("startTraining");
    QObject* outputPane = rootObject->findChild<QObject*>("networkOutput");
    QObject* outputPaneText = outputPane->findChild<QObject*>("networkOutputText");
    QObject* testPane = rootObject->findChild<QObject*>("testOutput");
    QObject* testText = testPane->findChild<QObject*>("testText");


    QObject::connect(network_builder, &NetworkBuilder::endTraining, outputPaneText, [&]() {
        bool changed = outputPaneText->setProperty("text", network_builder->outputText());
    });

    QObject::connect(network_builder, &NetworkBuilder::endTest, testText, [&]() {
        bool changed = testPane->setProperty("text", network_builder->testText());
    });

    return app.exec();
}
