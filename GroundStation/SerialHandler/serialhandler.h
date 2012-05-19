#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QByteArray>
#include <qextserialport.h>
#include "SerialHandler_global.h"

#define RET_OK true

#define BAUD_DEFAULT        BAUD57600
#define FLOW_DEFAULT        FLOW_OFF
#define PARITY_DEFAULT      PAR_NONE
#define DATABITS_DEFAULT    DATA_8
#define STOPBIT_DEFAULT     STOP_2


class SERIALHANDLERSHARED_EXPORT SerialHandler : public QObject
{
Q_OBJECT
public:
    SerialHandler();
    SerialHandler(const QString & portName);
    SerialHandler(PortSettings portSet, const QString & portName);
    void ConfigPort(PortSettings portSet, const QString & portName);
    void ConfigPort(const QString & portName);
    bool OpenClosePort();
    bool OpenPort();
    void ClosePort();
    bool isOpen();

    void sendBuffer(QByteArray Data);

private:
    QextSerialPort *port;

private slots:
    void handleBufferIn();

signals:
    void dataReceived(QByteArray Data);
};

#endif // SERIALHANDLER_H
