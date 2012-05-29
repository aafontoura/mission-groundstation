#ifndef MISSIONSTATICNODE_H
#define MISSIONSTATICNODE_H
#include <QString>
#include <QByteArray>
#include "missionnode.h"

class MissionStaticNode : public MissionNode
{
public:
    MissionStaticNode();
    MissionStaticNode(int newAddress);

    QString identifier;



};

#endif // MISSIONSTATICNODE_H
