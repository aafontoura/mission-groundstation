#ifndef WAYPOINTSHANDLER_H
#define WAYPOINTSHANDLER_H

#include <QList>
#include "HelicopterDefs.h"
#include "helicopterattribute.h"
#include "heliwaypoint.h"









class WaypointsHandler : public HelicopterAttribute
{



public:


    WaypointsHandler();
    void UpdateData(QByteArray NewData);
    ParameterRequest SendTargetPosition(HeliWaypoint newTarget);
    ParameterRequest RequestWaypoint(quint8 WPIndex);
    ParameterRequest RequestWaypoint();
    ParameterRequest SendNewWaypoint();
    ParameterRequest SendNewWaypoint(HeliWaypoint::WaypointStruct NewWaypoint);
    ParameterRequest ClearWaypointsList();
    HeliWaypoint::WaypointStruct CreateNewWaypoint();
    void UpdateNumberOfWaypoints(QByteArray Data);
    quint8 getNumberOfWaypoints();




private:
    QList<HeliWaypoint> WaypointsList;

    HeliWaypoint::WaypointStruct NewWaypoint;



    quint8 NumberOfWaypoint;
};

#endif // WAYPOINTSHANDLER_H
