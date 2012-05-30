#ifndef ZIGBEETRANSPARENTSTATICNODE_H
#define ZIGBEETRANSPARENTSTATICNODE_H

#include "missionstaticnode.h"

class ZigBeeTransparentStaticNode : public MissionStaticNode
{
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

};

#endif // ZIGBEETRANSPARENTSTATICNODE_H
