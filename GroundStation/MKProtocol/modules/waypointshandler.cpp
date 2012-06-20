#include "waypointshandler.h"

WaypointsHandler::WaypointsHandler() : HelicopterAttribute(REQUEST_WAYPOINT,NC_ADDRESS,0)
{
    NumberOfWaypoint = 0;
    waypointsSent = 0;
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
ParameterRequest WaypointsHandler::SendTargetPosition(GPSPosition newTarget)
{
    QByteArray tempArray;
    GPSPosition::WaypointStruct tempData = newTarget.getWaypointStructData();
    tempArray.append((char*)&tempData,sizeof(GPSPosition::WaypointStruct));

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
    GPSPosition *tempWaypoint = new GPSPosition();
    GPSPosition::WaypointStruct tempData;

    // tempWaypoint->setName("tst");
    // tempWaypoint->setWaypointIndex(NumberOfWaypoint+1);



    tempData = tempWaypoint->getWaypointStructData();

    tempArray.append((char*)&tempData,sizeof(GPSPosition::WaypointStruct));

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
ParameterRequest WaypointsHandler::SendNewWaypoint(GPSPosition*  NewWP)
{
    QByteArray tempArray;
    GPSPosition::WaypointStruct wpt;

    WaypointsList << NewWP;

    if ((WaypointsList.length()-1) == waypointsSent)
    {
        wpt = NewWP->getWaypointStructData();
        wpt.Index = waypointsSent+1;
        /*wpt.Name[0] = getName()[0].toLatin1();
        wpt.Name[1] = getName()[1].toLatin1();
        wpt.Name[2] = getName()[2].toLatin1();
        wpt.Name[3] = getName()[3].toLatin1();*/
        //NewWP.Index = WaypointsList.length();


        tempArray.append((char*)&wpt,sizeof(GPSPosition::WaypointStruct));

        setRequestID(SEND_WAYPOINT);
        setRequestData(tempArray);
        return(getParameter());
    }
    else
    {
        setRequestID(0);
        return(getParameter());
    }

}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::sendWaypoint()
{
    QByteArray tempArray;
    GPSPosition::WaypointStruct wpt;

    if ((WaypointsList.length() > 0) && (waypointsSent < WaypointsList.length()))
    {
        wpt = WaypointsList[waypointsSent]->getWaypointStructData();
        wpt.Index = waypointsSent+1;

        tempArray.append((char*)&wpt,sizeof(GPSPosition::WaypointStruct));


        setRequestID(SEND_WAYPOINT);
        setRequestData(tempArray);
        return(getParameter());
    }
    else
    {
        /* This will make the coordinator to send a dummy msg */
        /* TODO, prevent to send messages in this case */
        setRequestID(0);
        return(getParameter());
    }


}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
void WaypointsHandler::addNewWaypoint(GPSPosition *NewWaypoint)
{
    WaypointsList << NewWaypoint;
}


/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
ParameterRequest WaypointsHandler::ClearWaypointsList()
{
    QByteArray tempArray;
    GPSPosition::WaypointStruct tempWP;

    memset(&tempWP,0,sizeof(GPSPosition::WaypointStruct));

    tempArray.append((char*)&tempWP,sizeof(GPSPosition::WaypointStruct));

    setRequestID(SEND_WAYPOINT);
    setRequestData(tempArray);
    waypointsSent = 0;
    WaypointsList.clear();
    return(getParameter());
}



GPSPosition::WaypointStruct WaypointsHandler::CreateNewWaypoint()
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

    if ((quint8)Data[0] == (waypointsSent+1))
    {
        // WaypointsList << NewWaypoint;
        // WaypointsList.append((NewWaypoint));
        waypointsSent++;
    }
    else
    {
        /* Tratar inconformidade TODO */
        waypointsSent = 0;

        /*if (0 == NumberOfWaypoint)
            WaypointsList.clear();*/
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



/*********************************************************************************/
/* Name.........:                                                                */
/* Inputs.......:                                                                */
/* Outputs......:                                                                */
/* Description..:                                                                */
/*********************************************************************************/
int WaypointsHandler::unsentWaypoints()
{
    return (WaypointsList.length() - waypointsSent);
}
