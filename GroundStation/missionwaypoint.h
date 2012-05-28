#ifndef MISSIONWAYPOINT_H
#define MISSIONWAYPOINT_H

#include "missionnode.h"

class MissionWaypoint : public MissionNode
{
public:
    MissionWaypoint();

    QString name;

    QString getName();

};

#endif // MISSIONWAYPOINT_H
