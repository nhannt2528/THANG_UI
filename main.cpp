#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//#include "ModbusRtuMaster/modbusrtumaster.h"
//ModbusRtuMaster *rtu=new ModbusRtuMaster();
#include "mpu6050serial.h"
MPU6050Serial *my_mpu=new MPU6050Serial();

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
//    rtu->connectDevice();
    context->setContextProperty("my_mpu",my_mpu);
    my_mpu->begin();
    return app.exec();
}
