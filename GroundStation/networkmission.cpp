#include "networkmission.h"

NetworkMission::NetworkMission()
{
}

NetworkMission::NetworkMission(const QString &portName)
{
    missionNodesComm = new ZigBeeProtocol(portName);

    connect(missionNodesComm,SIGNAL(dataReceived(QByteArray,int)),this,SLOT(networkPackageReceiver(QByteArray,int)));

    addStaticNode("Teste1",0x03);
    addStaticNode("Teste2",0x04);


}

/*************************************************************************************************/
/* Name.........: addMobileNode                                                                  */
/* Inputs.......: name,address                                                                   */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void NetworkMission::addMobileNode(QString name, int address)
{
    HelicopterHandler *newHelicopter = new HelicopterHandler(name,address);
    translateCommunicationType newNode;

    /* Configure translation table */
    newNode.address = address;
    newNode.type = MOBILE_API_NODE_TYPE;

    /* Connect the sender data handler */
    connect(newHelicopter,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    connect(newHelicopter,SIGNAL(FCVersionReceived(int)),this,SLOT(handleFCVersionReceived(int)));
    connect(newHelicopter,SIGNAL(NCVersionReceived(int)),this,SLOT(handleNCVersionReceived(int)));
    connect(newHelicopter,SIGNAL(FC3DDatareceived(int)),this,SLOT(handleFC3DDatareceived(int)));
    connect(newHelicopter,SIGNAL(NumberOfWaypointsReceived(int)),this,SLOT(handleNumberOfWaypointsReceived(int)));


    typeTranslation << newNode;
    mobileNodesList << newHelicopter;

    /* Initialize the helicopter protocol process */
    newHelicopter->initMachineState();
}


/*************************************************************************************************/
/* Name.........: addStaticNode                                                                  */
/* Inputs.......: name, address                                                                  */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void NetworkMission::addStaticNode(QString identifier, int address)
{
    ZigBeeTransparentStaticNode *newStaticNode = new ZigBeeTransparentStaticNode(identifier,address);
    translateCommunicationType newNode;

    newNode.address = address;
    newNode.type = STATIC_TRANSPARENT_NODE_TYPE;

    //connect(newStaticNode,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    typeTranslation << newNode;

    //staticNodesList << newStaticNode;
    missionNodesList << newStaticNode;
}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
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


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void NetworkMission::networkPackageReceiver(QByteArray data, int address)
{

    /* TODO: Inheritize MobileNode also from missionNode */
    for(int i = 0 ; i < mobileNodesList.length(); i++)
    {
        if (mobileNodesList[i]->getAddress() == address)
        {
            mobileNodesList[i]->hubInProtocol(data);
            break;
        }
    }

    for(int i = 0 ; i < missionNodesList.length(); i++)
    {
        if (missionNodesList[i]->getAddress() == address)
        {
            /* GAMBIARRA (workaround)!!! */
            /* TODO: find another way. Just one list for all kind of nodes (inherited) but the
              data handler must be especialized */
            missionNodesList[i]->dataHandler(data);

            break;
        }
    }

}

void NetworkMission::handleFCVersionReceived(int address)
{
    emit(mobileNodeFCVersionReceived(address));
}

void NetworkMission::handleNCVersionReceived(int address)
{
    emit(mobileNodeNCVersionReceived(address));
}

void NetworkMission::handleFC3DDatareceived(int address)
{
    emit(mobileNodeFC3DDatareceived(address));
}

void NetworkMission::handleNumberOfWaypointsReceived(int address)
{
    emit(mobileNodeNumberOfWaypointsReceived(address));
}

void NetworkMission::changeNodeAddress(int address, int newAddress)
{
    MissionNode *tempNode = 0;
    for(int i = 0 ; i < missionNodesList.length(); i++)
    {
        /* Check if the newAddress is repeated */
        if (missionNodesList[i]->getAddress() == newAddress)
            return;
        else
        {
            /* Check the node to change de address */
            if (missionNodesList[i]->getAddress() == address)
            {
                tempNode = missionNodesList[i];
            }
        }
    }

    /* if the node was found, change address */
    if (tempNode!=0)
        tempNode->setAddress(newAddress);

}

