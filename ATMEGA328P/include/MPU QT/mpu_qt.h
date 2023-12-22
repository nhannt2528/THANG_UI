#include "Arduino.h"
#include <ModbusRTU.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
ModbusRTU mb;
void appInit()
{
    Serial.begin(9600);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    mb.begin(&Serial);
    mb.slave(1);
    mb.addHreg(0, 0, 20);
}
void appRun()
{

    static unsigned long preTime = millis();
    if (millis() - preTime > 10)
    {
        mpu6050.update();
        preTime = millis();
    }
    mb.Hreg(0, mpu6050.getTemp() * 10);
    mb.Hreg(1, mpu6050.getAccX());
    mb.Hreg(2, mpu6050.getAccY());
    mb.Hreg(3, mpu6050.getAccZ());
    mb.Hreg(4, mpu6050.getGyroX());
    mb.Hreg(5, mpu6050.getGyroY());
    mb.Hreg(6, mpu6050.getGyroZ());

    mb.Hreg(7, mpu6050.getAccAngleX());
    mb.Hreg(8, mpu6050.getAccAngleY());

    mb.Hreg(9, mpu6050.getGyroAngleX());
    mb.Hreg(10, mpu6050.getGyroAngleY());
    mb.Hreg(11, mpu6050.getGyroAngleZ());

    mb.Hreg(12, mpu6050.getAngleX());
    mb.Hreg(13, mpu6050.getAngleY());
    double z = mpu6050.getAngleZ();
    mb.Hreg(14, mpu6050.getAngleZ());
    mb.task();
    yield();
}