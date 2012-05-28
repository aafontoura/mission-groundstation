#include "gmapwidget.h"

#include <QXmlStreamReader>
#include <QNetworkRequest>
#include <QWebFrame>



GMapWidget::GMapWidget(QWidget *parent)
    : QWebView(parent)
    , m_accessManager(new QNetworkAccessManager(this))
    , m_initMap(false)
{
    connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotNetworkReply(QNetworkReply*)));

    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadFinished(bool)));

    //load(QUrl("qrc:/index.html"));
    setPage (new myWebPage());
    load(QUrl("file:///C:/Users/Antonio/Documents/Faculdade/TCC/Sw/MissionGroundStation/GroundStation/index.html"));
}

// wait till the load finished signal before initializing the map trough javascript functions!
// somethimes the geocoding is faster than the webview can load the google map runtime
void GMapWidget::slotLoadFinished(bool ok)
{
    if(!m_initMap && ok) {
        m_initMap = true;

        // load a default location on map init
        setGMapCenter("Porto Alegre, Brasil");
    }
}

// geocode location strings to Latitude / Longitude positions
void GMapWidget::setGMapCenter(const QString &location)
{
    QUrl url("http://maps.googleapis.com/maps/api/geocode/xml");
    url.addQueryItem("address", location);
    url.addQueryItem("sensor", "false");

    QNetworkRequest request(url);

    m_accessManager->get(request);
}

// overload with QPointF
void GMapWidget::setGMapCenter(const QPointF &pos)
{
    setGMapCenter(pos.x(), pos.y());
}

// overload with qreal
void GMapWidget::setGMapCenter(qreal lat, qreal lng)
{
    runScript(QString("setGMapCenter(%1,%2)").arg(lat).arg(lng));
}

void GMapWidget::fitMapBounderies(double latNE, double longNE, double latSW, double longSW)
{
    runScript(QString("fitMapBounderies(%1,%2,%3,%4)").arg(latNE).arg(longNE).arg(latSW).arg(longSW));
}

void GMapWidget::fitMapBounderies(GPSPosition NEPoint, GPSPosition SWPoint)
{
    runScript(QString("fitMapBounderies(%1,%2,%3,%4)").arg(NEPoint.getLatitude()).arg(NEPoint.getLongitude()).arg(SWPoint.getLatitude()).arg(SWPoint.getLongitude()));
}



void GMapWidget::addWaypoint(MissionWaypoint Waypoint)
{
    QString argument = QString("addWaypoint(%1,%2,\"").arg(Waypoint.getLatitude()).arg(Waypoint.getLongitude());
    argument += Waypoint.getName() + "\")";
    runScript(argument);
}

void GMapWidget::addStaticNode(MissionStaticNode staticNode)
{
    QString argument = QString("addStaticNode(%1,%2,\"").arg(staticNode.getLatitude()).arg(staticNode.getLongitude());
    argument += staticNode.identifier + "\")";
    runScript(argument);
}

// set a zoom level on the map
void GMapWidget::setGMapZoom(int zoomLevel)
{
    runScript(QString("setGMapZoom(%1)").arg(zoomLevel));
}

// read out a geocode xml reply from google
void GMapWidget::slotNetworkReply(QNetworkReply *reply)
{
    QXmlStreamReader reader(reply->readAll());

    while(!reader.atEnd()) {

        reader.readNext();

        if(reader.name() == "geometry") {

            reader.readNextStartElement();

            if(reader.name() == "location") {

                reader.readNextStartElement();

                if(reader.name() == "lat") {

                    QPointF pos;

                    pos.setX(reader.readElementText().toFloat());

                    reader.readNextStartElement();

                    if(reader.name() == "lng") {

                        pos.setY(reader.readElementText().toFloat());

                        setGMapCenter(pos);

                        return;
                    }
                }
            }
        }
    }
}

// run a javascript function
void GMapWidget::runScript(const QString &script)
{
    page()->mainFrame()->evaluateJavaScript(script);
}
