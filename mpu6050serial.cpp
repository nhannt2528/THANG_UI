#include "mpu6050serial.h"

MPU6050Serial::MPU6050Serial(QObject *parent)
    : QObject{parent}
{
    m_serial=new QSerialPort();
    m_serial->setPortName("/dev/ttyUSB1");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

}

void MPU6050Serial::begin()
{
    if (m_serial->open(QIODevice::ReadOnly)) {
        qDebug() << "Connected to" << m_serial->portName();

        // Đọc dữ liệu từ cổng COM khi có sẵn
        QObject::connect(m_serial, &QSerialPort::readyRead, [&]() {
            QByteArray data = m_serial->readLine();
            qDebug() << "Data received:" << data;
        });
        QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [&]() {
            // Empty, chỉ để chạy vòng lặp chính của ứng dụng
        });
        timer.start(0);
    } else {
        qDebug() << "Failed to connect to" << m_serial->portName();
    }
}
