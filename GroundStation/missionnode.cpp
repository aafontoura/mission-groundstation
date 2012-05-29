#include "missionnode.h"

MissionNode::MissionNode()
{
}

MissionNode::MissionNode(int address)
{
    this->address = address;
}

void MissionNode::setDescription(QString desc)
{
    description = desc;
}

void MissionNode::setAddress(int newAddress)
{
    address = newAddress;
}

int MissionNode::getAddress()
{
    return address;
}

void MissionNode::dataHandler(QByteArray data)
{
}
