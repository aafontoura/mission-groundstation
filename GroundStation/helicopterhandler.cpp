#include "helicopterhandler.h"

HelicopterHandler::HelicopterHandler()
{
}

#ifdef REAL_PORT_COMMUNICATION
HelicopterHandler::HelicopterHandler(QByteArray SerialPortName, QString newName, int newAddress)
{

    /* Informations */
    name = newName;
    address = newAddress;

    /* Helicopter Attributes */
    FCVersion = new VersionInfo(FC_ADDRESS);
    NCVersion = new VersionInfo(NC_ADDRESS);
    FCDebugOut = new DebugAnalogs(FC_ADDRESS);
    NCDebugOut = new DebugAnalogs(NC_ADDRESS);
    FCMovementData = new Data3D(FC_ADDRESS,FREQ_INTERVAL_10HZ);
    NCMovementData = new Data3D(NC_ADDRESS,FREQ_INTERVAL_10HZ);
    Waypoints = new WaypointsHandler();

    /* Config General Timer */
    GeneralTimer = new QTimer(this);
    connect(GeneralTimer,SIGNAL(timeout()),this,SLOT(RequestHelicopterState()));


    TimeOutCommand = new QTimer(this);
    connect(TimeOutCommand,SIGNAL(timeout()),this,SLOT(timedOut()));

    RequestState = GET_FC_VERSION;
    RequestMode = NORMAL_REQUEST_MODE;
    initState = true;*/

    /* Configure communication interface */
    heliProtocol = new MKProtocol(SerialPortName);
    if (heliProtocol->OpenInterface())
    {
        connect(heliProtocol,SIGNAL(dataReceived(char,char,QByteArray)),
                this,SLOT(processData(char,char,QByteArray)));
    }
    else
    {
        emit commError();
    }
    RequestHelicopterState();
}
#endif

HelicopterHandler::HelicopterHandler(QString newName, int newAddress)
{
    /* Informations */
    this->setName(newName);
    this->setAddress(newAddress);

    /* Helicopter Attributes */
    FCVersion = new VersionInfo(FC_ADDRESS);
    NCVersion = new VersionInfo(NC_ADDRESS);
    FCDebugOut = new DebugAnalogs(FC_ADDRESS);
    NCDebugOut = new DebugAnalogs(NC_ADDRESS);
    FCMovementData = new Data3D(FC_ADDRESS,FREQ_INTERVAL_10HZ);
    NCMovementData = new Data3D(NC_ADDRESS,FREQ_INTERVAL_10HZ);
    NavigationData = new OSDData();
    Waypoints = new WaypointsHandler();
    Engines = new EngineTest();


    /* Config General Timer */
    GeneralTimer = new QTimer(this);
    connect(GeneralTimer,SIGNAL(timeout()),this,SLOT(CalculateNextState()));
    TimeOutCommand = new QTimer(this);
    connect(TimeOutCommand,SIGNAL(timeout()),this,SLOT(timedOut()));
    engineTimer = new QTimer(this);
    connect(engineTimer,SIGNAL(timeout()),this,SLOT(sendEngineData()));
    //waypointTimer = new QTimer(this);
    //connect(waypointTimer,SIGNAL(timeout()),this,SLOT(sendWaypointData()));

    RequestState = GET_FC_VERSION;
    RequestMode = NORMAL_REQUEST_MODE;
    initState = true;
    timeOutCount = 0;

    /* Configure communication interface */
    heliProtocol = new MKProtocol();

    connect(heliProtocol,SIGNAL(bufferReady(QByteArray)),this,SLOT(hubOutProtocol(QByteArray)));

    connect(heliProtocol,SIGNAL(dataReceived(char,char,QByteArray)),
            this,SLOT(processData(char,char,QByteArray)));

    connect(heliProtocol,SIGNAL(terminalData(QByteArray)),this,SLOT(handleTerminalData(QByteArray)));

}

#ifdef REAL_PORT_COMMUNICATION
bool HelicopterHandler::OpenCloseCommunication()
{
    return (heliProtocol->OpenCloseInterface());
}

bool HelicopterHandler::OpenCommunication()
{
     return (heliProtocol->OpenInterface());
}

void HelicopterHandler::CloseCommunication()
{
    heliProtocol->CloseInterface();
}
#endif




/*************************************************************************************************/
/* Name.........: startTimeout                                                                   */
/* Inputs.......: expectedType - Which Command expect                                            */
/*                expectedFrom - From which address the command should be replied                */
/* Outputs......: none                                                                           */
/* Description..: Start a single timeout for a specific command                                  */
/*************************************************************************************************/
void HelicopterHandler::startTimeout(char expectedType, char expectedFrom, ParameterRequest request)
{
    if (!TimeOutCommand->isActive())
    {
        expectedCommandType = expectedType;
        expectedCommandFrom = expectedFrom;
        requestedParameter = request;
        previousState = RequestState;
        TimeOutCommand->singleShot(200,this,SLOT(timedOut()));
    }
}


QByteArray HelicopterHandler::getFCVersion()
{
    return (FCVersion->getSwVersion());
}

QByteArray HelicopterHandler::getFCProtoVersion()
{
    return (FCVersion->getProtoVersion());
}

QByteArray HelicopterHandler::getNCVersion()
{
    return (NCVersion->getSwVersion());
}

QByteArray HelicopterHandler::getNCProtoVersion()
{
    return (NCVersion->getProtoVersion());
}

DebugAnalogs *HelicopterHandler::getFCDebug()
{
    return FCDebugOut;
}

DebugAnalogs *HelicopterHandler::getNCDebug()
{
    return NCDebugOut;
}

WaypointsHandler *HelicopterHandler::getWaypointsHandler()
{
    return Waypoints;
}

Data3D *HelicopterHandler::getFCMovementData()
{
    return FCMovementData;
}

Data3D *HelicopterHandler::getNCMovementData()
{
    return NCMovementData;
}

OSDData *HelicopterHandler::getNavigationData()
{
    return NavigationData;
}



/*************************************************************************************************/
/* Name.........: SendWaypoint                                                                   */
/* Inputs.......: NewWP - All informations about the new Waypoint                                */
/* Outputs......: none                                                                           */
/* Description..: Send to the Helicopter a new Waypoint                                          */
/*************************************************************************************************/
void HelicopterHandler::SendWaypoint(GPSPosition* NewWP)
{    
    /* TODO: if theres is more modes, prevent to preempt recursively */
    /* preemptedRequestState will be a wrong value */
    if (RequestMode != WAYPOINT_SEND_MODE)
    {
        preemptedRequestState = RequestState;
        RequestState = SEND_WAYPOINT_STATE;
        RequestMode = WAYPOINT_SEND_MODE;
        //GeneralTimer->start(1000);
        heliProtocol->RequestData(Waypoints->SendNewWaypoint(NewWP));
        manageTimeOut(Waypoints->getDestDevice(),Waypoints->getAttributeType());
    }
    else
    {
        Waypoints->addNewWaypoint(NewWP);
    }
    //heliProtocol->RequestData(Waypoints->SendNewWaypoint(NewWP));
}

void HelicopterHandler::clearWaypoints()
{
    /* TODO: if theres is more modes, prevent to preempt recursively */
    /* preemptedRequestState will be a wrong value */
    if (RequestMode != WAYPOINT_SEND_MODE)
    {
        preemptedRequestState = RequestState;
        RequestState = CLEAR_WAYPOINT_STATE;
        RequestMode = WAYPOINT_SEND_MODE;
        GeneralTimer->stop();
        heliProtocol->RequestData(Waypoints->ClearWaypointsList());
        manageTimeOut(Waypoints->getDestDevice(),Waypoints->getAttributeType());
    }
    else
    {
        /* do nothing */
    }
}

void HelicopterHandler::SendWaypoint()
{
    heliProtocol->RequestData(Waypoints->SendNewWaypoint());
}



void HelicopterHandler::sendTargetPosition(double latitude, double longitude)
{
    /*GPSPosition *tempWP = new HeliWaypoint(latitude,longitude,1,"teste");
    heliProtocol->RequestData(Waypoints->SendTargetPosition(*tempWP));*/
    /* delete tempWP; */
}

void HelicopterHandler::setEngineValue(int engine, unsigned char newValue)
{
    if (0 == newValue)
    {
        engineTimer->stop();
    }
    else
    {
        engineTimer->start(Engines->getEngineFreq());
    }

    Engines->setEngine(engine,newValue);
}

void HelicopterHandler::sendEngineData()
{
    heliProtocol->RequestData(Engines->getParameter());
}

void HelicopterHandler::sendWaypoint()
{
    heliProtocol->RequestData(Waypoints->sendWaypoint());
}

int HelicopterHandler::getNumberOfWaypoints()
{
    return (Waypoints->getNumberOfWaypoints());
}

int HelicopterHandler::getAddress()
{
    return address;
}

QString HelicopterHandler::getName()
{
    return name;
}

void HelicopterHandler::setAddress(int newAddress)
{
    address = newAddress;
}

void HelicopterHandler::setName(QString newName)
{
    name = newName;
}

void HelicopterHandler::hubInProtocol(QByteArray data)
{    
    heliProtocol->handleBuffer(data);
}

void HelicopterHandler::dataHandler(QByteArray data)
{
    //QString t = data.left(1);
    RSSI = (int)*(data.left(1).data());
    data = data.right(data.length()-2);
    heliProtocol->handleBuffer(data);
}

void HelicopterHandler::checkTimeOut(char OriginAddress, char ModuleType)
{
    if (TimeOutCommand->isActive())
    {
        if ((OriginAddress == expectedCommandFrom)&&(ModuleType == expectedCommandType))
        {
            TimeOutCommand->stop();
            expectedCommandFrom = 0;
            expectedCommandType = 0;
        }
    }
}



/*************************************************************************************************/
/* Name.........: processData                                                                    */
/* Inputs.......: OriginAddress - Which Heli Layer the information came from                     */
/*                ModuleType - Wich Attribute                                                    */
/*                Data - Package Receive (Already Decoded)                                       */
/* Outputs......: none                                                                           */
/* Description..: Update attribute according to the package received                             */
/*************************************************************************************************/
void HelicopterHandler::processData(char OriginAddress, char ModuleType, QByteArray Data)
{
    if (0 != ModuleType)
    {
        //checkTimeOut(OriginAddress, ModuleType);

        switch(ModuleType)
        {

            case SEND_WAYPOINT_REPLY:
                Waypoints->UpdateNumberOfWaypoints(Data);

                manageStateMachine(Waypoints->isPeriodic(), OriginAddress, ModuleType);
                emit NumberOfWaypointsReceived(this->getNumberOfWaypoints(),this->getAddress());
                break;

            case REQUEST_WAYPOINT_REPLY:
                break;

            case REQUEST_OSD_REPLY:
                NavigationData->UpdateData(Data);
                this->setLatitude((double)NavigationData->getData()->CurrentPosition.Latitude / (double)10000000);
                this->setLongitude((double)NavigationData->getData()->CurrentPosition.Longitude / (double)10000000);
                this->setAltitude((double)NavigationData->getData()->CurrentPosition.Altitude / (double)1000);
                manageStateMachine(NavigationData->isPeriodic(), OriginAddress, ModuleType);
                emit navigationDataReceived(this->getAddress());


                break;

            case VERSION_INFO_HEADER_REPLY:
                switch (OriginAddress)
                {
                    case FC_ADDRESS_REPLY:
                        FCVersion->UpdateData(Data);
                        manageStateMachine(FCVersion->isPeriodic(), OriginAddress, ModuleType);
                        emit FCVersionReceived(this->getFCVersion(),this->getAddress());
                        break;
                    case NC_ADDRESS_REPLY:
                        NCVersion->UpdateData(Data);
                        manageStateMachine(NCVersion->isPeriodic(), OriginAddress, ModuleType);
                        emit NCVersionReceived(this->getNCVersion(),this->getAddress());

                        break;
                    default:
                        break;
                }
                break;

            case DEBUG_OUT_HEADER_REPLY:
               /* switch (OriginAddress)
                {
                    case FC_ADDRESS_REPLY:
                        TriggerTimerState();
                        FCDebugOut->UpdateData(Data);
                        emit FC3DDatareceived(this->getFCMovementData()->getWinkel(0),
                                              this->getFCMovementData()->getWinkel(1),
                                              this->getFCMovementData()->getWinkel(2),
                                              this->getAddress());

                        break;
                    case NC_ADDRESS_REPLY:
                        TriggerTimerState();
                        NCDebugOut->UpdateData(Data);

                        break;
                    default:
                        break;
                }


                break;*/

            case DATA_3D_HEADER_REPLY:
                switch (OriginAddress)
                {
                    case FC_ADDRESS_REPLY:
                        FCMovementData->UpdateData(Data);
                        manageStateMachine(FCMovementData->isPeriodic(), OriginAddress, ModuleType);
                        emit FC3DDatareceived(this->getFCMovementData()->getWinkel(0),
                                              this->getFCMovementData()->getWinkel(1),
                                              this->getFCMovementData()->getWinkel(2),
                                              this->getAddress());

                        break;
                    case NC_ADDRESS_REPLY:
                        NCMovementData->UpdateData(Data);
                        break;
                    default:
                        break;
                }


                break;

            default:

                break;
        }
        emit dataReceived(OriginAddress,ModuleType);


    }
    else
    {}

    /* Check if there are more valid packages available in the incoming buffer */
    heliProtocol->checkPackages();
}

void HelicopterHandler::hubOutProtocol(QByteArray data)
{
    emit (RSSIReceived(RSSI,this->getAddress()));
    emit (sendBuffer(data,this->getAddress()));

}

/*************************************************************************************************/
/* Name.........: RequestHelicopterState                                                         */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Machine State to get all the variables from the helicopter                     */
/*************************************************************************************************/
void HelicopterHandler::RequestHelicopterState()
{
    switch(RequestMode)
    {
        case NORMAL_REQUEST_MODE:
            switch (RequestState)
            {
                case GET_FC_VERSION:
                    heliProtocol->RequestData(FCVersion->RequestNewData());
                    manageTimeOut(FCVersion->getDestDevice(),FCVersion->getAttributeType());


                    break;
                case GET_NC_VERSION:
                    heliProtocol->RequestData(NCVersion->RequestNewData());
                    manageTimeOut(NCVersion->getDestDevice(),NCVersion->getAttributeType());


                    break;
                case GET_FC_3D_INFO:

                    heliProtocol->RequestData(FCMovementData->RequestNewData());
                    GeneralTimer->start(3000);
                    manageTimeOut(FCMovementData->getDestDevice(),FCMovementData->getAttributeType());

                    break;
                case GET_OSD_DATA:
                    heliProtocol->RequestData(NavigationData->RequestNewData());
                    //GeneralTimer->start(1000);
                    manageTimeOut(NavigationData->getDestDevice(),NavigationData->getAttributeType());

                    break;
                case GET_NC_3D_INFO:
                    break;
                case DEBUG_FC_MODE:
                    break;
                case DEBUG_NC_MODE:
                    break;
                default:
                    break;
            }
            break;

        case WAYPOINT_SEND_MODE:
            switch(RequestState)
            {
            case SEND_WAYPOINT_STATE:
                if (Waypoints->unsentWaypoints() > 0)
                {
                    heliProtocol->RequestData(Waypoints->sendWaypoint());
                    manageTimeOut(Waypoints->getDestDevice(),Waypoints->getAttributeType());
                }

                break;
            case CLEAR_WAYPOINT_STATE:
                heliProtocol->RequestData(Waypoints->ClearWaypointsList());
                manageTimeOut(Waypoints->getDestDevice(),Waypoints->getAttributeType());
                break;
            default:
                break;

            }
            break;

        default:
            break;
    }


}

void HelicopterHandler::handleTerminalData(QByteArray data)
{
    emit(terminalData(data,this->getAddress()));
}

void HelicopterHandler::manageTimeOut(char OriginAddress, char ModuleType)
{
    //GeneralTimer->singleShot(1000,this,SLOT(timedOut()));
    TimeOutCommand->start(1000);
    expectedCommandFrom = OriginAddress + 'a';
    expectedCommandType = ModuleType - 0x20;

}

void HelicopterHandler::manageStateMachine(bool isPeriodic, char OriginAddress, char ModuleType)
{
    /* If the expected package was received */
    if ((expectedCommandType == ModuleType) && (expectedCommandFrom == OriginAddress))
    {
        TimeOutCommand->stop();
        timeOutCount = 0;
        if (!isPeriodic)
        {

            expectedCommandType = 0;
            expectedCommandFrom = 0;
            CalculateNextState();

        }
        else
        {
            /* Renew time out */            
            //GeneralTimer->blockSignals(true);
            TimeOutCommand->start(500);
            //expectedCommandType = 0;
            //expectedCommandFrom = 0;
            // GeneralTimer->singleShot(2000,this,SLOT(RequestHelicopterState()));
        }

    }
    else
    {     
    }

}

/*************************************************************************************************/
/* Name.........: CalculateNextState                                                             */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Update the next state according to the Mode chosen and the actual state.       */
/*************************************************************************************************/
void HelicopterHandler::CalculateNextState()

{
    switch(RequestMode)
    {
        case NORMAL_REQUEST_MODE:
            switch(RequestState)
            {
                case GET_FC_VERSION:
                    RequestState = GET_NC_VERSION;
                    break;
                case GET_NC_VERSION:
                    RequestState = GET_FC_3D_INFO;
                    break;
                case GET_FC_3D_INFO:
                    RequestState = GET_OSD_DATA;
                    break;
                case GET_OSD_DATA:
                    RequestState = GET_FC_3D_INFO;
                    break;
                case GET_NC_3D_INFO:
                    break;
                case DEBUG_FC_MODE:
                    break;
                case DEBUG_NC_MODE:
                    break;
                default:
                    break;

            }
            break;
        case WAYPOINT_SEND_MODE:
            switch(RequestState)
            {
            case SEND_WAYPOINT_STATE:
                if (Waypoints->unsentWaypoints() == 0)
                {
                    RequestState = preemptedRequestState;
                    RequestMode = NORMAL_REQUEST_MODE;
                }
                break;
            case CLEAR_WAYPOINT_STATE:
                if (Waypoints->unsentWaypoints() == 0)
                {
                    RequestState = preemptedRequestState;
                    RequestMode = NORMAL_REQUEST_MODE;
                }
                else
                    RequestState = SEND_WAYPOINT_STATE;

                break;
            default:
                break;

            }

            break;

        default:
            break;
    }
    GeneralTimer->stop();
    RequestHelicopterState();


}



void HelicopterHandler::initMachineState()
{
    RequestHelicopterState();
}

void HelicopterHandler::timedOut()
{
    // RequestState = previousState;
    /*heliProtocol->RequestData(FCVersion->RequestNewData());
    startTimeout(VERSION_INFO_HEADER_REPLY,FC_ADDRESS_REPLY,FCVersion->RequestNewData());
    emit retried(expectedCommandType,expectedCommandFrom);*/
    if (++timeOutCount > 4)
        heliProtocol->resetUARTModule();
    this->RequestHelicopterState();



}



