#include "modbusrtumaster.h"

void ModbusRtuMaster::onTimerTimeout()
{
//    connectDevice();
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0x00, 1);
    readUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);
    readUnit.setStartAddress(0x00);
    readUnit.setValueCount(1);


    if (auto *reply = modbusMaster.sendReadRequest(readUnit, 1)) {
        // Chờ đợi phản hồi từ thiết bị Modbus RTU
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        // Kiểm tra kết quả
        if (reply->error() == QModbusDevice::NoError) {
            // Đọc dữ liệu thành công
             const QModbusDataUnit result = reply->result();
            qDebug() << "Dữ liệu đọc được từ thiết bị Modbus RTU ID 1:" << result.values();
        } else {
            // Đọc dữ liệu không thành công
            qDebug() << "Lỗi khi đọc dữ liệu từ thiết bị Modbus RTU ID 1:" << reply->errorString();
        }

        // Giải phóng bộ nhớ
        reply->deleteLater();
    } else {
        qDebug() << "Không thể gửi yêu cầu đọc dữ liệu đến thiết bị Modbus RTU";
    }
}

ModbusRtuMaster::ModbusRtuMaster(QObject *parent)
    : QObject{parent}
{

  timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ModbusRtuMaster::onTimerTimeout);
    timer->setInterval(10);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM1");
    modbusMaster.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    modbusMaster.setTimeout(1000);
}


void ModbusRtuMaster::connectDevice()
{

//    if (!serialPort.open(QIODevice::ReadWrite)) {
//        qDebug() << "Không thể mở cổng COM";
//        return;
//    }

    if (!modbusMaster.connectDevice()) {
        qDebug() << "Không thể kết nối với thiết bị Modbus RTU";
//        return;
    }
    else{
        qDebug()<<"connected modbus";

    }
 timer->start();
}

void ModbusRtuMaster::disconnectDevice()
{
    modbusMaster.disconnectDevice();
    serialPort.close();
}
