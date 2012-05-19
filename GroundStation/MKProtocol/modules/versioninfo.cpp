#include "versioninfo.h"

VersionInfo::VersionInfo()
{
}

VersionInfo::VersionInfo(char DestDeviceParam) : HelicopterAttribute(VERSION_INFO_HEADER,DestDeviceParam,0)
{
}

VersionInfo::VersionInfo(ParameterRequest Settings) : HelicopterAttribute(Settings)
{
}




QByteArray VersionInfo::getSwVersion()
{
    return SwVersion;
}

QByteArray VersionInfo::getProtoVersion()
{
    return ProtoVersion;
}

void VersionInfo::UpdateData(QByteArray NewData)
{
    memcpy(&VersionPacked,NewData.data(),sizeof(versionType));
    SwVersion.clear();
    SwVersion.append(QString::number(VersionPacked.SWMajor) + ".");
    SwVersion.append(QString::number(VersionPacked.SWMinor));
    SwVersion.append((char)(VersionPacked.SWPatch+'a'));

    ProtoVersion.clear();
    ProtoVersion.append(QString::number(VersionPacked.ProtoMajor) + ".");
    ProtoVersion.append(QString::number(VersionPacked.ProtoMinor));
}
