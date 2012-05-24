#ifndef NETWORKMISSION_H
#define NETWORKMISSION_H

#include <QString>
#include <QList>
#include <QObject>

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
        QString name;
        QString description;
        int priority;
        QString prorityXML;
        QString latitude;
        QString longitude;
        QString altitude;
        QString command;
        QString commandVector;
    } missionWaypoinType;

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

    QList<NetworkMission::missionWaypoinType> waypointsList;
    QList<missionStaticNodeType> staticNodesList;

private:




};

#endif // NETWORKMISSION_H
