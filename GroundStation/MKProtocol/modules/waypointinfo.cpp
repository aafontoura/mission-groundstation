#include "waypointinfo.h"

WaypointInfo::WaypointInfo() : GPSPosition()
{
}

WaypointInfo::WaypointInfo(WaypointInfo::WaypointStruct newWaypoint)
{
    Waypoint = newWaypoint;
}

void WaypointInfo::setWaypoint(WaypointInfo::WaypointStruct newWaypoint)
{
    Waypoint = newWaypoint;
}

WaypointInfo::WaypointStruct WaypointInfo::getWaypoint()
{
    return Waypoint;
}
