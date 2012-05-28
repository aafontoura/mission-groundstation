#ifndef MISSIONSTATICNODE_H
#define MISSIONSTATICNODE_H
#include <QString>
#include "missionnode.h"

class MissionStaticNode : public MissionNode
{
public:
    MissionStaticNode();

    QString identifier;
};

#endif // MISSIONSTATICNODE_H
