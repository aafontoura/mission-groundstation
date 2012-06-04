#ifndef OSDDATA_H
#define OSDDATA_H
#include "helicopterattribute.h"
#include "HelicopterDefs.h"
#include "waypointinfo.h"
#include "gpsposition.h"
#include <QByteArray>

// ------- NCFlags -------------------------------------
#define NC_FLAG_FREE                            0x01
#define NC_FLAG_PH                              0x02
#define NC_FLAG_CH                              0x04
#define NC_FLAG_RANGE_LIMIT                     0x08
#define NC_FLAG_NOSERIALLINK                    0x10
#define NC_FLAG_TARGET_REACHED                  0x20
#define NC_FLAG_MANUAL                          0x40
#define NC_FLAG_GPS_OK                          0x80

// ------- FCStatusFlags -------------------------------
#define FC_STATUS_MOTOR_RUN                     0x01
#define FC_STATUS_FLY                           0x02
#define FC_STATUS_CALIBRATE                     0x04
#define FC_STATUS_START                         0x08
#define FC_STATUS_EMERGENCY_LANDING             0x10
#define FC_STATUS_LOWBAT                        0x20
#define FC_STATUS_VARIO_TRIM_UP                 0x40
#define FC_STATUS_VARIO_TRIM_DOWN               0x80

// ------- FCStatusFlags2 ------------------------------
#define FC_STATUS2_CAREFREE_ACTIVE              0x01
#define FC_STATUS2_ALTITUDE_CONTROL_ACTIVE      0x02
#define FC_STATUS2_FAILSAFE_ACTIVE              0x04
#define FC_STATUS2_OUT1                         0x08
#define FC_STATUS2_OUT2                         0x10
#define FC_STATUS2_RES1                         0x20
#define FC_STATUS2_RES2                         0x40
#define FC_STATUS2_RES3                         0x80

class OSDData : public HelicopterAttribute
{
public:
    OSDData();
    OSDData(char DestDeviceParam);
    OSDData(char DestDeviceParam, int Period);

    typedef struct
    {
            quint16 Distance;                                   // distance to target in cm
            qint16 Bearing;                                    // course to target in deg
    }  __attribute__((packed)) GPS_PosDev_t;


    typedef struct
    {
        quint8 Version;                                     // version of the data structure
        WaypointInfo::GPSPositionStruct  CurrentPosition;                      // see ubx.h for details
        WaypointInfo::GPSPositionStruct TargetPosition;
        GPS_PosDev_t TargetPositionDeviation;
        WaypointInfo::GPSPositionStruct HomePosition;
        GPS_PosDev_t HomePositionDeviation;
        quint8  WaypointIndex;                              // index of current waypoints running from 0 to WaypointNumber-1
        quint8  WaypointNumber;                             // number of stored waypoints
        quint8  SatsInUse;                                  // number of satellites used for position solution
        qint16 Altimeter;                                  // hight according to air pressure
        qint16 Variometer;                                 // climb(+) and sink(-) rate
        quint16 FlyingTime;                                 // in seconds
        quint8  UBat;                                       // Battery Voltage in 0.1 Volts
        quint16 GroundSpeed;                                // speed over ground in cm/s (2D)
        qint16 Heading;                                    // current flight direction in ° as angle to north
        qint16 CompassHeading;                             // current compass value in °
        qint8  AngleNick;                                  // current Nick angle in 1°
        qint8  AngleRoll;                                  // current Rick angle in 1°
        quint8  RC_Quality;                                 // RC_Quality
        quint8  FCStatusFlags;                              // Flags from FC
        quint8  NCFlags;                                    // Flags from NC
        quint8  Errorcode;                                  // 0 --> okay
        quint8  OperatingRadius;                            // current operation radius around the Home Position in m
        qint16 TopSpeed;                                   // velocity in vertical direction in cm/s
        quint8  TargetHoldTime;                             // time in s to stay at the given target, counts down to 0 if target has been reached
        quint8  FCStatusFlags2;                             // StatusFlags2 (since version 5 added)
        qint16 SetpointAltitude;                           // setpoint for altitude
        quint8  Gas;                                        // for future use
        quint16 Current;                                    // actual current in 0.1A steps
        quint16 UsedCapacity;                               // used capacity in mAh
    } __attribute__((packed)) naviDataType;




    void UpdateData(QByteArray NewData);
    naviDataType *getData();
    //GPSPosition* getCurrentPosition();

private:
    QByteArray AutoSendInterval;
    naviDataType navigationData;
    //GPSPosition currentPosition;
};

#endif // OSDDATA_H
