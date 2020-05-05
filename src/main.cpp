#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "core.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    Core core;
    QQmlApplicationEngine engine;

    if (QQmlContext*  pContext = engine.rootContext())
        pContext->setContextProperty("core", &core);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
