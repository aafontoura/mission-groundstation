#ifndef GPSPOSITION_H
#define GPSPOSITION_H

#include <QString>

class GPSPosition
{
public:
    GPSPosition();
    GPSPosition(double lat, double longit, double alt);

    void setPosition(double lat, double longit, double alt = 0);
    void setPosition(QString longit, QString lat, double alt = 0);

    void setLatitudeStr(QString lat);
    void setLongitudeStr(QString longit);
    void setAltitudeStr(QString alt);

    void setLatitude(double lat);
    void setLongitude(double longit);
    void setAltitude(double alt);

    double getLatitude();
    double getLongitude();
    double getAltitude();

    QString getLatitudeString();
    QString getLongitudeString();


private:
   double longitude;
   double latitude;
   double altitude;


};

#endif // GPSPOSITION_H
