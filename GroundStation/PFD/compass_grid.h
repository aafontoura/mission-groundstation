#include <qframe.h>
class QwtCompass;

class CompassGrid: public QFrame
{
public:
    CompassGrid( QWidget *parent = NULL );
    QwtCompass *createCompass( int pos );

private:

};
