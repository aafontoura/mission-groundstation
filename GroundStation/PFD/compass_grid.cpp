#include <qlayout.h>
#include <qwt_compass.h>
#include <qwt_compass_rose.h>
#include <qwt_dial_needle.h>
#include "compass_grid.h"

CompassGrid::CompassGrid( QWidget *parent ):
    QFrame( parent )
{
    /*QPalette p = palette();
    p.setColor( backgroundRole(), Qt::gray );
    setPalette( p );

    setAutoFillBackground( true );

    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setMargin( 0 );

    QwtCompass *compass = createCompass( i );*/



}

QwtCompass *CompassGrid::createCompass( int pos )
{
    int c;

    QPalette palette0;
    for ( c = 0; c < QPalette::NColorRoles; c++ )
        palette0.setColor( ( QPalette::ColorRole )c, QColor() );

    palette0.setColor( QPalette::Base,
        palette().color( backgroundRole() ).light( 120 ) );
    palette0.setColor( QPalette::WindowText,
        palette0.color( QPalette::Base ) );

    QwtCompass *compass = new QwtCompass( this );
    compass->setLineWidth( 4 );
    compass->setFrameShadow(
        pos <= 2 ? QwtCompass::Sunken : QwtCompass::Raised );

    switch( pos )
    {
        case 0:
        {
            /*
              A compass with a rose and no needle. Scale and rose are
              rotating.
             */
            compass->setMode( QwtCompass::RotateScale );

            QwtSimpleCompassRose *rose = new QwtSimpleCompassRose( 16, 2 );
            rose->setWidth( 0.15 );

            compass->setRose( rose );
            break;
        }
        case 1:
        {
            /*
              A windrose, with a scale indicating the main directions only
             */
            QMap<double, QString> map;
            map.insert( 0.0, "N" );
            map.insert( 90.0, "E" );
            map.insert( 180.0, "S" );
            map.insert( 270.0, "W" );

            compass->setLabelMap( map );

            QwtSimpleCompassRose *rose = new QwtSimpleCompassRose( 4, 1 );
            compass->setRose( rose );

            compass->setNeedle(
                new QwtCompassWindArrow( QwtCompassWindArrow::Style2 ) );
            compass->setValue( 60.0 );
            break;
        }
        case 2:
        {
            /*
              A compass with a rotating needle in darkBlue. Shows
              a ticks for each degree.
             */

            palette0.setColor( QPalette::Base, Qt::darkBlue );
            palette0.setColor( QPalette::WindowText,
                               QColor( Qt::darkBlue ).dark( 120 ) );
            palette0.setColor( QPalette::Text, Qt::white );

            compass->setScaleComponents(
                QwtAbstractScaleDraw::Ticks | QwtAbstractScaleDraw::Labels );
            compass->setScaleTicks( 1, 1, 3 );
            compass->setScale( 36, 5, 0 );

            compass->setNeedle(
                new QwtCompassMagnetNeedle( QwtCompassMagnetNeedle::ThinStyle ) );
            compass->setValue( 220.0 );

            break;
        }
        case 3:
        {
            /*
              A compass without a frame, showing numbers as tick labels.
              The origin is at 220.0
             */
            palette0.setColor( QPalette::Base,
                palette().color( backgroundRole() ) );
            palette0.setColor( QPalette::WindowText, Qt::blue );

            compass->setLineWidth( 0 );

            compass->setScaleComponents( QwtAbstractScaleDraw::Backbone |
                QwtAbstractScaleDraw::Ticks | QwtAbstractScaleDraw::Labels );
            compass->setScaleTicks( 0, 0, 3 );

            QMap<double, QString> map;
            for ( double d = 0.0; d < 360.0; d += 60.0 )
            {
                QString label;
                label.sprintf( "%.0f", d );
                map.insert( d, label );
            }
            compass->setLabelMap( map );
            compass->setScale( 36, 5, 0 );

            compass->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                true, Qt::white ) );
            compass->setOrigin( 220.0 );
            compass->setValue( 20.0 );
            break;
        }
        case 4:
        {
            /*
             A compass showing another needle
             */
            compass->setScaleComponents(
                QwtAbstractScaleDraw::Ticks | QwtAbstractScaleDraw::Labels );
            compass->setScaleTicks( 0, 0, 3 );

            compass->setNeedle( new QwtCompassMagnetNeedle(
                QwtCompassMagnetNeedle::TriangleStyle, Qt::white, Qt::red ) );
            compass->setValue( 220.0 );
            break;
        }
        case 5:
        {
            /*
             A compass with a yellow on black ray
             */
            palette0.setColor( QPalette::WindowText, Qt::black );

            compass->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                false, Qt::yellow ) );
            compass->setValue( 315.0 );
            break;
        }
    }

    QPalette newPalette = compass->palette();
    for ( c = 0; c < QPalette::NColorRoles; c++ )
    {
        const QPalette::ColorRole colorRole = ( QPalette::ColorRole ) c;

        if ( palette0.color( colorRole ).isValid() )
            newPalette.setColor( colorRole, palette0.color( colorRole ) );
    }

    for ( int i = 0; i < QPalette::NColorGroups; i++ )
    {
        QPalette::ColorGroup colorGroup = ( QPalette::ColorGroup )i;

        const QColor light =
            newPalette.color( colorGroup, QPalette::Base ).light( 170 );
        const QColor dark = newPalette.color( colorGroup, QPalette::Base ).dark( 170 );
        const QColor mid = compass->frameShadow() == QwtDial::Raised
            ? newPalette.color( colorGroup, QPalette::Base ).dark( 110 )
            : newPalette.color( colorGroup, QPalette::Base ).light( 110 );

        newPalette.setColor( colorGroup, QPalette::Dark, dark );
        newPalette.setColor( colorGroup, QPalette::Mid, mid );
        newPalette.setColor( colorGroup, QPalette::Light, light );
    }

    compass->setPalette( newPalette );

    return compass;
}
