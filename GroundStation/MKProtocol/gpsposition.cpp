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

GPSPosition::WaypointStruct GPSPosition::getWaypointStructData()
{
    WaypointStruct tempWaypoint;



    memset(&tempWaypoint,0,sizeof(WaypointStruct));
    tempWaypoint.Position.Latitude = (quint32)  (getLatitude()*(double)10000000);
    tempWaypoint.Position.Longitude = (quint32) (getLongitude()*(double)10000000);
    tempWaypoint.Position.Altitude = (qint32) getAltitude();
    tempWaypoint.Position.Status = GPS_NEWDATA;
    tempWaypoint.ToleranceRadius = GPS_TOLERANCE_RADIUS_DEFAULT;
    tempWaypoint.HoldTime = GPS_HOLD_TIME_DEFAULT;
    tempWaypoint.Index = 0;
    tempWaypoint.pointType = GPS_POINT_TYPE_WPT;
    /*tempWaypoint.Name[0] = getName()[0].toLatin1();
    tempWaypoint.Name[1] = getName()[1].toLatin1();
    tempWaypoint.Name[2] = getName()[2].toLatin1();
    tempWaypoint.Name[3] = getName()[3].toLatin1();*/

    return tempWaypoint;
}



