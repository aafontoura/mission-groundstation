#ifndef ENGINETEST_H
#define ENGINETEST_H

#include "HelicopterDefs.h"
#include "helicopterattribute.h"

#define NUM_ENGINES 16
#define SEND_ENGINE_FREQ 100

class EngineTest : public HelicopterAttribute
{
public:
    EngineTest();
    EngineTest(ParameterRequest Settings);


    int getEngineFreq();
    void resetEngines();
    void setEngine(int engineIndex, unsigned char value);

    void UpdateData(QByteArray NewData);

private:
    void udpateRequestParameter();

    unsigned char enginesPower[16];


};

#endif // ENGINETEST_H
