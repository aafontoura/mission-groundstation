#include "gpsposition.h"

GPSPosition::GPSPosition()
{
    latitude = 0;
    longitude = 0;
    altitude = 0;
}


GPSPosition::GPSPosition(double lat, double longit, double alt)
{
    latitude = lat;
    longitude = longit;
    altitude = alt;
}

GPSPosition::GPSPosition(QString longit, QString lat, double alt)
{
}


void GPSPosition::setPosition(double lat, double longit, double alt)
{
    latitude = lat;
    longitude = longit;
    altitude = alt;
}

void GPSPosition::setPosition(QString longit, QString lat, double alt)
{

    longitude = longit.left(longit.indexOf("°")).toDouble();
    longit = longit.right(longit.length()-longit.indexOf("°")-1);
    longitude += longit.left(longit.indexOf("'")).toDouble()/60;
    longit = longit.right(longit.length()-longit.indexOf("'")-1);
    longitude += longit.left(longit.indexOf("'")).toDouble()/3600;

    if (longit.endsWith("O"))
        longitude = -longitude;

    latitude = lat.left(lat.indexOf("°")).toDouble();
    lat = lat.right(lat.length()-lat.indexOf("°")-1);
    latitude += lat.left(lat.indexOf("'")).toDouble()/60;
    lat = lat.right(lat.length()-lat.indexOf("'")-1);
    latitude += lat.left(lat.indexOf("'")).toDouble()/3600;

    if (lat.endsWith("S"))
        latitude = -latitude;

    altitude = alt;
}

/*************************************************************************************************/
/* Name.........: setLongitudeStr                                                                */
/* Inputs.......: longit - String in Degrees, minutes and seconds                                */
/* Outputs......: none                                                                           */
/* Description..: Convert the longitude from string in Degrees, minutes and seconds to degrees   */
/*                in double.                                                                     */
/*************************************************************************************************/
void GPSPosition::setLongitudeStr(QString longit)
{
    longitude = longit.left(longit.indexOf("°")).toDouble();
    longit = longit.right(longit.length()-longit.indexOf("°")-1);
    longitude += longit.left(longit.indexOf("'")).toDouble()/60;
    longit = longit.right(longit.length()-longit.indexOf("'")-1);
    longitude += longit.left(longit.indexOf("'")).toDouble()/3600;

    if (longit.endsWith("O"))
        longitude = -longitude;
}

/*************************************************************************************************/
/* Name.........: setLatitudeStr                                                                 */
/* Inputs.......: lat - String                                                                   */
/* Outputs......: none                                                                           */
/* Description..: Convert the latitude from string to double.                                    */
/*************************************************************************************************/
void GPSPosition::setAltitudeStr(QString alt)
{
    /* altitude in meters */
    if (alt.endsWith("m"))
    {
        altitude = alt.left(alt.indexOf("m")).toDouble();
    }

}

/*************************************************************************************************/
/* Name.........: setLatitudeStr                                                                 */
/* Inputs.......: lat - String in Degrees, minutes and seconds                                   */
/* Outputs......: none                                                                           */
/* Description..: Convert the latitude from string in Degrees, minutes and seconds to degrees    */
/*                in double.                                                                     */
/*************************************************************************************************/
void GPSPosition::setLatitudeStr(QString lat)
{
    latitude = lat.left(lat.indexOf("°")).toDouble();
    lat = lat.right(lat.length()-lat.indexOf("°")-1);
    latitude += lat.left(lat.indexOf("'")).toDouble()/60;
    lat = lat.right(lat.length()-lat.indexOf("'")-1);
    latitude += lat.left(lat.indexOf("'")).toDouble()/3600;

    if (lat.endsWith("S"))
        latitude = -latitude;
}

void GPSPosition::setLatitude(double lat)
{
    latitude = lat;
}

void GPSPosition::setLongitude(double longit)
{
    longitude = longit;
}

void GPSPosition::setAltitude(double alt)
{
    altitude = alt;
}

double GPSPosition::getLatitude()
{
    return latitude;
}

double GPSPosition::getLongitude()
{
    return longitude;
}

double GPSPosition::getAltitude()
{
    return altitude;
}




