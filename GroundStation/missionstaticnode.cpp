#include "missionstaticnode.h"

MissionStaticNode::MissionStaticNode()
{
}

MissionStaticNode::MissionStaticNode(int newAddress) : MissionNode(newAddress)
{
}

MissionStaticNode::MissionStaticNode(QString identifier, int newAddress) : MissionNode(identifier, newAddress)
{
}

QString MissionStaticNode::getIdentifier()
{
    return this->getName();
}

void MissionStaticNode::setIdentifier(QString newIdentifier)
{
    this->setName(newIdentifier);
}
