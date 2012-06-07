#include "zigbeetransparentstaticnode.h"

ZigBeeTransparentStaticNode::ZigBeeTransparentStaticNode()
{
    RSSI = 100;
    discretes = 0;
}

ZigBeeTransparentStaticNode::ZigBeeTransparentStaticNode(int address) : MissionStaticNode(address)
{
    RSSI = 100;
    discretes = 0;
}

ZigBeeTransparentStaticNode::ZigBeeTransparentStaticNode(QString identifier, int address) : MissionStaticNode(identifier,address)
{
}

void ZigBeeTransparentStaticNode::dataHandler(QByteArray data)
{
    RSSI = (int)data[0];

    //int maskIn = (((int)data[3])>>8) + (int)data[4];
    //int dataIn = (((int)data[5])>>8) + (int)data[6];
    if (data.length()>=10)
    {
        int maskIn = (((int)data[7])>>8) + (int)data[8];
        int dataIn = (((int)data[9])>>8) + (int)data[10];


        if (discretes != (dataIn & maskIn))
        {
            discretes = (dataIn & maskIn);
            emit(discrete1Changed(!(discretes&0x01)));
        }
    }
    emit(newRSSIReceived(RSSI));
}

bool ZigBeeTransparentStaticNode::getDIO(int selDIO)
{
    return (discretes & (1 >> selDIO));
}

int ZigBeeTransparentStaticNode::getRSSI()
{
    return RSSI;
}
