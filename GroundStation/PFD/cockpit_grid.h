#include <qframe.h>
#include <qpalette.h>
#include <qwt_compass.h>
#include <qwt_compass_rose.h>
#include <qwt_dial_needle.h>

class QwtDial;
class QwtAnalogClock;
class SpeedoMeter;
class AttitudeIndicator;

class CockpitGrid: public QFrame
{
    Q_OBJECT

public:
    CockpitGrid( QWidget *parent = NULL );    

    QwtCompass *d_compass;
    AttitudeIndicator *d_ai;

public Q_SLOTS:
    void changeGradient(double gradient);
    void changeAngle(double angle);

private:
    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial( int pos );
    QwtCompass *createCompass( int pos );

    QwtAnalogClock *d_clock;
    SpeedoMeter *d_speedo;



};
