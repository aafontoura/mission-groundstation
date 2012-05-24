#ifndef GPSPOSITION_H
#define GPSPOSITION_H

#include <QString>

class GPSPosition
{
public:
    GPSPosition();
    GPSPosition(long lat, long longit, long alt);

    void setPosition(long lat, long longit, long alt = 0);
    void setPosition(QString longit, QString lat, long alt = 0);

    long getLatitude();
    long getLongitude();
    long getAltitude();

    QString getLatitudeString();
    QString getLongitudeString();


private:
   long longitude;
   long latitude;
   long altitude;


};

#endif // GPSPOSITION_H
