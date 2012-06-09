#include "enginetest.h"

EngineTest::EngineTest() : HelicopterAttribute(ENGINE_TEST,FC_ADDRESS,0)
{
    resetEngines();
}

EngineTest::EngineTest(ParameterRequest Settings) : HelicopterAttribute(Settings)
{
    resetEngines();
}

int EngineTest::getEngineFreq()
{
    return SEND_ENGINE_FREQ;
}

void EngineTest::resetEngines()
{
    for (int i = 0 ; i < NUM_ENGINES ; i++)
        enginesPower[i] = 0;
}


void EngineTest::setEngine(int engineIndex, unsigned char value)
{

    /* Allow just one engine working at a time */
    resetEngines();

    if (engineIndex < NUM_ENGINES)
    {
        enginesPower[engineIndex] = value;
    }

    udpateRequestParameter();

}

void EngineTest::UpdateData(QByteArray NewData)
{
}

void EngineTest::udpateRequestParameter()
{
    QByteArray tempArray;

    tempArray.append((char*)&enginesPower,NUM_ENGINES);

    setRequestData(tempArray);
}


