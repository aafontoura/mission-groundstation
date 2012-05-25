#ifndef MISSIONXMLREADER_H
#define MISSIONXMLREADER_H

#include <QTreeWidgetItem>
#include <qtxml/QXmlStreamReader>
#include "networkmission.h"
#include "missionwaypoint.h"


#define PRIORITY_NORMAL 2


class MissionXMLReader
{
public:
    MissionXMLReader(QTreeWidget *treeWidget, NetworkMission *missionItem);
    bool read(QIODevice *device);

    QString errorString() const;

private:
    void readMission();
    void readTitle(QTreeWidgetItem *item);
    void readSeparator(QTreeWidgetItem *item);
    void readFolder(QTreeWidgetItem *item);
    void readBookmark(QTreeWidgetItem *item);

    void readInformation(QTreeWidgetItem *item);
    void readInformationName(QTreeWidgetItem *item);
    void readNode(QTreeWidgetItem *item, const QString &nodeName);
    void readDescription(QTreeWidgetItem *item);
    void readPriority(QTreeWidgetItem *item);
    void readTasks(QTreeWidgetItem *item);
    void readTimeStart(QTreeWidgetItem *item);

    void readWaypoint(QTreeWidgetItem *item);
    void readWaypointName(QTreeWidgetItem *item);
    void readWaypointDescription(QTreeWidgetItem *item);
    void readWaypointLatitude(QTreeWidgetItem *item);
    void readWaypointLongitude(QTreeWidgetItem *item);
    void readWaypointAltitude(QTreeWidgetItem *item);



    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);

    QXmlStreamReader xml;
    QTreeWidget *treeWidget;
    NetworkMission *mission;

    MissionWaypoint *waypointTemp;

    QIcon folderIcon;
    QIcon bookmarkIcon;

};

#endif // MISSIONXMLREADER_H



