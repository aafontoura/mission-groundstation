#ifndef MISSIONNODE_H
#define MISSIONNODE_H
#include "MKProtocol/gpsposition.h"

class MissionNode : public GPSPosition
{
public:
    MissionNode();

    QString description;
    int priority;
    QString prorityXML;
    QString command;
    QString commandVector;

    void setDescription(QString desc);


};

#endif // MISSIONNODE_H
