#ifndef HELICOPTERATTRIBUTE_H
#define HELICOPTERATTRIBUTE_H
#include <QByteArray>
#include "parameterrequest.h"

class HelicopterAttribute
{
public:
    HelicopterAttribute();
    HelicopterAttribute(ParameterRequest Settings);
    HelicopterAttribute(ParameterRequest Settings, bool isPeriodicAtt);
    HelicopterAttribute(char attrType,char dstType, QByteArray newReqData);
    HelicopterAttribute(char attrType,char dstType, QByteArray newReqData, bool isPeriodicAtt);
    ParameterRequest RequestNewData();
    virtual void UpdateData(QByteArray NewData) = 0;

    char getAttributeType();
    char getDestDevice();
    QByteArray getRequestData();
    void setRequestData(QByteArray newReqData);
    void setRequestData(char NewReqData);
    void setRequestID(char NewID);
    ParameterRequest getParameter();
    bool isPeriodic();

private:
    ParameterRequest RequestSettings;
    bool isPeriodicAttribute;



};

#endif // HELICOPTERATTRIBUTE_H
