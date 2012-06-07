#include "osddata.h"

OSDData::OSDData() : HelicopterAttribute(REQUEST_OSD,NC_ADDRESS,0, false)
{
    AutoSendInterval.append(10);
    setRequestData(AutoSendInterval);
}

OSDData::OSDData(char DestDeviceParam) : HelicopterAttribute(DATA_3D_HEADER,DestDeviceParam,0, true)
{
}

OSDData::OSDData(char DestDeviceParam, int Period) : HelicopterAttribute(DATA_3D_HEADER,DestDeviceParam,0, true)
{
    AutoSendInterval.append(Period);
    setRequestData(AutoSendInterval);
}

void OSDData::UpdateData(QByteArray NewData)
{
    memcpy(&navigationData,NewData.data(),sizeof(naviDataType));
}

OSDData::naviDataType *OSDData::getData()
{
    return &navigationData;
}

