#include "osddata.h"

OSDData::OSDData() : HelicopterAttribute(REQUEST_OSD,NC_ADDRESS,0, true)
{
    AutoSendInterval.append(1);
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
    currentPosition.setLatitude(((double)navigationData.CurrentPosition.Latitude * (double)10000000));
    currentPosition.setLongitude(((double)navigationData.CurrentPosition.Longitude * (double)10000000));
    currentPosition.setAltitude(((double)navigationData.CurrentPosition.Altitude * (double)1000));
}

OSDData::naviDataType *OSDData::getData()
{
    return &navigationData;
}

GPSPosition *OSDData::getCurrentPosition()
{
    return &currentPosition;
}
