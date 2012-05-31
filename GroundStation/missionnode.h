#ifndef MISSIONNODE_H
#define MISSIONNODE_H
#include "MKProtocol/gpsposition.h"
#include <QObject>

class MissionNode : public QObject, public GPSPosition
{
    Q_OBJECT
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

    void setName(QString newName);

    int getAddress();

    virtual void dataHandler(QByteArray data) = 0;


public slots:
    void setAddress(int newAddress);


};

#endif // MISSIONNODE_H
