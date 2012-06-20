#ifndef WAYPOINTSHANDLER_H
#define WAYPOINTSHANDLER_H

#include <QList>
#include "HelicopterDefs.h"
#include "helicopterattribute.h"
#include "gpsposition.h"









class WaypointsHandler : public HelicopterAttribute
{



public:


    WaypointsHandler();
    void UpdateData(QByteArray NewData);
    ParameterRequest SendTargetPosition(GPSPosition newTarget);
    ParameterRequest RequestWaypoint(quint8 WPIndex);
    ParameterRequest RequestWaypoint();
    ParameterRequest SendNewWaypoint();
    ParameterRequest SendNewWaypoint(GPSPosition *NewWaypoint);
    ParameterRequest sendWaypoint();
    void addNewWaypoint(GPSPosition *NewWaypoint);
    ParameterRequest ClearWaypointsList();
    GPSPosition::WaypointStruct CreateNewWaypoint();
    void UpdateNumberOfWaypoints(QByteArray Data);
    quint8 getNumberOfWaypoints();

    int unsentWaypoints();




private:
    QList<GPSPosition*> WaypointsList;
    int waypointsSent;

    // HeliWaypoint::WaypointStruct NewWaypoint;



    quint8 NumberOfWaypoint;
};

#endif // WAYPOINTSHANDLER_H
