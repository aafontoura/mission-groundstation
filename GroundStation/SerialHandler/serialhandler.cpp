#include "serialhandler.h"
#include <QByteArray>





SerialHandler::SerialHandler()
{

   connect(port, SIGNAL(readyRead()), this, SLOT(handleBufferIn()));

}


SerialHandler::SerialHandler(const QString &portName)
{
    this->port = new QextSerialPort(portName, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD_DEFAULT);
    port->setFlowControl(FLOW_DEFAULT);
    port->setParity(PARITY_DEFAULT);
    port->setDataBits(DATABITS_DEFAULT);
    port->setStopBits(STOPBIT_DEFAULT);
    connect(port, SIGNAL(readyRead()), this, SLOT(handleBufferIn()));

}

SerialHandler::SerialHandler(PortSettings portSet, const QString &portName)
{
    port->setPortName(portName);
    port->setBaudRate(portSet.BaudRate);
    port->setFlowControl(portSet.FlowControl);
    port->setParity(portSet.Parity);
    port->setDataBits(portSet.DataBits);
    port->setStopBits(portSet.StopBits);
    connect(port, SIGNAL(readyRead()), this, SLOT(handleBufferIn()));
}

void SerialHandler::ConfigPort(PortSettings portSet, const QString &portName)
{
    port->setPortName(portName);
    port->setBaudRate(portSet.BaudRate);
    port->setFlowControl(portSet.FlowControl);
    port->setParity(portSet.Parity);
    port->setDataBits(portSet.DataBits);
    port->setStopBits(portSet.StopBits);
}

void SerialHandler::ConfigPort(const QString &portName)
{
    port->setPortName(portName);
    port->setBaudRate(BAUD_DEFAULT);
    port->setFlowControl(FLOW_DEFAULT);
    port->setParity(PARITY_DEFAULT);
    port->setDataBits(DATABITS_DEFAULT);
    port->setStopBits(STOPBIT_DEFAULT);
}

bool SerialHandler::OpenClosePort()
{
    if (port->isOpen())
    {
        port->close();
        return RET_OK;
    }
    else
    {
        return(port->open(QextSerialPort::ReadWrite));
    }
}

bool SerialHandler::OpenPort()
{
    if (!port->isOpen())
    {
        return(port->open(QextSerialPort::ReadWrite));
    }
    else
        return RET_OK;
}


void SerialHandler::handleBufferIn()
{
    QByteArray bytes;
    int size = port->bytesAvailable();
    bytes.resize(size);
    port->read(bytes.data(), size);

    emit dataReceived(bytes);
}

void SerialHandler::sendBuffer(QByteArray Data)
{
    port->write(Data);
}

bool SerialHandler::isOpen()
{
    return port->isOpen();
}


