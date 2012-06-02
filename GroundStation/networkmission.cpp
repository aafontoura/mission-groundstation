#include "networkmission.h"

NetworkMission::NetworkMission()
{
}

NetworkMission::NetworkMission(const QString &portName)
{
    missionNodesComm = new ZigBeeProtocol(portName);

    connect(missionNodesComm,SIGNAL(dataReceived(QByteArray,int)),this,SLOT(networkPackageReceiver(QByteArray,int)));

    //addStaticNode("Teste1",0x03);
    //addStaticNode("Teste2",0x04);


}

/*************************************************************************************************/
/* Name.........: addMobileNode                                                                  */
/* Inputs.......: name,address                                                                   */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
HelicopterHandler* NetworkMission::addMobileNode(QString name, int address)
{
    HelicopterHandler *newHelicopter = new HelicopterHandler(name,address);
    translateCommunicationType newNode;

    /* Configure translation table */
    newNode.address = address;
    newNode.type = MOBILE_API_NODE_TYPE;

    /* Connect the sender data handler */
    connect(newHelicopter,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    /*connect(newHelicopter,SIGNAL(FCVersionReceived(QString)),this,SLOT(handleFCVersionReceived(QString)));
    connect(newHelicopter,SIGNAL(NCVersionReceived(QString)),this,SLOT(handleNCVersionReceived(QString)));
    connect(newHelicopter,SIGNAL(FC3DDatareceived(int,int,int)),this,SLOT(handleFC3DDatareceived(int,int,int)));
    connect(newHelicopter,SIGNAL(NumberOfWaypointsReceived(int)),this,SLOT(handleNumberOfWaypointsReceived(int)));*/


    typeTranslation << newNode;
    mobileNodesList << newHelicopter;
    missionNodesList << newHelicopter;

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

int NetworkMission::getEmptyAddress()
{
    bool emptyAddr = true;
    /* 500 is arbitrary number, just to prevent loop forever */
    for (int nAddress = 1; nAddress < 500 ; nAddress++)
    {
        emptyAddr = true;
        for(int i = 0 ; i < missionNodesList.length(); i++)
        {
            if (missionNodesList[i]->getAddress() == nAddress)
            {
                emptyAddr = false;
                break;
            }
        }
        if (emptyAddr)
            return nAddress;
    }

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
   /* for(int i = 0 ; i < mobileNodesList.length(); i++)
    {
        if (mobileNodesList[i]->getAddress() == address)
        {
            mobileNodesList[i]->hubInProtocol(data.right(data.length()-2));
            break;
        }
    }*/

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




/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void NetworkMission::changeNodeAddress(int address, int newAddress)
{
    MissionNode *tempMissionNode = 0;

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
                tempMissionNode = missionNodesList[i];

            }
        }
    }

    /* TODO: as soon as the helicopter is inserted in the missionNodeList, this
      isn't need anymore */
    for(int i = 0 ; i < typeTranslation.length(); i++)
    {
        if (typeTranslation[i].address == address)
        {
            typeTranslation[i].address = newAddress;
            break;
        }
    }



    /* if the node was found, change address */
    if (tempMissionNode!=0)
    {
        tempMissionNode->setAddress(newAddress);
    }


}

