#ifndef NETWORKMISSION_H
#define NETWORKMISSION_H

#include <QString>
#include <QList>
#include <QObject>
#include "missionwaypoint.h"

class NetworkMission
{
public:
    NetworkMission();
    /* NetworkMission(NetworkMission *newMission); */

    typedef struct
    {
        QString name;
        QString description;
        QString tasks;
        int priority;
        QString priorityXML;
        QString latBoundaries;        
        QString longBoundaries;
        GPSPosition SWPointBound;
        GPSPosition NEPointBound;
        QString altBoundaries;

    } informationType;

    typedef struct
    {
        QString wheater;
        QString timeOfTheDay;
        QString type;
    } environmentType;



    typedef struct
    {
        QString identifier;
        QString description;
        QString latitude;
        QString longitude;
        QString command;
        QString commandVector;
        QString mainConstraint;
    } missionStaticNodeType;


    informationType missionInformation;
    environmentType missionEnvironment;

    QList<MissionWaypoint> waypointsList;
    QList<missionStaticNodeType> staticNodesList;

private:




};

#endif // NETWORKMISSION_H
