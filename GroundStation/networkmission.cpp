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

    return newHelicopter;
}


/*************************************************************************************************/
/* Name.........: addStaticNode                                                                  */
/* Inputs.......: name, address                                                                  */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
ZigBeeTransparentStaticNode* NetworkMission::addStaticNode(QString identifier, int address)
{
    ZigBeeTransparentStaticNode *newStaticNode = new ZigBeeTransparentStaticNode(identifier,address);
    translateCommunicationType newNode;

    newNode.address = address;
    newNode.type = STATIC_TRANSPARENT_NODE_TYPE;
    newStaticNode->setAddress(address);
    //connect(newStaticNode,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    typeTranslation << newNode;

    staticNodesList << newStaticNode;
    missionNodesList << newStaticNode;

    connect(newStaticNode,SIGNAL(discrete1Event(bool,int)),this,SLOT(handleZigbeeStaticNodeEvent(bool,int)));

    return (newStaticNode);
}


/*************************************************************************************************/
/* Name.........: addStaticNode                                                                  */
/* Inputs.......:                                                                                */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
ZigBeeTransparentStaticNode *NetworkMission::addStaticNode()
{
    ZigBeeTransparentStaticNode *newStaticNode = new ZigBeeTransparentStaticNode();
    translateCommunicationType newNode;

    newNode.address = this->getEmptyAddress();
    newStaticNode->setAddress(newNode.address);
    newNode.type = STATIC_TRANSPARENT_NODE_TYPE;

    //connect(newStaticNode,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    typeTranslation << newNode;

    staticNodesList << newStaticNode;
    missionNodesList << newStaticNode;

    connect(newStaticNode,SIGNAL(discrete1Event(bool,int)),this,SLOT(handleZigbeeStaticNodeEvent(bool,int)));

    return (newStaticNode);

}

void NetworkMission::addStaticNode(ZigBeeTransparentStaticNode *newStaticNode)
{
    translateCommunicationType newNode;

    newNode.address = this->getEmptyAddress();
    newStaticNode->setAddress(newNode.address);
    newNode.type = STATIC_TRANSPARENT_NODE_TYPE;

    //connect(newStaticNode,SIGNAL(sendBuffer(QByteArray,int)),this,SLOT(networkPackageSender(QByteArray,int)));

    typeTranslation << newNode;

    staticNodesList << newStaticNode;
    missionNodesList << newStaticNode;

    connect(newStaticNode,SIGNAL(discrete1Event(bool,int)),this,SLOT(handleZigbeeStaticNodeEvent(bool,int)));

}

/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void NetworkMission::assignWaypoints()
{
    HelicopterHandler* copterNode;
    if ((waypointsList.length() > 0) && (mobileNodesList.length() > 0))
    {
        copterNode = mobileNodesList[0];
        for (int i = 0; i < waypointsList.length() ; i++)
        {
            //copterNode->SendWaypoint(waypointsList[i]->getWaypointStructData());
            copterNode->SendWaypoint((GPSPosition*)waypointsList[i]);
        }
    }

}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/

int NetworkMission::getEmptyAddress()
{
    bool emptyAddr = true;

    if (0 == missionNodesList.length())
    {
        return (1);
    }
    else
    {

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

        return 0;
    }

}

MissionNode *NetworkMission::getMisisonNode(int address)
{
    for(int i = 0 ; i < missionNodesList.length(); i++)
    {
        if (missionNodesList[i]->getAddress() == address)
        {
            return missionNodesList[i];
        }
    }
    return 0;


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

    for(int i = 0 ; i < missionNodesList.length(); i++)
    {
        if (missionNodesList[i]->getAddress() == address)
        {            
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

void NetworkMission::sendTargetPosition(double latitude, double longitude, int address)
{
    for(int i = 0 ; i < missionNodesList.length(); i++)
    {
        if (missionNodesList[i]->getAddress() == address)
        {
            HelicopterHandler* nodeTemp = dynamic_cast<HelicopterHandler*>(missionNodesList[i]);
            nodeTemp->SendWaypoint();
            //nodeTemp->sendTargetPosition(latitude,longitude);



        }
    }
}

void NetworkMission::sendMotorSpeed(int engine, int newValue, int address)
{
    HelicopterHandler* heliTemp = dynamic_cast<HelicopterHandler*>(getMisisonNode(address));
    if (heliTemp)
    {
        if (newValue < 256)
            heliTemp->setEngineValue(engine,(unsigned char)newValue);
    }
}

void NetworkMission::handleZigbeeStaticNodeEvent(bool discrete, int address)
{
    if (discrete)
    {
        if (mobileNodesList.length() > 0)
        {
            ZigBeeTransparentStaticNode* tempStaticNode = dynamic_cast<ZigBeeTransparentStaticNode*>(getMisisonNode(address));
            if (tempStaticNode)
            {
                mobileNodesList[0]->clearWaypoints();
                mobileNodesList[0]->SendWaypoint((GPSPosition*)tempStaticNode);
            }
        }
    }
}

