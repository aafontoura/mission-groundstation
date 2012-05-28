#include "networkmission.h"

NetworkMission::NetworkMission()
{
}

NetworkMission::NetworkMission(const QString &portName)
{
    missionNodesComm = new ZigBeeProtocol(portName);
}

void NetworkMission::addMobileNode(QString name, int address)
{
    HelicopterHandler *newHelicopter = new HelicopterHandler(name,address);

    mobileNodesList << newHelicopter;

}

