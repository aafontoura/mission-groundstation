#include "helicopterattribute.h"


HelicopterAttribute::HelicopterAttribute()
{
}

HelicopterAttribute::HelicopterAttribute(ParameterRequest Settings)
{
    RequestSettings.setAttributeType(Settings.getAttributeType());
    RequestSettings.setDestDevice(Settings.getDestDevice());
    RequestSettings.setRequestParameter(Settings.getRequestParameter());
    isPeriodicAttribute = false;
}

HelicopterAttribute::HelicopterAttribute(ParameterRequest Settings, bool isPeriodicAtt)
{
    RequestSettings.setAttributeType(Settings.getAttributeType());
    RequestSettings.setDestDevice(Settings.getDestDevice());
    RequestSettings.setRequestParameter(Settings.getRequestParameter());
    isPeriodicAttribute = isPeriodicAtt;
}

HelicopterAttribute::HelicopterAttribute(char attrType, char dstType, QByteArray newReqData)
{
    RequestSettings.setAttributeType(attrType);
    RequestSettings.setDestDevice(dstType);
    RequestSettings.setRequestParameter(newReqData);
    isPeriodicAttribute = false;
}

HelicopterAttribute::HelicopterAttribute(char attrType, char dstType, QByteArray newReqData, bool isPeriodicAtt)
{
    RequestSettings.setAttributeType(attrType);
    RequestSettings.setDestDevice(dstType);
    RequestSettings.setRequestParameter(newReqData);
    isPeriodicAttribute = isPeriodicAtt;
}

ParameterRequest HelicopterAttribute::RequestNewData()
{
    return(RequestSettings);
}


char HelicopterAttribute::getAttributeType()
{
    return RequestSettings.getAttributeType();
}

char HelicopterAttribute::getDestDevice()
{
    return RequestSettings.getDestDevice();
}

QByteArray HelicopterAttribute::getRequestData()
{
    return (RequestSettings.getRequestParameter());
}

void HelicopterAttribute::setRequestData(QByteArray newReqData)
{
    RequestSettings.setRequestParameter(newReqData);
}

void HelicopterAttribute::setRequestData(char NewReqData)
{
    QByteArray newData;
    newData.append(NewReqData);
    RequestSettings.setRequestParameter(newData);
}

void HelicopterAttribute::setRequestID(char NewID)
{
    RequestSettings.setAttributeType(NewID);
}

ParameterRequest HelicopterAttribute::getParameter()
{
    return(RequestSettings);
}

bool HelicopterAttribute::isPeriodic()
{
    return(isPeriodicAttribute);
}
