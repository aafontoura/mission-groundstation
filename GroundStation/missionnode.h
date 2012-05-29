#ifndef MISSIONNODE_H
#define MISSIONNODE_H
#include "MKProtocol/gpsposition.h"

class MissionNode : public GPSPosition
{
public:
    MissionNode();
    MissionNode(int address);

    QString description;
    int priority;
    QString prorityXML;
    QString command;
    QString commandVector;

    int address;

    void setDescription(QString desc);
    void setAddress(int newAddress);

    int getAddress();

    virtual void dataHandler(QByteArray data);


};

#endif // MISSIONNODE_H
