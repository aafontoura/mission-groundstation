#include "missionnode.h"

MissionNode::MissionNode()
{
    name = "";
    description = "";
    priority = 0;
    prorityXML = "";
    command = "";
    commandVector = "";
    address = 0;
}

MissionNode::MissionNode(int address)
{
    this->address = address;
    name = "";
    description = "";
    priority = 0;
    prorityXML = "";
    command = "";
    commandVector = "";
}

MissionNode::MissionNode(QString name, int address)
{
    this->name = name;
    description = "";
    priority = 0;
    prorityXML = "";
    command = "";
    commandVector = "";
    this->address = address;
}

MissionNode::MissionNode(QString name)
{
    this->name = name;
    description = "";
    priority = 0;
    prorityXML = "";
    command = "";
    commandVector = "";
    address = 0;
}

void MissionNode::setDescription(QString desc)
{
    description = desc;
}

void MissionNode::setAddress(int newAddress)
{
    address = newAddress;
}

void MissionNode::setName(QString newName)
{
    name = newName;
}

int MissionNode::getAddress()
{
    return address;
}

QString MissionNode::getName()
{
    return name;
}









