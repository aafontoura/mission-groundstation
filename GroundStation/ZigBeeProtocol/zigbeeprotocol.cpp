#include "zigbeeprotocol.h"

ZigBeeProtocol::ZigBeeProtocol()
{
}

ZigBeeProtocol::ZigBeeProtocol(const QString &portName)
{
    /* Open a serial interface */
    serialComm = new SerialHandler(portName);

    /* Event Configuration */
    connect(serialComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));
}

ZigBeeProtocol::ZigBeeProtocol(PortSettings SerialSetting, const QString &portName)
{
    /* Open a serial interface */
    serialComm = new SerialHandler(SerialSetting,portName);

    /* Event Configuration */
    connect(serialComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));
}


bool ZigBeeProtocol::OpenInterface()
{
    if (serialComm)
        return (serialComm->OpenPort());
    else
        return false;
}

void ZigBeeProtocol::CloseInterface()
{
    if (serialComm)
        if (serialComm->isOpen())
            serialComm->OpenClosePort();
}

bool ZigBeeProtocol::OpenCloseInterface()
{
    if (serialComm)
        return serialComm->OpenClosePort();
    else
        return false;
}

bool ZigBeeProtocol::isOpen()
{
    return serialComm->isOpen();
}



void ZigBeeProtocol::handleBuffer(QByteArray Data)
{
    emit(dataReceived(Data));
}



void ZigBeeProtocol::sendBuffer(QByteArray Data)
{
    //serialComm->sendBuffer(Data);
    PrepareSendPackage(0x01,0,Data);
}

void ZigBeeProtocol::PrepareSendPackage(char atCommandID, quint16 addrDestiny, QByteArray Data)
{
    zigBeeStruct dataOut;
    QByteArray sendData;
    quint16 tempLength = 0;
    char *ptrBuffer;
    char tempChecksum = 0;


    dataOut.startByte = 0x7E;


    switch (atCommandID)
    {
        case 0x10:
            zigBeeTransmitRequestStruct command;




            dataOut.data = (char*)&command;
            command.frameId = 1;
            command.atCommandId = atCommandID;
            command.addr16Lsb = 0xFE;
            command.addr16Msb = 0xFF;
            command.addr64Lsb = 0xFFFF0000;
            command.addr64Msb = 0;
            command.broadCastRadius = 0;
            command.commandOption = 0;
            command.data = Data.data();

            //dataOut.length = 14 + Data.length();
            tempLength = 14 + Data.length();
            dataOut.length[0] = (tempLength >> 8) & 0xFF;
            dataOut.length[1] = tempLength & 0xFF;

            ptrBuffer = dataOut.data;

            tempChecksum = 0;
            for (int i = 0 ; i < 14 ; i++)
            {
                tempChecksum += ptrBuffer[i];
            }

            ptrBuffer = command.data;
            for (int i = 0 ; i < Data.length() ; i++)
            {
                tempChecksum += ptrBuffer[i];
            }

            dataOut.checksum = 0xFF - tempChecksum;

            sendData.append((char*)&dataOut,3);
            sendData.append((char*)&command,14);
            sendData.append(Data);
            sendData.append(dataOut.checksum);

            serialComm->sendBuffer(sendData);
            break;

    case 0x01:
        zigBeeTx16RequestStruct commandTx16;


        dataOut.data = (char*)&commandTx16;
        commandTx16.frameId = 1;
        commandTx16.atCommandId = atCommandID;
        commandTx16.addr16Lsb = 0x02;
        commandTx16.addr16Msb = 0x00;
        commandTx16.commandOption = 0;
        commandTx16.data = Data.data();

        //dataOut.length = 14 + Data.length();
        tempLength = 5 + Data.length();
        dataOut.length[0] = (tempLength >> 8) & 0xFF;
        dataOut.length[1] = tempLength & 0xFF;

        ptrBuffer = dataOut.data;

        tempChecksum = 0;
        for (int i = 0 ; i < 5 ; i++)
        {
            tempChecksum += ptrBuffer[i];
        }

        ptrBuffer = commandTx16.data;
        for (int i = 0 ; i < Data.length() ; i++)
        {
            tempChecksum += ptrBuffer[i];
        }

        dataOut.checksum = 0xFF - tempChecksum;

        sendData.append((char*)&dataOut,3);
        sendData.append((char*)&commandTx16,5);
        sendData.append(Data);
        sendData.append(dataOut.checksum);

        serialComm->sendBuffer(sendData);
        break;

        case 0x08:
            zigBeeAtCommandStruct frameAtData;

            dataOut.data = (char*)&frameAtData;
            frameAtData.atCommandId = 0x08;
            frameAtData.frameId = 0x52;
            frameAtData.command[0] = 'C';
            frameAtData.command[1] = 'C';
            frameAtData.parameterValue = 0;

            tempLength = 4;
            dataOut.length[0] = (tempLength >> 8) & 0xFF;
            dataOut.length[1] = tempLength & 0xFF;

            ptrBuffer = dataOut.data;
            tempChecksum = 0;
            for (int i = 0 ; i < tempLength ; i++)
            {
                tempChecksum += ptrBuffer[i];
            }

            dataOut.checksum = 0xFF - tempChecksum;

            sendData.append((char*)&dataOut,3);
            sendData.append((char*)&frameAtData,4);
            sendData.append(dataOut.checksum);

            serialComm->sendBuffer(sendData);

            break;
        case 0x17:
            zigBeeRemoteAtRequestStruct frameAtRemoteData;

            dataOut.data = (char*)&frameAtRemoteData;
            frameAtRemoteData.atCommandId = 0x17;
            frameAtRemoteData.frameId = 0x52;
            frameAtRemoteData.addr16Lsb = 0xFE;
            frameAtRemoteData.addr16Msb = 0xFF;
            frameAtRemoteData.addr64Lsb = 0xFFFF0000;
            frameAtRemoteData.addr64Msb = 0;
            frameAtRemoteData.commandOption = 0;
            frameAtRemoteData.commandName[0] = 'M';
            frameAtRemoteData.commandName[1] = 'Y';
            frameAtRemoteData.commandData = 0;

            tempLength = 15;
            dataOut.length[0] = (tempLength >> 8) & 0xFF;
            dataOut.length[1] = tempLength & 0xFF;

            ptrBuffer = dataOut.data;
            tempChecksum = 0;
            for (int i = 0 ; i < tempLength ; i++)
            {
                tempChecksum += ptrBuffer[i];
            }

            dataOut.checksum = 0xFF - tempChecksum;

            sendData.append((char*)&dataOut,3);
            sendData.append((char*)&frameAtRemoteData,15);
            sendData.append(dataOut.checksum);

            serialComm->sendBuffer(sendData);
            break;
    }

}
