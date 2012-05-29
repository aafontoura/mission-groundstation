#ifndef ZIGBEETRANSPARENTSTATICNODE_H
#define ZIGBEETRANSPARENTSTATICNODE_H

#include "missionstaticnode.h"

class ZigBeeTransparentStaticNode : MissionStaticNode
{
public:
    ZigBeeTransparentStaticNode();
    ZigBeeTransparentStaticNode(int address);

    void dataHandler(QByteArray data);
};

#endif // ZIGBEETRANSPARENTSTATICNODE_H
