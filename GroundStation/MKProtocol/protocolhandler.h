#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H





class MKProtocol : public QObject
{
    Q_OBJECT
public:
    MKProtocol();

    /* Constructors for Serial as comm interface */
    MKProtocol(const QString &portName);
    MKProtocol(PortSettings SerialSetting, const QString &portName);

    void RequestData(char Origin, char Destiny, QByteArray reqData);
    void RequestData(ParameterRequest Setting);
    void configInterface(PortSettings SerialSetting, const QString &portName);
    void configInterface(const QString &portName);
    void checkPackages();
    bool OpenInterface();
    void CloseInterface();
    bool OpenCloseInterface();


private:
    QByteArray Decode64(QByteArray inputBuffer);
    QByteArray Encode64(QByteArray inputBuffer);
    quint16 CalcCRC(QByteArray DataBuffer);

    void PrepareSendPackage(char Origin, char Destiny, QByteArray reqData);
    bool isUartModule(char newModule);
    QByteArray getRequestUartRedirect(char newUart);
    void setUartModule(char newModule);
    char getActualAddress();


    /* Communication interface */
    /* Serial comm interface */
    //SerialHandler *heliComm;
    ZigBeeProtocolHandler *heliComm;

    QByteArray incomingData;

    QByteArray ReqModule[4];
    char actualUART;


private slots:
    void handleBuffer(QByteArray Data);

signals:
    void dataReceived(char,char,QByteArray);
};

#endif // PROTOCOLHANDLER_H
