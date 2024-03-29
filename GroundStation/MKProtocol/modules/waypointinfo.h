#ifndef WAYPOINTINFO_H
#define WAYPOINTINFO_H

#include <QtGlobal>
#include "gpsposition.h"

class WaypointInfo : GPSPosition
{
public:


    typedef struct
    {
        qint32 Longitude;                                  // in 1E-7 deg
        qint32 Latitude;                                   // in 1E-7 deg
        qint32 Altitude;                                   // in mm
        quint8 Status;                                      // validity of data
    } __attribute__((packed)) GPSPositionStruct;

    typedef struct
    {
        GPSPositionStruct Position;             // the gps position of the waypoint, see ubx.h for details
        qint16 Heading;                    // orientation, 0 no action, 1...360 fix heading, neg. = Index to POI in WP List
        quint8  ToleranceRadius;            // in meters, if the MK is within that range around the target, then the next target is triggered
        quint8  HoldTime;                   // in seconds, if the was once in the tolerance area around a WP, this time defines the delay before the next WP is triggered
        quint8  Event_Flag;                 // future implementation
        quint8  Index;                      // to indentify different waypoints, workaround for bad communications PC <-> NC
        quint8  Type;                       // typeof Point
        quint8  WP_EventChannelValue;       //
        quint8  AltitudeRate;               // rate to change the setpoint
        quint8  Speed;                      // rate to change the Position
        quint8  CamAngle;                   // Camera servo angle
        quint8  Name[4];                    // Name of that point (ASCII)
        quint8  reserve[2];                     // reserve
    } __attribute__((packed)) WaypointStruct;




    WaypointInfo();
    WaypointInfo(WaypointStruct newWaypoint);
    void setWaypoint(WaypointStruct newWaypoint);
    WaypointStruct getWaypoint();

private:
    WaypointStruct Waypoint;
};

#endif // WAYPOINTINFO_H
