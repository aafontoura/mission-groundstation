#include "waypointshandler.h"

WaypointsHandler::WaypointsHandler() : HelicopterAttribute(REQUEST_WAYPOINT,NC_ADDRESS,0)
{
    NumberOfWaypoint = 0;
    WaypointsList.clear();
}

void WaypointsHandler::UpdateData(QByteArray NewData)
{

}

/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::SendTargetPosition(HeliWaypoint newTarget)
{
    QByteArray tempArray;
    HeliWaypoint::WaypointStruct tempData = newTarget.getWaypointData();
    tempArray.append((char*)&tempData,sizeof(HeliWaypoint::WaypointStruct));

    setRequestID(SEND_TARGET_POSITION);
    setRequestData(tempArray);
    /* delete tempArray; */

    return(getParameter());
}

/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::RequestWaypoint(quint8 WPIndex)
{
    setRequestID(REQUEST_WAYPOINT);
    setRequestData(WPIndex);
    return(getParameter());
}

/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::RequestWaypoint()
{
    setRequestID(REQUEST_WAYPOINT);
    setRequestData(NumberOfWaypoint);
    return(getParameter());
}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::SendNewWaypoint()
{
    QByteArray tempArray;
    HeliWaypoint *tempWaypoint = new HeliWaypoint();
    HeliWaypoint::WaypointStruct tempData;

    tempWaypoint->setName("tst");
    tempWaypoint->setWaypointIndex(NumberOfWaypoint+1);

    tempData = tempWaypoint->getWaypointData();

    tempArray.append((char*)&tempData,sizeof(HeliWaypoint::WaypointStruct));

    setRequestID(SEND_WAYPOINT);
    setRequestData(tempArray);
    return(getParameter());
}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::SendNewWaypoint(HeliWaypoint::WaypointStruct NewWP)
{
    QByteArray tempArray;
    tempArray.append((char*)&NewWP,sizeof(HeliWaypoint::WaypointStruct));

    setRequestID(SEND_WAYPOINT);
    setRequestData(tempArray);
    return(getParameter());
}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::ClearWaypointsList()
{
    setRequestID(SEND_WAYPOINT);
    setRequestData(0);
    return(getParameter());
}



HeliWaypoint::WaypointStruct WaypointsHandler::CreateNewWaypoint()
{
    // WaypointStruct tempWP;
    /*memset(&NewWaypoint,0,sizeof(WaypointStruct));
    NewWaypoint.Position.Altitude = ALTITUDE_DEFAULT;
    NewWaypoint.Position.Status = NEWDATA;
    NewWaypoint.ToleranceRadius = TOLERANCE_RADIUS_DEFAULT;
    NewWaypoint.Index = NumberOfWaypoint+1;
    NewWaypoint.Name[0] = 't';
    NewWaypoint.Name[0] = 's';
    NewWaypoint.Name[0] = 't';*/

    // WaypointsList << tempWP;

    // return tempWP;

}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
void WaypointsHandler::UpdateNumberOfWaypoints(QByteArray Data)
{
    if ((quint8)Data[0] == (NumberOfWaypoint+1))
    {
        // WaypointsList << NewWaypoint;
        // WaypointsList.append((NewWaypoint));
        NumberOfWaypoint = (quint8)Data[0];
    }
    else
    {
        /* Tratar inconformidade TODO */

        if (0 == NumberOfWaypoint)
            WaypointsList.clear();
    }


    // NumberOfWaypoint = (quint8)Data[0];


}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
quint8 WaypointsHandler::getNumberOfWaypoints()
{
    return(NumberOfWaypoint);
}
