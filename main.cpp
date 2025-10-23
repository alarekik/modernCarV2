#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "canhandler.h"
#include "cameracontroller.h"
#include "uarthandler.h"
#include <QQmlContext>
#include "uartbcg.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    //---------
    CanHandler canbus;
    CameraController cameraController;
    uarthandler uartport;
    uartBCG bcg;
    //----------------
    QQmlApplicationEngine engine;
    //--------------------------
    //-uart bcg-------
    QQmlContext * rootbcg =engine.rootContext();
    rootbcg->setContextProperty("bcg", &bcg);
    //-------------------
    QQmlContext * rootcamera =engine.rootContext();
    rootcamera->setContextProperty("cameraController", &cameraController);
    //----------------
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("canbus", &canbus );
    //------------------------------
    QQmlContext * root =engine.rootContext();
    root->setContextProperty("uartport",&uartport);
    //-------------------------------
    if (uartport.openPort()) {
        qCritical() << "BSP is  open ";
    }
    else {
        qCritical() << "BSP is not open ";
    }
    if (bcg.openPort()) {
        qDebug() << "  Port BCG open :" ;
    }else {
        qDebug() << "  Port not BCG open :" ;
    }
    qDebug()<<"dataBSP" <<uartport.lastMessage();
    qDebug()<<"dataBrahth" <<bcg.lastbreathValue();
    qDebug()<<"dataheart"  <<bcg.lastheartValue();
    //------------------
    canbus.connectToCanBus("can0");
    //----------this to ensure the connect run in GUI--------
    QMetaObject::invokeMethod(&canbus, "connectToCanBus", Qt::QueuedConnection,Q_ARG(QString, "can0"));
    //---------
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    //--------

    return app.exec();
}
