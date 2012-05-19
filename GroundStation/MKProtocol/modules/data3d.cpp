#include "data3d.h"

Data3D::Data3D() : HelicopterAttribute(DATA_3D_HEADER,FC_ADDRESS,0, true)
{
    AutoSendInterval.append(1);
    setRequestData(AutoSendInterval);
}

Data3D::Data3D(char DestDeviceParam) : HelicopterAttribute(DATA_3D_HEADER,DestDeviceParam,0, true )
{

}

Data3D::Data3D(char DestDeviceParam, int Period) : HelicopterAttribute(DATA_3D_HEADER,DestDeviceParam,0, true)
{
    AutoSendInterval.append(Period);
    setRequestData(AutoSendInterval);
}

void Data3D::UpdateData(QByteArray NewData)
{
    memcpy(&Data3Dim,NewData.data(),sizeof(str_Data3D));
}

qint16 Data3D::getWinkel(int index)
{
    if (index < 3)
        return(Data3Dim.Winkel[index]);
    else
        return 0;
}

signed char Data3D::getCentroid(int index)
{
    if (index < 3)
        return(Data3Dim.Winkel[index]);
    else
        return 0;

}
