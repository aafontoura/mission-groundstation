#include "missionxmlreader.h"


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
MissionXMLReader::MissionXMLReader(QTreeWidget *treeWidget, NetworkMission *missionItem)
    : treeWidget(treeWidget) , mission(missionItem)
{
    QStyle *style = treeWidget->style();

    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
                      QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
                      QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));

   waypointTemp = 0;
}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
bool MissionXMLReader::read(QIODevice *device)
{
    xml.setDevice(device);

    if (xml.readNextStartElement())
    {
         if (xml.name() == "mission" && xml.attributes().value("tool_version") == "0.0.1")
             readMission();
         else
             xml.raiseError(QObject::tr("The file is not a Mission version 0.0.1 file."));
    }

    return !xml.error();
}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
QString MissionXMLReader::errorString() const
 {
     return QObject::tr("%1\nLine %2, column %3")
             .arg(xml.errorString())
             .arg(xml.lineNumber())
             .arg(xml.columnNumber());
 }


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void MissionXMLReader::readMission()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "mission");

    /* If there is no waypoint, create a root node for all waypoints */
    QTreeWidgetItem *waypointParent;


    while (xml.readNextStartElement())
    {
        if (xml.name() == "information")
            readInformation(0);
        /*else if (xml.name() == "environment")
            readInvironment(0);*/
        else if (xml.name() == "waypoint")
        {
            if (mission->waypointsList.isEmpty())
            {
                waypointParent = createChildItem(0);
                waypointParent->setText(0,"Waypoints");
            }
            readWaypoint(waypointParent);
        }
        /*else if (xml.name() == "static_node")
            readStaticNode(0);*/
        else
            xml.skipCurrentElement();

        /*
        else if (xml.name() == "folder")
            readFolder(0);
        else if (xml.name() == "bookmark")
            readBookmark(0);
        else if (xml.name() == "separator")
            readSeparator(0);
        else
            xml.skipCurrentElement();*/
    }
}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void MissionXMLReader::readInformation(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "information");

    /* Field tree */
    QTreeWidgetItem *information = createChildItem(item);    
    treeWidget->setItemExpanded(information, true);


    while (xml.readNextStartElement())
    {
        if (xml.name() == "name")
            readInformationName(information);
        else if (xml.name() == "description")
            readDescription(information);
        else if (xml.name() == "tasks")
            readTasks(information);
        else if (xml.name() == "priority")
            readPriority(information);
        /*else if (xml.name() == "latitude_boundaries")
            readLatBound(information);*/
        else
            readNode(information,xml.name().toString());
    }
}


/*************************************************************************************************/
/* Name.........: readWaypoint                                                                   */
/* Inputs.......: item - rootNode treeWidget                                                     */
/* Outputs......: none                                                                           */
/* Description..: Read all the waypoints from xml                                                */
/*************************************************************************************************/
void MissionXMLReader::readWaypoint(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "waypoint");

    /* create root node for all waypoints */
    QTreeWidgetItem *waypoint = createChildItem(item);

    /* initialize waypointTemp */
    waypointTemp = new MissionWaypoint();

    while (xml.readNextStartElement())
    {
        if (xml.name() == "name")
            readWaypointName(waypoint);
        else if (xml.name() == "description")
            readWaypointDescription(waypoint);
        else if (xml.name() == "latitude")
            readWaypointLatitude(waypoint);
        else if (xml.name() == "longitude")
            readWaypointLongitude(waypoint);
        else if (xml.name() == "altitude")
            readWaypointAltitude(waypoint);
        else
            xml.skipCurrentElement();
    }

    mission->waypointsList << *waypointTemp;
    waypointTemp = new MissionWaypoint();
}

/*************************************************************************************************/
/* Name.........: readWaypointDescription                                                        */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the descritpion of the waypoint from XML                                  */
/*************************************************************************************************/
void MissionXMLReader::readWaypointDescription(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "description");

    /* Read information inside the tag */
    QString desc = xml.readElementText();

    /* Update waypoint information */
    waypointTemp->description = desc;

    /* Update Tree (GUI) */
    if (!desc.isEmpty())
    {
        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "description");
        newItem->setText(1, desc);
    }
}

/*************************************************************************************************/
/* Name.........: readWaypointLatitude                                                           */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the latitude of the waypoint from XML                                     */
/*************************************************************************************************/
void MissionXMLReader::readWaypointLatitude(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "latitude");

    /* Read information inside the tag */
    QString lat = xml.readElementText();



    /* Update Tree (GUI) */
    if (!lat.isEmpty())
    {
        /* Update waypoint information */
        waypointTemp->setLatitudeStr(lat);

        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "Latitude");
        newItem->setText(1, lat);
    }
}

/*************************************************************************************************/
/* Name.........: readWaypointLongitude                                                          */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the longitude of the waypoint from XML                                    */
/*************************************************************************************************/
void MissionXMLReader::readWaypointLongitude(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "longitude");

    /* Read information inside the tag */
    QString longit = xml.readElementText();



    /* Update Tree (GUI) */
    if (!longit.isEmpty())
    {
        /* Update waypoint information */
        waypointTemp->setLongitudeStr(longit);

        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "Longitude");
        newItem->setText(1, longit);
    }
}

/*************************************************************************************************/
/* Name.........: readWaypointAltitude                                                           */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the altitude of the waypoint from XML                                     */
/*************************************************************************************************/
void MissionXMLReader::readWaypointAltitude(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "altitude");

    /* Read information inside the tag */
    QString alt = xml.readElementText();



    /* Update Tree (GUI) */
    if (!alt.isEmpty())
    {
        /* Update waypoint information */
        waypointTemp->setAltitudeStr(alt);

        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "Altitude");
        newItem->setText(1, alt);
    }
}


/*************************************************************************************************/
/* Name.........: readWaypointName                                                               */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the name of the waypoint from XML                                         */
/*************************************************************************************************/
void MissionXMLReader::readWaypointName(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "name");

    /* Read information inside the tag */
    QString name = xml.readElementText();

    /* Update mission information */
    waypointTemp->name = name;

    /* Update Tree (GUI) */
    item->setText(0, name);
}


/*************************************************************************************************/
/* Name.........: readNode                                                                       */
/* Inputs.......: Item     - Reference for the treeView                                          */
/*                nodeName - Tag Name                                                            */
/* Outputs......: none                                                                           */
/* Description..: Generic procedure to fill the treeView from any tag                            */
/*************************************************************************************************/
void MissionXMLReader::readNode(QTreeWidgetItem *item,const QString &nodeName )
{
    Q_ASSERT(xml.isStartElement() && xml.name() == nodeName);

    QString desc = xml.readElementText();
    if (!desc.isEmpty())
    {
        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, nodeName);
        newItem->setText(1, desc);
    }
}

/*************************************************************************************************/
/* Name.........: readPriority                                                                   */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the Priority of the mission from XML                                      */
/*************************************************************************************************/
void MissionXMLReader::readPriority(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "priority");

    /* Read information inside the tag */
    QString priority = xml.readElementText();

    /* Update mission information */
    if (priority == "NORMAL")
        mission->missionInformation.priority = PRIORITY_NORMAL;
    else
        mission->missionInformation.priority = 0;

    mission->missionInformation.priorityXML = priority;

    /* Update Tree (GUI) */
    if (!priority.isEmpty())
    {
        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "priority");
        newItem->setText(1, priority);
    }
}

/*************************************************************************************************/
/* Name.........: readTasks                                                                      */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the task of the mission from XML                                          */
/*************************************************************************************************/
void MissionXMLReader::readTasks(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "tasks");

    /* Read information inside the tag */
    QString task = xml.readElementText();

    /* Update mission information */
    mission->missionInformation.tasks = task;

    /* Update Tree (GUI) */
    if (!task.isEmpty())
    {
        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "tasks");
        newItem->setText(1, task);
    }
}





/*************************************************************************************************/
/* Name.........: readDescription                                                                */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the descritpion of the mission from XML                                   */
/*************************************************************************************************/
void MissionXMLReader::readDescription(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "description");

    /* Read information inside the tag */
    QString desc = xml.readElementText();

    /* Update mission information */
    mission->missionInformation.description = desc;

    /* Update Tree (GUI) */
    if (!desc.isEmpty())
    {
        QTreeWidgetItem *newItem = createChildItem(item);

        newItem->setText(0, "description");
        newItem->setText(1, desc);
    }
    // readNode(item,xml.name().toString());
}



/*************************************************************************************************/
/* Name.........: readInformationName                                                            */
/* Inputs.......: item                                                                           */
/* Outputs......: none                                                                           */
/* Description..: Read the name of the mission from XML                                          */
/*************************************************************************************************/
void MissionXMLReader::readInformationName(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "name");

    /* Read information inside the tag */
    QString name = xml.readElementText();

    /* Update mission information */
    mission->missionInformation.name = name;

    /* Update Tree (GUI) */
    item->setText(0, name);
}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
void MissionXMLReader::readTitle(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "title");

    QString title = xml.readElementText();
    item->setText(0, title);
}


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
/*void MissionXMLReader::readSeparator(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "separator");

    QTreeWidgetItem *separator = createChildItem(item);
    separator->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    separator->setText(0, QString(30, 0xB7));
    xml.skipCurrentElement();
}*/


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/
/*void MissionXMLReader::readFolder(QTreeWidgetItem *item)
 {
     Q_ASSERT(xml.isStartElement() && xml.name() == "folder");

     QTreeWidgetItem *folder = createChildItem(item);
     bool folded = (xml.attributes().value("folded") != "no");
     treeWidget->setItemExpanded(folder, !folded);

     while (xml.readNextStartElement()) {
         if (xml.name() == "title")
             readTitle(folder);
         else if (xml.name() == "folder")
             readFolder(folder);
         else if (xml.name() == "bookmark")
             readBookmark(folder);
         else if (xml.name() == "separator")
             readSeparator(folder);
         else
             xml.skipCurrentElement();
     }
 }*/


/*************************************************************************************************/
/* Name.........:                                                                                */
/* Inputs.......: none                                                                           */
/* Outputs......: none                                                                           */
/* Description..:                                                                                */
/*************************************************************************************************/

 QTreeWidgetItem *MissionXMLReader::createChildItem(QTreeWidgetItem *item)
 {
     QTreeWidgetItem *childItem;
     if (item) {
         childItem = new QTreeWidgetItem(item);
     } else {
         childItem = new QTreeWidgetItem(treeWidget);
     }
     childItem->setData(0, Qt::UserRole, xml.name().toString());
     return childItem;
 }




