#ifndef VERSIONINFO_H
#define VERSIONINFO_H

#include <QByteArray>
#include <QString>
#include "HelicopterDefs.h"
#include "helicopterattribute.h"



class VersionInfo : public HelicopterAttribute
{
public:
    VersionInfo();
    VersionInfo(char DestDeviceParam);
    VersionInfo(ParameterRequest Settings);
    QByteArray getSwVersion();
    QByteArray getProtoVersion();
    void UpdateData(QByteArray NewData);


private:


    struct versionType
    {
      unsigned char SWMajor;
      unsigned char SWMinor;
      unsigned char ProtoMajor;
      unsigned char ProtoMinor;
      unsigned char SWPatch;
      unsigned char HardwareError[5];
    } VersionPacked;

    QByteArray SwVersion;
    QByteArray ProtoVersion;
    QByteArray SwPatch;

};

#endif // VERSIONINFO_H
