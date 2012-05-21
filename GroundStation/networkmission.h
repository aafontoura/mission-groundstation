#ifndef NETWORKMISSION_H
#define NETWORKMISSION_H

#include <QString>

class NetworkMission
{
public:
    NetworkMission();

    typedef struct
    {
        QString name;
        QString description;
        QString tasks;
        int priority;
        QString latBoundaries;
        QString longBoundaries;
        QString altBoundaries;

    } informationType;
};

#endif // NETWORKMISSION_H
