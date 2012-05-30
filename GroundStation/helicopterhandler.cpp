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
    initState = true;

    /* Configure communication interface */
    heliProtocol = new MKProtocol();

    connect(heliProtocol,SIGNAL(bufferReady(QByteArray)),this,SLOT(hubOutProtocol(QByteArray)));


    connect(heliProtocol,SIGNAL(dataReceived(char,char,QByteArray)),
            this,SLOT(processData(char,char,QByteArray)));

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

/*************************************************************************************************/
/* Name.........: SendWaypoint                                                                   */
/* Inputs.......: NewWP - All informations about the new Waypoint                                */
/* Outputs......: none                                                                           */
/* Description..: Send to the Helicopter a new Waypoint                                          */
/*************************************************************************************************/
void HelicopterHandler::SendWaypoint(HeliWaypoint::WaypointStruct NewWP)
{
    heliProtocol->RequestData(Waypoints->SendNewWaypoint(NewWP));
}

void HelicopterHandler::SendWaypoint()
{
    heliProtocol->RequestData(Waypoints->SendNewWaypoint());
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

                emit NumberOfWaypointsReceived(this->getAddress());
                break;

            case REQUEST_WAYPOINT_REPLY:
                break;

            case REQUEST_OSD_REPLY:
                break;

            case VERSION_INFO_HEADER_REPLY:
                switch (OriginAddress)
                {
                    case FC_ADDRESS_REPLY:
                        FCVersion->UpdateData(Data);
                        manageStateMachine(FCVersion->isPeriodic(), OriginAddress, ModuleType);
                        emit FCVersionReceived(this->getAddress());
                        break;
                    case NC_ADDRESS_REPLY:
                        NCVersion->UpdateData(Data);
                        manageStateMachine(NCVersion->isPeriodic(), OriginAddress, ModuleType);
                        emit NCVersionReceived(this->getAddress());

                        break;
                    default:
                        break;
                }
                break;

            case DEBUG_OUT_HEADER_REPLY:
                switch (OriginAddress)
                {
                    case FC_ADDRESS_REPLY:
                        TriggerTimerState();
                        FCDebugOut->UpdateData(Data);
                        emit FC3DDatareceived(this->getAddress());

                        break;
                    case NC_ADDRESS_REPLY:
                        TriggerTimerState();
                        NCDebugOut->UpdateData(Data);

                        break;
                    default:
                        break;
                }


                break;

            case DATA_3D_HEADER_REPLY:
                switch (OriginAddress)
                {
                    case FC_ADDRESS_REPLY:
                        FCMovementData->UpdateData(Data);
                        manageStateMachine(FCMovementData->isPeriodic(), OriginAddress, ModuleType);
                        emit FC3DDatareceived(this->getAddress());

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
            GeneralTimer->start(2000);
            manageTimeOut(FCMovementData->getDestDevice(),FCMovementData->getAttributeType());

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

    /*switch (RequestState)
    {
        case GET_FC_VERSION:
            GeneralTimer->stop();
            heliProtocol->RequestData(FCVersion->RequestNewData());
           // startTimeout(VERSION_INFO_HEADER_REPLY,FC_ADDRESS_REPLY,FCVersion->RequestNewData());



            break;
        case GET_NC_VERSION:
            heliProtocol->RequestData(NCVersion->RequestNewData());

            CalculateNextState();

            break;
        case GET_FC_3D_INFO:
            GeneralTimer->stop();
            heliProtocol->RequestData(FCMovementData->RequestNewData());

            CalculateNextState();

            break;
        case GET_NC_3D_INFO:
            break;
        case DEBUG_FC_MODE:
            break;
        case DEBUG_NC_MODE:
            break;
        default:
            break;
    }*/
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
        if (!isPeriodic)
        {
            TimeOutCommand->stop();
            expectedCommandType = 0;
            expectedCommandFrom = 0;
            CalculateNextState();
            RequestHelicopterState();
        }
        else
        {
            /* Renew time out */
            TimeOutCommand->stop();
            //GeneralTimer->blockSignals(true);
            TimeOutCommand->start(500);
            //expectedCommandType = 0;
            //expectedCommandFrom = 0;
            // GeneralTimer->singleShot(2000,this,SLOT(RequestHelicopterState()));
        }
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
        default:
            break;
    }


}

/*************************************************************************************************/
/* Name.........: CalculateNextState                                                             */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Trigger the respective timer according to the Request state and mode.          */
/*************************************************************************************************/
void HelicopterHandler::TriggerTimerState()
{
    switch(RequestMode)
    {
        case NORMAL_REQUEST_MODE:
            switch(RequestState)
            {
                case GET_FC_VERSION:
                    if (!GeneralTimer->isActive() && !TimeOutCommand->isActive())
                        GeneralTimer->start();
                    break;
                case GET_NC_VERSION:
                    if (!GeneralTimer->isActive())
                        GeneralTimer->start();
                    break;
                case GET_FC_3D_INFO:
                    if (initState)
                        GeneralTimer->start();
                    else
                        if (!GeneralTimer->isActive())
                        {
                            GeneralTimer->setInterval(TIMER_2_SECONDS);
                            GeneralTimer->start(TIMER_2_SECONDS);
                        }
                            //GeneralTimer->singleShot(TIMER_2_SECONDS,this,SLOT(RequestHelicopterState()));
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
        default:
            break;
    }
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
    this->RequestHelicopterState();



}

