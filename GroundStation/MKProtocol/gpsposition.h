#ifndef GPSPOSITION_H
#define GPSPOSITION_H

#include <QString>

/* Waypoints */
// type of point
#define GPS_POINT_TYPE_INVALID 255
#define GPS_POINT_TYPE_WPT  0
#define GPS_POINT_TYPE_POI  1

// status
#define GPS_INVALID         0x00
#define GPS_NEWDATA         0x01
#define GPS_PROCESSED       0x02

#define GPS_ALTITUDE_DEFAULT    10000   /* 10 meters */
#define GPS_LONGITUDE_DEFAULT   0
#define GPS_LATITUDE_DEFAULT    0
#define GPS_HEADING_DEFAULT     0
#define GPS_TOLERANCE_RADIUS_DEFAULT    1
#define GPS_HOLD_TIME_DEFAULT           15
#define GPS_TYPE_WAYPOINT_DEFAULT       0


class GPSPosition
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
            quint8  pointType;                       // typeof Point
            quint8  WP_EventChannelValue;       //
            quint8  AltitudeRate;               // rate to change the setpoint
            quint8  Speed;                      // rate to change the Position
            quint8  CamAngle;                   // Camera servo angle
            quint8  Name[4];                    // Name of that point (ASCII)
        quint8  reserve[2];                     // reserve
    } __attribute__((packed)) WaypointStruct;


    GPSPosition();
    GPSPosition(double lat, double longit, double alt);
    GPSPosition(QString longit, QString lat, double alt = 0);

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

    WaypointStruct getWaypointStructData();





private:
   double longitude;
   double latitude;
   double altitude;


};

#endif // GPSPOSITION_H
