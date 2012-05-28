#ifndef GMAPWIDGET_H
#define GMAPWIDGET_H

#include <QWebView>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "MKProtocol/gpsposition.h"
#include "missionwaypoint.h"
#include "missionstaticnode.h"

class GMapWidget : public QWebView
{
    Q_OBJECT
public:
    explicit GMapWidget(QWidget *parent = 0);

public slots:
    void setGMapCenter(const QString &location);
    void setGMapCenter(const QPointF &pos);
    void setGMapCenter(qreal lat, qreal lng);
    void fitMapBounderies(double latNE,double longNE,double latSW,double longSW);
    void fitMapBounderies(GPSPosition NEPoint, GPSPosition SWPoint);
    void addWaypoint(MissionWaypoint Waypoint);
    void addStaticNode(MissionStaticNode staticNode);

    void setGMapZoom(int zoomLevel);

private slots:
    void slotNetworkReply(QNetworkReply *reply);
    void slotLoadFinished(bool ok);

private:
    void runScript(const QString &script);

private:
    QNetworkAccessManager *m_accessManager;
    bool m_initMap;
};

class myWebPage : public QWebPage
{
    virtual QString userAgentForUrl(const QUrl& url) const {
        return "Chrome/1.0";
    }
};

#endif // GMAPWIDGET_H
