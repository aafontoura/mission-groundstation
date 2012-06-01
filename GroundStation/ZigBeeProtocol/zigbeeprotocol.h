#ifndef ZIGBEEPROTOCOL_H
#define ZIGBEEPROTOCOL_H

#include <QObject>
#include <QString>

#include "ZigBeeProtocol_global.h"
#include "serialhandler.h"
#include "zigBeeDefs.h"




class ZIGBEEPROTOCOLSHARED_EXPORT ZigBeeProtocol : public QObject
{
    Q_OBJECT
public:
    ZigBeeProtocol();
    ZigBeeProtocol(const QString &portName);
    ZigBeeProtocol(PortSettings SerialSetting, const QString &portName);
    void configInterface(PortSettings SerialSetting, const QString &portName);
    void configInterface(const QString &portName);
    void checkPackages();
    bool OpenInterface();
    void CloseInterface();
    bool OpenCloseInterface();
    bool isOpen();
    void sendBuffer(QByteArray Data, int address, int type);



private:

    typedef struct
    {
        char startByte;
        char length[2];
        char *data;
        char checksum;
    } __attribute__((packed)) zigBeeStruct;

    typedef struct
    {
        char atCommandId;
        char frameId;        
        quint32 addr64Msb;
        quint32 addr64Lsb;
        char addr16Msb;
        char addr16Lsb;
        char broadCastRadius;
        char commandOption;
        char *data;
    } __attribute__((packed)) zigBeeTransmitRequestStruct;

    typedef struct
    {
        char atCommandId;
        char frameId;
        char addr16Msb;
        char addr16Lsb;
        char commandOption;
        char *data;
    } __attribute__((packed)) zigBeeTx16RequestStruct;

    typedef struct
    {
        char atCommandId;
        char frameId;
        char command[2];
        char *parameterValue;
    } __attribute__((packed)) zigBeeAtCommandStruct;

    typedef struct
    {
        char atCommandId;
        char frameId;
        quint32 addr64Msb;
        quint32 addr64Lsb;
        char addr16Msb;
        char addr16Lsb;
        char commandOption;
        char commandName[2];
        char *commandData;
    } __attribute__((packed)) zigBeeRemoteAtRequestStruct;



    /* Communication interface */
    /* Serial comm interface */
    SerialHandler *serialComm;

    QByteArray incomingData;

    void PrepareSendPackage(char atCommandID, quint16 addrDestiny, QByteArray Data);
    bool checkByteCecksum(QByteArray data);
    void dataHandler(QByteArray data);

private slots:

    void handleBuffer(QByteArray Data);

signals:
    void dataReceived(QByteArray,int);


};

#endif // ZIGBEEPROTOCOL_H
