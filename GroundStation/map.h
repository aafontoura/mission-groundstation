#ifndef HEADER_H
#define HEADER_H


#include <QLabel>
#include <QtWebKit/QWebView>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebPage>
#include <QEventLoop>
#include <QApplication>
#include <QDebug>
// #include "../global.h"

#include <math.h>

class QNetworkAccessManager;

class Map : public QWebView
{
    Q_OBJECT

    public:
        Map(QWidget *parent=0);

public slots:
        void replyFinished(QNetworkReply*);
        void loadCoordinates();
        void geoCode(const QString &address);
        //void geoCode(QString local);
        void clearCoordinates();
        void setPosition(float x, float y);
        void getMarkerPosition(QString n);
        void cleanAllMarkers();
        void getAllMarkersPositions(QString markerCoordinates[][5], int *markersNumber);
        int markersNumber();
        void setDroneCurrentPosition(float latitude, float longitude);

signals:
        void reloadMap();

private:
        QNetworkAccessManager *manager;
        QList<QPointF> coordinates;
        int pendingRequests;
};

#endif // HEADER_H
