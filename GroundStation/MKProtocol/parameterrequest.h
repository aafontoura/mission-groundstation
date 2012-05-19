#ifndef PARAMETERREQUEST_H
#define PARAMETERREQUEST_H
#include <QByteArray>

class ParameterRequest
{
public:
    ParameterRequest();
    ParameterRequest(char attType,char dstDev, QByteArray reqParam);

    char getAttributeType();
    void setAttributeType(char newAttType);
    char getDestDevice();
    void setDestDevice(char newDstDev);
    QByteArray getRequestParameter();
    void setRequestParameter(QByteArray newReqParam);
    void setParameters(char attType,char dstDev, QByteArray reqParam);


private:
    char AttributeType;
    char DestDevice;
    QByteArray RequestParameter;
};

#endif // PARAMETERREQUEST_H
