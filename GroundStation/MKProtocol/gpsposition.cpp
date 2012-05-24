#include "gpsposition.h"

GPSPosition::GPSPosition()
{
    latitude = 0;
    longitude = 0;
    altitude = 0;
}


GPSPosition::GPSPosition(long lat, long longit, long alt)
{
    latitude = lat;
    longitude = longit;
    altitude = alt;
}


void GPSPosition::setPosition(long lat, long longit, long alt)
{
    latitude = lat;
    longitude = longit;
    altitude = alt;
}

long GPSPosition::getLatitude()
{
    return latitude;
}

long GPSPosition::getLongitude()
{
    return longitude;
}

long GPSPosition::getAltitude()
{
    return altitude;
}


