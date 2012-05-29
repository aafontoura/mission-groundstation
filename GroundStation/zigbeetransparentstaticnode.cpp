#include "zigbeetransparentstaticnode.h"

ZigBeeTransparentStaticNode::ZigBeeTransparentStaticNode()
{
}

ZigBeeTransparentStaticNode::ZigBeeTransparentStaticNode(int address)
{
    this->setAddress(address);
}

void ZigBeeTransparentStaticNode::dataHandler(QByteArray data)
{
    int RSSI = (int)data[0];
    RSSI++;
}
