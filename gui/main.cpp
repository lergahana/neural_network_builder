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

    qmlRegisterType<NetworkBuilder>("NetworkBuilder", 1, 1, "NetworkBuilder");

    QQuickStyle::setStyle("Material");

    QuickQanava::initialize(&engine);

    QQmlContext* context = engine.rootContext();
    //context->setContextProperty("_node", &node);



    std::vector<std::vector<double>> traindata {
        {2.7810836,		2.550537003,	0},
        {1.465489372,	2.362125076,	0},
        {3.396561688,	4.400293529,	0},
        {6.922596716,	1.77106367,		1},
        {8.675418651,	-0.242068655,	1},
        {7.673756466,	3.508563011,	1}
    };

    std::vector<std::vector<double>> testdata {
        {1.38807019,	1.850220317,	0},
        {3.06407232,	3.005305973,	0},
        {7.627531214,	2.759262235,	1},
        {5.332441248,	2.088626775,	1},
    };

    // binary classification
    std::set<double> results;
    for (const auto& r : traindata) {
        results.insert(r.back());
    }
    int n_outputs = results.size();
    int n_inputs = traindata[0].size() - 1;

    // we can experiment with these values
    double learn_rate = 0.4;
    int epochs = 50;



    NetworkBuilder network_builder = NetworkBuilder(2, 2);
    //context->setContextProperty("_menu", &network_builder);
    network_builder.traindata = traindata;
    network_builder.epochs = epochs;
    network_builder.learn_rate = learn_rate;
    network_builder.n_outputs = n_outputs;

    engine.setInitialProperties({
        { "_menu", QVariant::fromValue(&network_builder) }

    });

    engine.loadFromModule("zadnji", "Main");

    QObject* rootObject = engine.rootObjects().value(0);
    QObject* trainButton = rootObject->findChild<QObject*>("startTraining");
    QObject* outputPane = rootObject->findChild<QObject*>("networkOutput");

//    if (outputPane) {
//        QObject::connect(&network_builder, &NetworkBuilder::endTraining, outputPane, [outputPane]() {
//            outputPane->children()[0]->setProperty("text", "nesto se zekim");
//        });
//        qDebug() << outputPane->children()[0]->property("text").toString();
//    }



//    network_builder.setOutputText("iz mejna");
//    QString s = "nesto";
//    outputPane->children()[0]->setProperty("text", s);
//    qDebug() << outputPane->children()[0]->property("text").toString();

    return app.exec();
}
