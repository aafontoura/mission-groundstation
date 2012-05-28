#ifndef HELICOPTERHANDLER_H
#define HELICOPTERHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include "MKProtocol.h"
#include "modules/versioninfo.h"
#include "modules/HelicopterDefs.h"
#include "parameterrequest.h"
#include "modules/debuganalogs.h"
#include "modules/data3d.h"
#include "modules/waypointshandler.h"

#include "structureparser.h"
#include <qapplication.h>
#include <qfile.h>
#include <QtXml/qxml.h>
#include <qmainwindow.h>
#include <qlabel.h>

class HelicopterHandler : public QObject
{
Q_OBJECT
public:
    HelicopterHandler();
    HelicopterHandler(QByteArray SerialPortName);
    HelicopterHandler(QString newName, int newAddress);

    bool OpenCloseCommunication();
    bool OpenCommunication();
    void CloseCommunication();

    void CalculateNextState();
    void TriggerTimerState();

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

    void SendWaypoint(HeliWaypoint::WaypointStruct NewWP);
    void SendWaypoint();

    int getNumberOfWaypoints();

    int getAddress();
    QString getName();
    void setAddress(int newAddress);
    void setName(QString newName);





private:
    /* Information */
    QString name;
    int address;

    /* Communication Handler */
    MKProtocol *heliProtocol;

    /* Helicopter Attributes */
    VersionInfo      *FCVersion;
    VersionInfo      *NCVersion;
    DebugAnalogs     *NCDebugOut;
    DebugAnalogs     *FCDebugOut;
    Data3D           *NCMovementData;
    Data3D           *FCMovementData;
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



    char expectedCommandType;
    char expectedCommandFrom;

    ParameterRequest requestedParameter;

    void checkTimeOut(char OriginAddress, char ModuleType);

    void manageTimeOut(char OriginAddress, char ModuleType);
    void manageStateMachine(bool isPeriodic, char OriginAddress, char ModuleType);



private slots:
    void processData(char OriginAddress, char ModuleType, QByteArray Data);
    void RequestHelicopterState();
    void timedOut();

signals:
    void dataReceived(char,char);    
    void commError();
    void FCVersionReceived();
    void NCVersionReceived();
    void FC3DDatareceived();
    void NumberOfWaypointsReceived();
    void retried(char typeCommand ,char origin);

};

#endif // HELICOPTERHANDLER_H
