#include "heliwaypoint.h"

HeliWaypoint::HeliWaypoint() : GeneralWaypoint()
{
    waypointIndex = 1;
}

HeliWaypoint::HeliWaypoint(float newLongitude, float newLatitude, float newAltitude, QString newName) : GeneralWaypoint(newLongitude, newLatitude, newAltitude, newName)
{
    waypointIndex = 1;

}

HeliWaypoint::HeliWaypoint(qint32 newLongitude, qint32 newLatitude, qint32 newAltitude, QString newName) : GeneralWaypoint(0,0,0,newName)
{
   setPosition(newLatitude,newLongitude,newAltitude);
   waypointIndex = 1;
}

void HeliWaypoint::setWaypointIndex(int newWPIndex)
{
    waypointIndex = newWPIndex;
}

HeliWaypoint::WaypointStruct HeliWaypoint::getWaypointData()
{
    HeliWaypoint::WaypointStruct tempWaypoint;

    memset(&tempWaypoint,0,sizeof(WaypointStruct));
    tempWaypoint.Position.Latitude = (quint32) getLatitude();
    tempWaypoint.Position.Longitude = (quint32) getLongitude();
    tempWaypoint.Position.Altitude = (qint32) getAltitude();
    tempWaypoint.Position.Status = NEWDATA;
    tempWaypoint.ToleranceRadius = TOLERANCE_RADIUS_DEFAULT;
    tempWaypoint.Index = waypointIndex;
    tempWaypoint.Name[0] = getName()[0].toLatin1();
    tempWaypoint.Name[1] = getName()[1].toLatin1();
    tempWaypoint.Name[2] = getName()[2].toLatin1();
    tempWaypoint.Name[3] = getName()[3].toLatin1();

    return tempWaypoint;

}
