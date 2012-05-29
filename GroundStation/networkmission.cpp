#include "networkmission.h"

NetworkMission::NetworkMission()
{
}

NetworkMission::NetworkMission(const QString &portName)
{
    missionNodesComm = new ZigBeeProtocol(portName);

    connect(missionNodesComm,SIGNAL(dataReceived(QByteArray,int)),this,SLOT(networkPackageReceiver(QByteArray,int)));

    //ZigBeeTransparentStaticNode *testNode = new ZigBeeTransparentStaticNode(0x02);

    //staticNodesList << testNode;


}

void NetworkMission::addMobileNode(QString name, int address)
{
    HelicopterHandler *newHelicopter = new HelicopterHandler(name,address);
    translateCommunicationType newNode;

    newNode.address = address;
    newNode.type = MOBILE_API_NODE_TYPE;

    connect(newHelicopter,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));
    //connect(newHelicopter,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    typeTranslation << newNode;
    mobileNodesList << newHelicopter;

    newHelicopter->initMachineState();
}

void NetworkMission::networkPackageSender(QByteArray data, int address)
{
    int type = 0;

    /* Search the address in the typeTranslation table */
    /* TODO: implement a binary search (keep the table always sorted by address) */
    for(int i = 0 ; i < typeTranslation.length() ; i++)
    {
        if (typeTranslation[i].address == address)
        {
            type = typeTranslation[i].type;
            break;
        }
    }

    missionNodesComm->sendBuffer(data,address,type);



}

void NetworkMission::networkPackageReceiver(QByteArray data, int address)
{
    for(int i = 0 ; i < mobileNodesList.length(); i++)
    {
        if (mobileNodesList[i]->getAddress() == address)
        {
            mobileNodesList[i]->hubInProtocol(data);
            break;
        }
    }

    for(int i = 0 ; i < staticNodesList.length(); i++)
    {
        if (staticNodesList[i]->getAddress() == address)
        {
            staticNodesList[i]->dataHandler(data);
            break;
        }
    }

}

