#include "modbusrtumaster.h"

void ModbusRtuMaster::onTimerTimeout()
{
    uint16_t data[20]={0};
    readHoldingRegister(1,0,20,data);
    int16_t signedValue;
    signedValue=static_cast<int16_t>(data[14]);
    qDebug()<<"data: "<<signedValue;
}

ModbusRtuMaster::ModbusRtuMaster(QObject *parent)
    : QObject{parent}
{

//  timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &ModbusRtuMaster::onTimerTimeout);
//    timer->setInterval(10);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM6");
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
// timer->start();
}

void ModbusRtuMaster::disconnectDevice()
{
    modbusMaster.disconnectDevice();
 serialPort.close();
}

void ModbusRtuMaster::readHoldingRegister(uint8_t slaveID, uint16_t offset, uint8_t qty, uint16_t *data)
{
 QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, offset, qty);
 readUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);


 if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        // Chờ đợi phản hồi từ thiết bị Modbus RTU
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            // Đọc dữ liệu thành công
            const QModbusDataUnit result = reply->result();
//            int16_t hihi=result.value(14);
//            qDebug()<<"value: "<<hihi;
//            qDebug() << "Dữ liệu đọc được từ thiết bị Modbus RTU ID 1:" << result.value(1);
                for(int i=0;i<(int)result.valueCount();i++){
                data[i]=result.value(i);
            }

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
