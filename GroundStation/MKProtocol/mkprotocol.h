#ifndef MKPROTOCOL_H
#define MKPROTOCOL_H

#include "MKProtocol_global.h"
#include <QObject>
#include <QByteArray>
#include <QString>
#include <windows.h>
#include "qextserialport.h"
//#include "serialhandler.h"
#include "zigbeeprotocol.h"
#include "modules/HelicopterDefs.h"
#include "parameterrequest.h"

#define WAIT_REDIRECT_TIME 50



class MKPROTOCOLSHARED_EXPORT  MKProtocol: public QObject
{
    Q_OBJECT
public:
    MKProtocol();


    void RequestData(char Origin, char Destiny, QByteArray reqData);
    void RequestData(ParameterRequest Setting);    
    void checkPackages();   
    void resetUARTModule();


private:
    QByteArray Decode64(QByteArray inputBuffer);
    QByteArray Encode64(QByteArray inputBuffer);
    quint16 CalcCRC(QByteArray DataBuffer);

    void PrepareSendPackage(char Origin, char Destiny, QByteArray reqData);
    bool isUartModule(char newModule);
    QByteArray getRequestUartRedirect(char newUart);
    void setUartModule(char newModule);
    char getActualAddress();
    void sendBuffer(QByteArray data);


    /* Communication interface */
    /* Serial comm interface */
    //SerialHandler *heliComm;
    //ZigBeeProtocol *heliComm;

    QByteArray incomingData;

    QByteArray ReqModule[4];
    char actualUART;


public slots:
    void handleBuffer(QByteArray Data);    

signals:
    void dataReceived(char,char,QByteArray);
    void bufferReady(QByteArray);
    void terminalData(QByteArray);

};

#endif // MKPROTOCOL_H
