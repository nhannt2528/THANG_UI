#ifndef MPU6050SERIAL_H
#define MPU6050SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
class MPU6050Serial : public QObject
{
    Q_OBJECT
private:
    QSerialPort *m_serial;

public:
    explicit MPU6050Serial(QObject *parent = nullptr);
    void begin();
    void readFromModbus();
signals:

};

#endif // MPU6050SERIAL_H
