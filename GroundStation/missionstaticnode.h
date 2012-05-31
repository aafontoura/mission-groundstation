#ifndef MISSIONSTATICNODE_H
#define MISSIONSTATICNODE_H
#include <QString>
#include <QByteArray>
#include "missionnode.h"

class MissionStaticNode : public MissionNode
{
public:
    MissionStaticNode();
    MissionStaticNode(int newAddress);
    MissionStaticNode(QString identifier,int newAddress);

    QString getIdentifier();
    void setIdentifier(QString newIdentifier);

    void dataHandler(QByteArray data);










};

#endif // MISSIONSTATICNODE_H
