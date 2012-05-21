#include "missionxmlreader.h"

MissionXMLReader::MissionXMLReader(QTreeWidget *treeWidget)
     : treeWidget(treeWidget)
{
    QStyle *style = treeWidget->style();

    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
                      QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
                      QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
}


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


QString MissionXMLReader::errorString() const
 {
     return QObject::tr("%1\nLine %2, column %3")
             .arg(xml.errorString())
             .arg(xml.lineNumber())
             .arg(xml.columnNumber());
 }

void MissionXMLReader::readMission()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "mission");

    while (xml.readNextStartElement())
    {
        if (xml.name() == "information")
            readInformation(0);
        /*else if (xml.name() == "environment")
            readInvironment(0);
        else if (xml.name() == "waypoint")
            readWaypoint(0);
        else if (xml.name() == "static_node")
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

void MissionXMLReader::readInformation(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "information");

    QTreeWidgetItem *information = createChildItem(item);
    // bool folded = (xml.attributes().value("folded") != "no");
    treeWidget->setItemExpanded(information, true);
    // information->setText("Information");

    while (xml.readNextStartElement())
    {

        if (xml.name() == "name")
            readName(information);
        /*else if (xml.name() == "latitude_boundaries")
            readLatBound(information);*/
        else
            readNode(information,xml.name().toString());
    }
}

void MissionXMLReader::readNode(QTreeWidgetItem *item,const QString &nodeName )
{
    Q_ASSERT(xml.isStartElement() && xml.name() == nodeName);

    QString desc = xml.readElementText();
    if (!desc.isEmpty())
    {
        QTreeWidgetItem *newItem = createChildItem(item);
        // QTreeWidgetItem *newItemDesc = createChildItem(newItem);

        newItem->setText(0, nodeName);
        newItem->setText(1, desc);
    }
}

void MissionXMLReader::readTimeStart(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "time_start");

    QTreeWidgetItem *timerStartItem = createChildItem(item);

    QString time_start = xml.readElementText();
    timerStartItem->setText(0, time_start);
}

void MissionXMLReader::readTasks(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "tasks");

    QTreeWidgetItem *tasksItem = createChildItem(item);

    QString tasks = xml.readElementText();
    tasksItem->setText(0, tasks);
}

void MissionXMLReader::readDescription(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "description");

    QTreeWidgetItem *descriptionItem = createChildItem(item);
    QString description = xml.readElementText();
    descriptionItem->setText(0, description);
}


void MissionXMLReader::readName(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "name");

    // QTreeWidgetItem *nameItem = createChildItem(item);

    QString name = xml.readElementText();
    item->setText(0, name);
}



void MissionXMLReader::readTitle(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "title");

    QString title = xml.readElementText();
    item->setText(0, title);
}

void MissionXMLReader::readSeparator(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "separator");

    QTreeWidgetItem *separator = createChildItem(item);
    separator->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    separator->setText(0, QString(30, 0xB7));
    xml.skipCurrentElement();
}

void MissionXMLReader::readFolder(QTreeWidgetItem *item)
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
 }

 void MissionXMLReader::readBookmark(QTreeWidgetItem *item)
 {
     Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");

     QTreeWidgetItem *bookmark = createChildItem(item);
     bookmark->setFlags(bookmark->flags() | Qt::ItemIsEditable);
     bookmark->setIcon(0, bookmarkIcon);
     bookmark->setText(0, QObject::tr("Unknown title"));
     bookmark->setText(1, xml.attributes().value("href").toString());

     while (xml.readNextStartElement()) {
         if (xml.name() == "title")
             readTitle(bookmark);
         else
             xml.skipCurrentElement();
     }
 }

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

