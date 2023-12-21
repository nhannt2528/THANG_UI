#ifndef MODBUSRTUMASTER_H
#define MODBUSRTUMASTER_H

#include <QObject>
#include <QCoreApplication>
#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QModbusRtuSerialMaster>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>
class ModbusRtuMaster : public QObject
{
    Q_OBJECT
private:
    QSerialPort serialPort;
    QModbusRtuSerialMaster modbusMaster;
    QTimer *timer;
private slots:
    void onTimerTimeout();
public:
    explicit ModbusRtuMaster(QObject *parent = nullptr);
    void connectDevice();
    void disconnectDevice();


signals:


};

#endif // MODBUSRTUMASTER_H
