#include "generalwaypoint.h"

GeneralWaypoint::GeneralWaypoint()
{
    longitude = 0;
    latitude = 0;
    altitude = 0;
    name.clear();
}

GeneralWaypoint::GeneralWaypoint(float newLongitude, float newLatitude, float newAltitude, QString newName)
{
    longitude = newLongitude;
    latitude = newLatitude;
    altitude = newAltitude;
    name = newName;
}

void GeneralWaypoint::setLongitude(float newLongitude)
{
    longitude = newLongitude;
}

void GeneralWaypoint::setLatitude(float newLatitude)
{
    latitude = newLatitude;
}

void GeneralWaypoint::setPosition(float newLongitude, float newLatitude, float newAltitude)
{
    longitude = newLongitude;
    latitude = newLatitude;
    altitude = newAltitude;
}

void GeneralWaypoint::setName(QString newName)
{
    name = newName;
}

void GeneralWaypoint::setName(const char *newName)
{
    name.clear();
    name.append(newName);
}

void GeneralWaypoint::setName(char *newName, int nameSize)
{
    QByteArray *tempName = new QByteArray(newName,nameSize);
    name.clear();
    name.append(*tempName);
}

void GeneralWaypoint::setAltitude(float newAltitude)
{
    altitude = newAltitude;
}

float GeneralWaypoint::getLongitude()
{
    return longitude;
}

float GeneralWaypoint::getLatitude()
{
    return latitude;
}

float GeneralWaypoint::getAltitude()
{
    return altitude;
}

QString GeneralWaypoint::getName()
{
    return name;
}
