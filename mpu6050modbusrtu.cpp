#include "mpu6050modbusrtu.h"

mpu6050ModbusRtu::mpu6050ModbusRtu(QObject *parent)
    : QObject{parent}
{
    serialPort.setPortName("COM1");
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
}

void mpu6050ModbusRtu::readFromModbus()
{
    if (!serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Không thể mở cổng COM";
        return;
    }

    // Khởi tạo và cấu hình QModbusRtuSerialMaster
    modbusMaster.setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM1");
    modbusMaster.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    modbusMaster.setTimeout(1000);

    // Kết nối với thiết bị Modbus RTU
    if (!modbusMaster.connectDevice()) {
        qDebug() << "Không thể kết nối với thiết bị Modbus RTU";
        return;
    }

    // Tạo yêu cầu đọc dữ liệu từ địa chỉ 0x00 của thiết bị Modbus RTU
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0x00, 1);
    if (auto *reply = modbusMaster.sendReadRequest(readUnit, 1)) {
        // Chờ đợi phản hồi từ thiết bị Modbus RTU
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        // Kiểm tra kết quả
        if (reply->error() == QModbusDevice::NoError) {
            // Đọc dữ liệu thành công
            qDebug() << "Dữ liệu đọc được từ thiết bị Modbus RTU:" << reply->resultAt(0);
        } else {
            // Đọc dữ liệu không thành công
            qDebug() << "Lỗi khi đọc dữ liệu từ thiết bị Modbus RTU:" << reply->errorString();
        }

        // Giải phóng bộ nhớ
        reply->deleteLater();
    } else {
        qDebug() << "Không thể gửi yêu cầu đọc dữ liệu đến thiết bị Modbus RTU";
    }

    // Ngắt kết nối với thiết bị Modbus RTU và đóng cổng COM
    modbusMaster.disconnectDevice();
    serialPort.close();
}
