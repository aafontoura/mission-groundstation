#ifndef GENERALWAYPOINT_H
#define GENERALWAYPOINT_H

#include <QString>

class GeneralWaypoint
{
public:
    GeneralWaypoint();
    GeneralWaypoint(float newLongitude, float newLatitude, float newAltitude, QString newName);

    void setLongitudeRad(float newLongitudeRad);
    void setLatitudeRad(float newLatitudeRad);
    void setAltitude(float newAltitude);
    void setPositionRad(float newLongitude, float newLatitude, float newAltitude);

    void setLongitude(float newLongitude);
    void setLatitude(float newLatitude);
    void setPosition(float newLongitude, float newLatitude, float newAltitude);

    void setName(QString newName);
    void setName(QByteArray newName);
    void setName(const char *newName);
    void setName(char* newName,int nameSize);

    float getLongitude();
    float getLatitude();
    float getAltitude();
    QString getName();

private:
    float longitude;
    float latitude;
    float altitude;

    QString name;




};

#endif // GENERALWAYPOINT_H
