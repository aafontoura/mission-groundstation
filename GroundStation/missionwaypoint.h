#ifndef MISSIONWAYPOINT_H
#define MISSIONWAYPOINT_H

#include "MKProtocol/gpsposition.h"

class MissionWaypoint : public GPSPosition
{
public:
    MissionWaypoint();

    QString name;
    QString description;
    int priority;
    QString prorityXML;
    QString command;
    QString commandVector;

    QString getName();

};

#endif // MISSIONWAYPOINT_H
