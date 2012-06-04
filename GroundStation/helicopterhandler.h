#ifndef HELICOPTERHANDLER_H
#define HELICOPTERHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include "missionnode.h"
#include "MKProtocol.h"
#include "MKProtocol/modules/versioninfo.h"
#include "MKProtocol/modules/HelicopterDefs.h"
#include "MKProtocol/parameterrequest.h"
#include "MKProtocol/modules/debuganalogs.h"
#include "MKProtocol/modules/data3d.h"
#include "MKProtocol/modules/osddata.h"
#include "MKProtocol/modules/waypointshandler.h"
#include "MKProtocol/gpsposition.h"

#include "structureparser.h"
#include <qapplication.h>
#include <qfile.h>
#include <QtXml/qxml.h>
#include <qmainwindow.h>
#include <qlabel.h>

class HelicopterHandler : public MissionNode
{
    Q_OBJECT
public:
    HelicopterHandler();
    HelicopterHandler(QString newName, int newAddress);

#ifdef REAL_PORT_COMMUNICATION
    HelicopterHandler(QByteArray SerialPortName, QString newName, int newAddress);
#endif



    bool OpenCloseCommunication();
    bool OpenCommunication();
    void CloseCommunication();

    void CalculateNextState();
    void TriggerTimerState();

    void initMachineState();

    void startTimeout(char expectedType, char expectedFrom, ParameterRequest request);

    QByteArray getFCVersion();
    QByteArray getFCProtoVersion();
    QByteArray getNCVersion();
    QByteArray getNCProtoVersion();


    DebugAnalogs* getFCDebug();
    DebugAnalogs* getNCDebug();

    WaypointsHandler* getWaypointsHandler();
    Data3D* getFCMovementData();
    Data3D* getNCMovementData();

    OSDData *getNavigationData();

    double getCurrentLatitude();
    double getCurrentLongitude();
    double getCurrentAltitude();

    GPSPosition *getCurrentPosition();



    void SendWaypoint(HeliWaypoint::WaypointStruct NewWP);
    void SendWaypoint();

    void sendTargetPosition(double latitude, double longitude);

    int getNumberOfWaypoints();

    int getAddress();
    QString getName();
    void setAddress(int newAddress);
    void setName(QString newName);

    void hubInProtocol(QByteArray data);
    void dataHandler(QByteArray data);






private:
    /* Information */
    //QString name;
    //int address;

    /* Communication Handler */
    MKProtocol *heliProtocol;

    /* Helicopter Attributes */
    VersionInfo      *FCVersion;
    VersionInfo      *NCVersion;
    DebugAnalogs     *NCDebugOut;
    DebugAnalogs     *FCDebugOut;
    Data3D           *NCMovementData;
    Data3D           *FCMovementData;
    OSDData          *NavigationData;
    WaypointsHandler *Waypoints;

    /* Request Timers */
    QTimer *VersionTimer;
    QTimer *MovementTimer;
    QTimer *GeneralTimer;
    QTimer *TimeOutCommand;
    bool GeneralTimerIsOn;

    /* State for machine state (Request heli state) */
    int RequestState;
    int previousState;
    int RequestMode;
    bool initState;
    int timeOutCount;



    char expectedCommandType;
    char expectedCommandFrom;

    ParameterRequest requestedParameter;

    void checkTimeOut(char OriginAddress, char ModuleType);

    void manageTimeOut(char OriginAddress, char ModuleType);
    void manageStateMachine(bool isPeriodic, char OriginAddress, char ModuleType);



private slots:
    void processData(char OriginAddress, char ModuleType, QByteArray Data);
    void hubOutProtocol(QByteArray data);
    void RequestHelicopterState();
    void handleTerminalData(QByteArray data);
    void timedOut();

signals:

    void dataReceived(char,char);    
    void sendBuffer(QByteArray, int);
    void commError();
    void navigationDataReceived(int);
    void FCVersionReceived(QString,int);
    void NCVersionReceived(QString,int);
    void FC3DDatareceived(int,int,int,int);
    void NumberOfWaypointsReceived(int,int);
    void retried(char,char);
    void terminalData(QByteArray,int);



};

#endif // HELICOPTERHANDLER_H
