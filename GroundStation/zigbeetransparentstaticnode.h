#ifndef ZIGBEETRANSPARENTSTATICNODE_H
#define ZIGBEETRANSPARENTSTATICNODE_H

#include "missionstaticnode.h"

class ZigBeeTransparentStaticNode : public MissionStaticNode
{
    Q_OBJECT
public:
    ZigBeeTransparentStaticNode();
    ZigBeeTransparentStaticNode(int address);
    ZigBeeTransparentStaticNode(QString identifier,int address);

    void dataHandler(QByteArray data);

    bool getDIO(int selDIO);
    int getRSSI();

private:
    int RSSI;
    int discretes;

signals:
    void discrete1Changed(bool);
    void newRSSIReceived(int);
};

#endif // ZIGBEETRANSPARENTSTATICNODE_H
