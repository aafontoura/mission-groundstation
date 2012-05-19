#include "MKProtocol.h"


MKProtocol::MKProtocol()
{
    /* Open a serial interface */
    heliComm = new ZigBeeMKProtocol();

    ReqModule[UART_FC_REQ].append(UART_FC);
    ReqModule[UART_NC_REQ].append(UART_NC);
    ReqModule[UART_NC_REQ].append(UART_FC);
    ReqModule[UART_MK3MAG_REQ].append(UART_MK3MAG);
    ReqModule[UART_MKGPS_REQ].append(UART_MKGPS);


    actualUART = UART_INIT;

    /* Event Configuration */
    connect(heliComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));
}

MKProtocol::MKProtocol(const QString &portName)
{
    /* Open a zigbee interface */
    heliComm = new ZigBeeProtocolHandler(portName);

    ReqModule[UART_FC_REQ].append(UART_FC);
    ReqModule[UART_NC_REQ].append(UART_NC);
    ReqModule[UART_NC_REQ].append(UART_FC);
    ReqModule[UART_MK3MAG_REQ].append(UART_MK3MAG);
    ReqModule[UART_MKGPS_REQ].append(UART_MKGPS);

    actualUART = UART_INIT;

    /* Event Configuration */
    connect(heliComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));
}

MKProtocol::MKProtocol(PortSettings SerialSetting, const QString &portName)
{
    /* Open a serial interface */
    heliComm = new ZigBeeProtocolHandler(SerialSetting,portName);

    /* Event Configuration */
    connect(heliComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));
}

/*********************************************************************************/
/* Name.........: Decode64                                                       */
/* Inputs.......: inputBuffer - Data encoded from the serial interface           */
/* Outputs......: QByteArray - Data decoded                                      */
/* Description..: Decode the data from the serial interface                      */
/*********************************************************************************/

QByteArray MKProtocol::Decode64(QByteArray inputBuffer)
{
    int length = inputBuffer.size();
    int indexOut = 0, indexIn = 0;
    QByteArray decodedData;

    /* Calculate the size of the output buffer decoded
      (for each 4 bytes will be 3 decoded) */
    decodedData.resize(3*inputBuffer.size()/4);

    /* Remove the 'default' value from data */
    for (int i = 0 ; i < inputBuffer.size() ; i++)
        inputBuffer[i] = inputBuffer[i] - INTERFACE_NULL_BYTE;


    /* Decode 64. Algorithm took from mikrokopter embedded code */
    while(3 <= length)
    {
        decodedData[indexOut++] = (inputBuffer[indexIn] << 2) | (inputBuffer[indexIn+DECODE_B] >> 4);
        decodedData[indexOut++] = ((inputBuffer[indexIn+DECODE_B] & 0x0F) << 4) | (inputBuffer[indexIn+DECODE_C] >> 2);
        decodedData[indexOut++] = ((inputBuffer[indexIn+DECODE_C] & 0x03) << 6) | inputBuffer[indexIn+DECODE_D];
        length -= 3;
        indexIn += 4;
    }

    return (decodedData);
}

/*********************************************************************************/
/* Name.........: Encode64                                                       */
/* Inputs.......: inputBuffer - Data to encode                                   */
/* Outputs......: QByteArray - Data encoded                                      */
/* Description..: Encode the data to send to the serial interface                */
/*********************************************************************************/
QByteArray MKProtocol::Encode64(QByteArray inputBuffer)
{
    int length = inputBuffer.size();
    int sizeOut = inputBuffer.size();
    int indexOut = 0, indexIn = 0;
    char a,b,c;
    QByteArray encodedData;
    //encodedData.insert(0,'h');

    /* Calculate the the size of the Encoded Data
      for each 3 bytes, will be 4 transmitted */
    if (0 < sizeOut)
    {
        sizeOut *= 4;
        sizeOut /= 3;
        sizeOut += (sizeOut % 4) ? (4 - sizeOut % 4) : 0;
    }
    encodedData.resize(sizeOut);

    while(0 < length)
    {
       a = (length--) ? inputBuffer[indexIn++] : 0;
       b = (length--) ? inputBuffer[indexIn++] : 0;
       c = (length--) ? inputBuffer[indexIn++] : 0;

       encodedData[indexOut++] = INTERFACE_NULL_BYTE + (a >> 2);
       encodedData[indexOut++] = INTERFACE_NULL_BYTE + (((a & 0x03) << 4) | ((b & 0xf0) >> 4));
       encodedData[indexOut++] = INTERFACE_NULL_BYTE + (((b & 0x0f) << 2) | ((c & 0xc0) >> 6));
       encodedData[indexOut++] = INTERFACE_NULL_BYTE + ( c & 0x3f);
       //encodedData[indexOut] = 'j';
       //encodedData.push_back('e');
       //encodedData.push_back('r');
    }

    return encodedData;

}


/*********************************************************************************/
/* Name.........: CalcCRC                                                        */
/* Inputs.......: DataBuffer                                                     */
/* Outputs......: CRC                                                            */
/* Description..: Calculate the CRC of a Buffer                                  */
/* CRC1 = '=' + tmpCRC / 64;                                                     */
/* CRC2 = '=' + tmpCRC % 64;                                                     */
/*********************************************************************************/
quint16 MKProtocol::CalcCRC(QByteArray DataBuffer)
{
    quint16 tmpCRC = 0;

    for(int i = 0 ; i < DataBuffer.size() ; i++)
    {
        tmpCRC += DataBuffer[i];
    }
    tmpCRC %= 4096;
    return tmpCRC;
}

/*********************************************************************************/
/* Name.........: PrepareSendPackage                                             */
/* Inputs.......: Origin - The data Requested                                    */
/*                Destiny - The destination of the Request                       */
/*                reqData - The data needed for the specific request             */
/* Outputs......: none                                                           */
/* Description..: Mount the Package within the mikrokopter protocol              */
/*********************************************************************************/
void MKProtocol::PrepareSendPackage(char Origin, char Destiny, QByteArray reqData)
{
    QByteArray sendBuffer, tempBuffer;
    int sizeOut = reqData.size();
    unsigned int CRC;

    /* Calculate the the size of the Encoded Data
      for each 3 bytes, will be 4 transmitted */
    if (0 < sizeOut)
    {
        sizeOut *= 4;
        sizeOut /= 3;
        sizeOut += (sizeOut % 4) ? (4 - sizeOut % 4) : 0;
        // sizeOut += 4 - sizeOut % 4;

        sendBuffer.resize(sizeOut + PAYLOAD_PACKAGE);

        tempBuffer = Encode64(reqData);
        sendBuffer.replace(3,tempBuffer.size(),tempBuffer);
    }
    else
        sendBuffer.resize(PAYLOAD_PACKAGE);


    sendBuffer[0] = START_PACKAGE;
    sendBuffer[1] = Destiny + ADDRESS_ADD_BYTE;
    sendBuffer[2] = Origin;


    CRC = CalcCRC(sendBuffer.left(sendBuffer.size()-3));
    sendBuffer[sendBuffer.size() - 2] = CRC % 64 + INTERFACE_NULL_BYTE;
    sendBuffer[sendBuffer.size() - 3] = CRC / 64 + INTERFACE_NULL_BYTE;
    sendBuffer[sendBuffer.size() - 1] = STOP_PACKAGE;

    heliComm->sendBuffer(sendBuffer);


}

bool MKProtocol::isUartModule(char newModule)
{
    return(newModule==(actualUART+1));
}

QByteArray MKProtocol::getRequestUartRedirect(char newUart)
{
    if ((MK3MAG_ADDRESS >= newUart) && (FC_ADDRESS <= newUart))
        return (ReqModule[newUart-1]);
    else
        return(0);
}



void MKProtocol::setUartModule(char newModule)
{
    actualUART = newModule-1;
}

char MKProtocol::getActualAddress()
{
    if (UART_INIT == actualUART)
        return(NC_ADDRESS);
    else
        return(actualUART+1);
}

/*********************************************************************************/
/* Name.........: RequestData                                                    */
/* Inputs.......: Origin - The data Requested                                    */
/*                Destiny - The destination of the Request                       */
/*                reqData - The data needed for the specific request             */
/* Outputs......: none                                                           */
/* Description..: Request Data from the target                                   */
/*********************************************************************************/
void MKProtocol::RequestData(char Origin, char Destiny, QByteArray reqData)
{
    char h = Destiny;
    if(!isUartModule(Destiny))
    {
        PrepareSendPackage(REDIRECT_UART_HEADER,getActualAddress(),getRequestUartRedirect(Destiny));
        this->setUartModule(Destiny);
    }

    for (int i = 0 ; i<10000000; i++)
     Destiny++;

    Destiny = h;


    PrepareSendPackage(Origin,Destiny,reqData);


}

void MKProtocol::RequestData(ParameterRequest Setting)
{
    // char h;
    if(!isUartModule(Setting.getDestDevice()))
    {
        if (Setting.getDestDevice() == NC_ADDRESS)
            heliComm->sendBuffer(getRequestUartRedirect(Setting.getDestDevice()));
        else
            PrepareSendPackage(REDIRECT_UART_HEADER,getActualAddress(),getRequestUartRedirect(Setting.getDestDevice()));
        this->setUartModule(Setting.getDestDevice());

        /* Works only with this delay */
        Sleep(100);
       // for (int i = 0 ; i<10000000; i++)
       //  h++;
    }





    PrepareSendPackage(Setting.getAttributeType(),Setting.getDestDevice(),
                       Setting.getRequestParameter());
}

/*********************************************************************************/
/* Name.........: handleBuffer                                                   */
/* Inputs.......: Data - Data received from the serial interface                 */
/* Outputs......: none                                                           */
/* Description..: Check if there is a new valid package from the Helicopter.     */
/*                Check the CRC of the the new package, decode it, and send it   */
/*********************************************************************************/
void MKProtocol::handleBuffer(QByteArray Data)
{
    /* push back the incoming data on the local buffer */
    incomingData.append(Data);

    /* Find the start byte of the protocol */
    int indexSearch = incomingData.indexOf(START_PACKAGE);
    int stopProtocolIndex = incomingData.indexOf(STOP_PACKAGE);
    //int expectedSize = PAYLOAD_PACKAGE + dataSizeRequested;
    quint16 CRC = 0;



    /* Check if there is a possible valid package (Start and Stop byte) */
    if ((0 <= indexSearch) && (stopProtocolIndex > indexSearch))
    {

        /* Ignore bytes */
        QByteArray incomingBuffer = incomingData.mid(indexSearch,stopProtocolIndex-indexSearch+1);

        /* Calculate CRC, ignoring the CRC sent and the stop BIT */
        CRC = CalcCRC(incomingBuffer.left(stopProtocolIndex-indexSearch-2));
        if (((int)incomingBuffer[incomingBuffer.size() - 2] == (CRC % 64 + INTERFACE_NULL_BYTE)) &&
            ((int)incomingBuffer[incomingBuffer.size() - 3] == (CRC / 64 + INTERFACE_NULL_BYTE)))
        {
            /* Flush Processed Data */
            incomingData = incomingData.right(incomingData.size()-stopProtocolIndex - 1);
            //waitingReply = false;
            emit dataReceived(incomingBuffer[1],incomingBuffer[2],Decode64(incomingBuffer.mid(3,incomingBuffer.size()-PAYLOAD_PACKAGE)));
        }
        else
        {
            /* Flush Data */
            incomingData = incomingData.right(incomingData.size()-stopProtocolIndex - 1);
            emit dataReceived(0,0,"Data Flushed\n");
        }


    }
    else
    {
        /* Flush Data */
        if (indexSearch < 0)
        {
            incomingData.clear();
            emit dataReceived(0,0,"Cleared\n");
        }
        else
        {
            if ((stopProtocolIndex >= 0) && (stopProtocolIndex < indexSearch))
                incomingData = incomingData.right(incomingData.size()-indexSearch);

            QByteArray index;
            QByteArray stop;

            index.setNum(indexSearch);
            stop.setNum(stopProtocolIndex);

            emit dataReceived(0,0,"Waiting: "+index + " - " + stop + "\n"+incomingData+"\n");
        }


    }


}


void MKProtocol::configInterface(PortSettings SerialSetting, const QString &portName)
{
}

void MKProtocol::configInterface(const QString &portName)
{
}

void MKProtocol::checkPackages()
{
    /* Find the start byte of the protocol */
    int indexSearch = incomingData.indexOf(START_PACKAGE);
    int stopProtocolIndex = incomingData.indexOf(STOP_PACKAGE);

    /* Check if there is a possible valid package (Start and Stop byte) */
    if ((0 <= indexSearch) && (stopProtocolIndex > indexSearch))
        this->handleBuffer(0);

}

bool MKProtocol::OpenInterface()
{
    if (heliComm)
        return (heliComm->OpenInterface());
    else
        return false;
}

void MKProtocol::CloseInterface()
{
    if (heliComm)
        if (heliComm->isOpen())
            heliComm->CloseInterface();
}

bool MKProtocol::OpenCloseInterface()
{
    if (heliComm)
        return heliComm->OpenCloseInterface();
    else
        return false;
}

