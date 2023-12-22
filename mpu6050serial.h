#ifndef MPU6050SERIAL_H
#define MPU6050SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <ModbusRtuMaster/modbusrtumaster.h>
class MPU6050Serial : public QObject
{
    Q_OBJECT
private:
    ModbusRtuMaster my_modbus;
    QTimer *timer;
    Q_PROPERTY(int angleZ READ getAngleZ WRITE setAngleZ NOTIFY angleZChanged FINAL)
private slots:
    void updateModbus();
public:
    explicit MPU6050Serial(QObject *parent = nullptr);
    void begin();
    void readFromModbus();
    int angleZ=0;

    int getAngleZ() const;
    void setAngleZ(int newAngleZ);

signals:

    void angleZChanged();
};

#endif // MPU6050SERIAL_H
