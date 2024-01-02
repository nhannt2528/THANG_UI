#include "mpu6050serial.h"

void MPU6050Serial::updateModbus()
{
    uint16_t data_reg[20]={0};
    my_modbus.readHoldingRegister(1,0,20,data_reg);
    int16_t angleZ;
    angleZ=static_cast<uint16_t>(data_reg[14]);
    angleZ=angleZ%360;
    if(angleZ<0){
        angleZ=360-abs(angleZ);
    }
    setAngleZ(angleZ);
//    qDebug()<<"angle_z: "<<angleZ;
}

MPU6050Serial::MPU6050Serial(QObject *parent)
    : QObject{parent}
{
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MPU6050Serial::updateModbus);
    timer->setInterval(10);
}
void MPU6050Serial::begin()
{
    my_modbus.connectDevice();
    timer->start();
}

int MPU6050Serial::getAngleZ() const
{
    return angleZ;
}

void MPU6050Serial::setAngleZ(int newAngleZ)
{
    if (angleZ == newAngleZ)
        return;
    angleZ = newAngleZ;
    emit angleZChanged();
}

