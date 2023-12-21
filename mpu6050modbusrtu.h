#ifndef MPU6050MODBUSRTU_H
#define MPU6050MODBUSRTU_H

#include <QObject>
#include <QModbusDevice>
#include <QModbusRtuSerialMaster>
#include <QSerialPort>
#include <QModbusDataUnit>
#include <QDebug>

class mpu6050ModbusRtu : public QObject
{
    Q_OBJECT
private:
    QSerialPort serialPort;
     QModbusRtuSerialMaster modbusMaster;
public:
    explicit mpu6050ModbusRtu(QObject *parent = nullptr);
    void readFromModbus();

signals:

};

#endif // MPU6050MODBUSRTU_H
