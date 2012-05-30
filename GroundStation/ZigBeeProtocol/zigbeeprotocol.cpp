#include "zigbeeprotocol.h"

ZigBeeProtocol::ZigBeeProtocol()
{
}

ZigBeeProtocol::ZigBeeProtocol(const QString &portName)
{
    /* Open a serial interface */
    serialComm = new SerialHandler(portName);

    bool returnCode = serialComm->OpenPort();

    /* Event Configuration */
    connect(serialComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));

    incomingData.clear();


}

ZigBeeProtocol::ZigBeeProtocol(PortSettings SerialSetting, const QString &portName)
{
    /* Open a serial interface */
    serialComm = new SerialHandler(SerialSetting,portName);

    /* Event Configuration */
    connect(serialComm,SIGNAL(dataReceived(QByteArray)),this,SLOT(handleBuffer(QByteArray)));

    bool returnCode = serialComm->OpenPort();
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
    /* push back the incoming data on the local buffer */
    incomingData.append(Data);

    /* Find the start byte of the protocol */
    int indexSearch = incomingData.indexOf(START_ZIGBEE_PACKAGE);

    int expectedSize = ((int)incomingData[indexSearch+2])+(((int)incomingData[indexSearch+1])>>8);

    /* TODO: handle an over capacity of package (overtraffic)
    /* Check if there is a possible valid package (Start and Stop byte) */
    while ((0 <= indexSearch) && (0 < expectedSize) && (MAX_ZIGBEE_SIZE > expectedSize)
           && (expectedSize <= (incomingData.length()-3)))
    {
        QByteArray incomingBuffer = incomingData.mid(indexSearch+3,expectedSize+1);
        if (checkByteCecksum(incomingBuffer))
        {

            /* Ignore bytes */
            incomingBuffer = incomingBuffer.left(expectedSize);


            /* Flush Processed Data */
            incomingData = incomingData.right(incomingData.length()-indexSearch-expectedSize-4);
            //waitingReply = false;
            dataHandler(incomingBuffer);
        }
        else
        {
            /* Flush Data */
            incomingData = incomingData.right(incomingData.length()-indexSearch-4);
        }

        indexSearch = incomingData.indexOf(START_ZIGBEE_PACKAGE);
        expectedSize = ((int)incomingData[indexSearch+2])+(((int)incomingData[indexSearch+1])>>8);
    }

    if (0 > indexSearch)
        incomingData.clear();
}



void ZigBeeProtocol::sendBuffer(QByteArray Data, int address, int type)
{
    //serialComm->sendBuffer(Data);
    PrepareSendPackage(type,address,Data);
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

        /* Serial Emulate Mode */
    case SERIAL_TX_MODE:
        zigBeeTx16RequestStruct commandTx16;


        dataOut.data = (char*)&commandTx16;

        /* prepare header */
        commandTx16.frameId = 1;
        commandTx16.atCommandId = atCommandID;
        commandTx16.addr16Lsb = addrDestiny & 0xFF; // 0x02;
        commandTx16.addr16Msb = (addrDestiny >> 8) & 0xFF;
        commandTx16.commandOption = 0;

        /* encapsulate data */
        commandTx16.data = Data.data();

        /* Adjust package size*/
        tempLength = 5 + Data.length();
        dataOut.length[0] = (tempLength >> 8) & 0xFF;
        dataOut.length[1] = tempLength & 0xFF;

        ptrBuffer = dataOut.data;

        /* Calculate checksum */
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

        /* Fill checksum field */
        dataOut.checksum = 0xFF - tempChecksum;

        /* Agregate data */
        sendData.append((char*)&dataOut,3);
        sendData.append((char*)&commandTx16,5);
        sendData.append(Data);
        sendData.append(dataOut.checksum);

        /* send to the communication interface */
        serialComm->sendBuffer(sendData);

        break;

        case 0x08:
            zigBeeAtCommandStruct frameAtData;

            dataOut.data = (char*)&frameAtData;
            frameAtData.atCommandId = 0x08;
            frameAtData.frameId = 0x52;
            frameAtData.command[0] = 'P';
            frameAtData.command[1] = '1';
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

bool ZigBeeProtocol::checkByteCecksum(QByteArray data)
{
    char tempChecksum = 0;
    for (int i = 0 ; i < data.length() ; i++)
    {
        tempChecksum += data[i];
    }
    tempChecksum++;

    return(!tempChecksum);
}

void ZigBeeProtocol::dataHandler(QByteArray data)
{
    QByteArray nodeData;
    int address;
    unsigned char type = data[0];
    switch(type)
    {
        case 0x83:
            nodeData = data.right(data.length()-3);
            address = (int)data[2]+(((int)incomingData[1])>>8);

            emit(dataReceived(nodeData,address));
            break;
        default:
            address = 0;
            break;
    }
}
