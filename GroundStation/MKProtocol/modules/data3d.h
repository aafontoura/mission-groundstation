#ifndef DATA3D_H
#define DATA3D_H

#include "helicopterattribute.h"
#include "HelicopterDefs.h"
#include <QByteArray>

class Data3D : public HelicopterAttribute
{
public:
    Data3D();
    Data3D(char DestDeviceParam);
    Data3D(char DestDeviceParam, int Period);

    void UpdateData(QByteArray NewData);
    qint16 getWinkel(int index);
    signed char getCentroid(int index);


private:
    struct str_Data3D
    {
       qint16  Winkel[3]; // nick, roll, compass in 0,1°
       signed char Centroid[3];
       signed char reserve[5];
    } Data3Dim;

    QByteArray AutoSendInterval;
};

#endif // DATA3D_H
