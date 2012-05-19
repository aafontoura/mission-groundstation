#include "debuganalogs.h"

DebugAnalogs::DebugAnalogs() : HelicopterAttribute(DEBUG_OUT_HEADER,NC_ADDRESS,0)
{
    AutoSendInterval.append(1);
    setRequestData(AutoSendInterval);
}

DebugAnalogs::DebugAnalogs(char DestDeviceParam) : HelicopterAttribute(DEBUG_OUT_HEADER,DestDeviceParam,0)
{
    AutoSendInterval.append(1);
    setRequestData(AutoSendInterval);
    //RequestSettings.setRequestParameter(new QByteArray(1));
}

DebugAnalogs::DebugAnalogs(char DestDeviceParam, int Period) : HelicopterAttribute(DEBUG_OUT_HEADER,DestDeviceParam,0)
{
    AutoSendInterval.append(Period);
    setRequestData(AutoSendInterval);
}

void DebugAnalogs::UpdateData(QByteArray NewData)
{
    memcpy(&DebugValues,NewData.data(),sizeof(str_DebugOut));

}

unsigned char DebugAnalogs::getStatus(int index)
{
    if (index < 2)
        return DebugValues.Status[index];
    else
        return 0;
}

signed int DebugAnalogs::getAnalog(int index)
{
    if (index < 32)
        return DebugValues.Analog[index];
    else
        return 0;
}
