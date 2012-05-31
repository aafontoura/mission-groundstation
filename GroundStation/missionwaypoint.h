#ifndef MISSIONWAYPOINT_H
#define MISSIONWAYPOINT_H

#include "missionnode.h"

class MissionWaypoint : public MissionNode
{
public:
    MissionWaypoint();

    void dataHandler(QByteArray data);



};

#endif // MISSIONWAYPOINT_H
