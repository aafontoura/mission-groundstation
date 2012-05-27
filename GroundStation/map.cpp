#include "map.h"


Map::Map(QWidget *parent) : QWebView(parent), pendingRequests(0)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    connect(this,SIGNAL(reloadMap()),this,SLOT(loadCoordinates()));

   //load(QUrl("qrc:/www/html/index.html"));
   load(QUrl("file:///C:/Users/Antonio/Documents/Faculdade/TCC/Sw/MissionGroundStation/GroundStation/index.html"));

}


void Map::geoCode(const QString& address)
{
 /*   clearCoordinates();
    QString requestStr( tr("http://maps.google.com/maps/geo?q=%1&output=%2&key=%3")
            .arg(address)
            .arg("csv")
            .arg("ABQIAAAAub_PNjonlRECUZhNhTZI6RTalSVoAkeQnlLd2DdhIgSImdd-MxQB58MV4TTDqzY0VM8rqDQ88gGiWA") );

    manager->get( QNetworkRequest(requestStr) );
    ++pendingRequests;
    */
}

void Map::replyFinished(QNetworkReply *reply)
{
    QString replyStr( reply->readAll() );
    QStringList coordinateStrList = replyStr.split(",");

    if( coordinateStrList.size() == 4) {
        QPointF coordinate( coordinateStrList[2].toFloat(),coordinateStrList[3].toFloat() );
        coordinates << coordinate;
    }

    --pendingRequests;
    if( pendingRequests<1 )
        emit( reloadMap() );
}

void Map::loadCoordinates()
{
    foreach(QPointF point ,coordinates)
{
            this->page()->mainFrame()->evaluateJavaScript(
                            QString("Open(%1,%2)").arg(point.x()).arg(point.y()) );
}

   // QString javascript = QString("getlat()");

    //QVariant latfromjava = this->page()->currentFrame()->evaluateJavaScript(javascript);

    qDebug(qPrintable(this->page()->currentFrame()->evaluateJavaScript("getlat()").toString()));


}

void Map::getMarkerPosition(QString n)
{
    QString javascript = QString("getMarkerPosition(%1)").arg(n);
    qDebug(qPrintable(this->page()->currentFrame()->evaluateJavaScript(javascript).toString()));
}

void Map::getAllMarkersPositions(QString markerCoordinates[][5], int *markersNumber)
{
   *markersNumber = this->markersNumber();

    for(int i=0;i<*markersNumber;i++){
        QString javascript = QString("getMarkerPosition(%1)").arg(QString::number(i));
        QString coordinates = this->page()->currentFrame()->evaluateJavaScript(javascript).toString();

        qDebug(qPrintable(this->page()->currentFrame()->evaluateJavaScript(javascript).toString()));

        QStringList coordinateStrList = coordinates.split(", ");
        QStringList coordinateX = coordinateStrList[0].split("(");
        QStringList coordinateY = coordinateStrList[1].split(")");

        markerCoordinates[i][0]=coordinateX[1];
        markerCoordinates[i][1]=coordinateY[0];
    }
}

void Map::setPosition(float x, float y)
{
    this->page()->mainFrame()->evaluateJavaScript("Open(-30.363882,-51.044922)");
}

void Map::setDroneCurrentPosition(float x, float y)
{
    this->page()->mainFrame()->evaluateJavaScript("DroneCurrentPosition(-30.363882,-51.044922)");
}

void Map::cleanAllMarkers()
{
    this->page()->mainFrame()->evaluateJavaScript("cleanMarkers()");
}

void Map::clearCoordinates()
{
    coordinates.clear();
}

int Map::markersNumber(){
    QString javascript = QString("markersNumber()");
    return this->page()->currentFrame()->evaluateJavaScript(javascript).toInt();
}



/*
void Map::geoCode(QString local)
{
        clearCoordinates();

        QString requestStr( tr("http://maps.google.com/maps/geo?q=%1&output=%2&key=%3")
                        .arg(local)
                        .arg("csv")
                        .arg("ABQIAAAAub_PNjonlRECUZhNhTZI6RTalSVoAkeQnlLd2DdhIgSImdd-MxQB58MV4TTDqzY0VM8rqDQ88gGiWA") ); //.arg("GOOGLE_MAPS_KEY") );

        manager->get( QNetworkRequest(requestStr) );
        ++pendingRequests;
}
void Map::replyFinished(QNetworkReply *reply)
{
    QString replyStr( reply->readAll() );
    QStringList coordinateStrList = replyStr.split(",");

    if( coordinateStrList.size() == 4)
    {
        QPointF coordinate( coordinateStrList[2].toFloat(),coordinateStrList[3].toFloat() );
        coordinates << coordinate;
    }

    --pendingRequests;
    if( pendingRequests<1 )
    {
        emit( reloadMap() );
    }

}

void Map::loadCoordinates()
{
        foreach(QPointF point ,coordinates)
    {
                this->page()->mainFrame()->evaluateJavaScript(
                                QString("Open(%1,%2)").arg(point.x()).arg(point.y()) );
    }
}

void Map::clearCoordinates()
{
    coordinates.clear();
}

*/


