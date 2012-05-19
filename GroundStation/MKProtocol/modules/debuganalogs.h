#ifndef DEBUGANALOGS_H
#define DEBUGANALOGS_H
#include "helicopterattribute.h"
#include "HelicopterDefs.h"
#include <QByteArray>

class DebugAnalogs : public HelicopterAttribute
{
public:
    DebugAnalogs();
    DebugAnalogs(char DestDeviceParam);
    DebugAnalogs(char DestDeviceParam, int Period);
    void UpdateData(QByteArray NewData);
    unsigned char getStatus(int index);
    signed int getAnalog(int index);

private:
    struct str_DebugOut
    {
     unsigned char Status[2];
     qint16 Analog[32];    // Debugvalue can be displayed in MK-Tool as value or graph
    } DebugValues;

    QByteArray AutoSendInterval;
};

#endif // DEBUGANALOGS_H

/******************* Analogs ******************************/

/*    0 - IntegralNick / (EE_Parameter.GyroAccFaktor * 4);
    1 - IntegralRoll / (EE_Parameter.GyroAccFaktor * 4);
    2 - Mittelwert_AccNick / 4;
    3 - Mittelwert_AccRoll / 4;
    4 - (signed int) AdNeutralGier - AdWertGier;
    5 - HoehenWert/5;
    6 - AdWertAccHoch;//(Mess_Integral_Hoch / 512);// Aktuell_az;
    8 - KompassValue;
    9 - UBat;
    10 - SenderOkay;
    11 - ErsatzKompassInGrad;
    12 - Motor[0].SetPoint;
    13 - Motor[1].SetPoint;
    14 - Motor[2].SetPoint;
    15 - Motor[3].SetPoint;
    20 - ServoNickValue;
    22 - Capacity.ActualCurrent;
    23 - Capacity.UsedCapacity;
    24 - SollHoehe/5;
//    22 - FromNaviCtrl_Value.GpsZ;
//    29 - FromNaviCtrl_Value.SerialDataOkay;
    27 - KompassSollWert;
    29 - Capacity.MinOfMaxPWM;
    30 - GPS_Nick;
    31 - GPS_Roll;*/
