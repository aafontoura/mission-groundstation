#include "parameterrequest.h"

ParameterRequest::ParameterRequest()
{
}

ParameterRequest::ParameterRequest(char attType, char dstDev, QByteArray reqParam)
{
    AttributeType = attType;
    DestDevice = dstDev;
    RequestParameter = reqParam;


}

char ParameterRequest::getAttributeType()
{
    return (AttributeType);
}

void ParameterRequest::setAttributeType(char newAttType)
{
    AttributeType = newAttType;
}

char ParameterRequest::getDestDevice()
{
    return (DestDevice);
}

void ParameterRequest::setDestDevice(char newDstDev)
{
    DestDevice = newDstDev;
}

QByteArray ParameterRequest::getRequestParameter()
{
    return (RequestParameter);
}

void ParameterRequest::setRequestParameter(QByteArray newReqParam)
{
    RequestParameter = newReqParam;
}

void ParameterRequest::setParameters(char attType, char dstDev, QByteArray reqParam)
{
    AttributeType = attType;
    DestDevice = dstDev;
    RequestParameter = reqParam;
}
