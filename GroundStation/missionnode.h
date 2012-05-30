#ifndef MISSIONNODE_H
#define MISSIONNODE_H
#include "MKProtocol/gpsposition.h"

class MissionNode : public GPSPosition
{
public:
    MissionNode();
    MissionNode(int address);
    MissionNode(QString name,int address);
    MissionNode(QString name);

    QString name;
    QString description;
    int priority;
    QString prorityXML;
    QString command;
    QString commandVector;

    int address;



    QString getName();

    void setDescription(QString desc);
    void setAddress(int newAddress);
    void setName(QString newName);

    int getAddress();

    void dataHandler(QByteArray data);


};

#endif // MISSIONNODE_H
