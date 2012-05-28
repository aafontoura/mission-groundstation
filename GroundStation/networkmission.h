#ifndef NETWORKMISSION_H
#define NETWORKMISSION_H

#include <QString>
#include <QList>
#include <QObject>
#include "zigbeeprotocol.h"
#include "helicopterhandler.h"
#include "missionwaypoint.h"
#include "missionstaticnode.h"

class NetworkMission
{
public:
    NetworkMission();
    NetworkMission(const QString &portName);
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
    QList<MissionStaticNode> staticNodesList;
    QList<HelicopterHandler*> mobileNodesList;

    void addMobileNode(QString name, int address);

private:
    ZigBeeProtocol *missionNodesComm;
    //slots:


private slots:
    void networkPackageSender(QByteArray data, int address);
    void networkPackageReceiver(QByteArray data, int address);


};

#endif // NETWORKMISSION_H
