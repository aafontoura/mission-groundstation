#ifndef NETWORKMISSION_H
#define NETWORKMISSION_H

#include <QString>
#include <QList>
#include <QObject>
#include "missionnode.h"
#include "zigbeeprotocol.h"
#include "helicopterhandler.h"
#include "missionwaypoint.h"
#include "missionstaticnode.h"
#include "zigbeetransparentstaticnode.h"
#include "zigBeeDefs.h"




class NetworkMission : public QObject
{
    Q_OBJECT
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

    typedef struct
    {
        int address;
        int type;
    } translateCommunicationType;


    informationType missionInformation;
    environmentType missionEnvironment;


    QList<MissionWaypoint*> waypointsList;

    QList<MissionNode*> staticNodesList;
    QList<HelicopterHandler*> mobileNodesList;
    QList<MissionNode*> missionNodesList;

    QList<translateCommunicationType> typeTranslation;

    HelicopterHandler *addMobileNode(QString name, int address);
    ZigBeeTransparentStaticNode *addStaticNode(QString identifier, int address);
    ZigBeeTransparentStaticNode *addStaticNode();
    void addStaticNode(ZigBeeTransparentStaticNode *newStaticNode);
    void assignWaypoints();

    int getEmptyAddress();

    MissionNode* getMisisonNode(int address);







private:
    ZigBeeProtocol *missionNodesComm;
    //slots:


private slots:
    void networkPackageSender(QByteArray data, int address);
    void networkPackageReceiver(QByteArray data, int address);


    /* MK Interface */
    void changeNodeAddress(int address,int newAddress);
    void sendTargetPosition(double latitude,double longitude,int address);
    void sendMotorSpeed(int engine,int newValue,int address);

    void handleZigbeeStaticNodeEvent(bool discrete,int address);



signals:
    void commError();
    void mobileNodeFCVersionReceived(int);
    void mobileNodeNCVersionReceived(int);
    void mobileNodeFC3DDatareceived(int);
    void mobileNodeNumberOfWaypointsReceived(int);


};

#endif // NETWORKMISSION_H
