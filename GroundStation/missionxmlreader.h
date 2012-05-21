#ifndef MISSIONXMLREADER_H
#define MISSIONXMLREADER_H

#include <QTreeWidgetItem>
#include <qtxml/QXmlStreamReader>



class MissionXMLReader
{
public:
    MissionXMLReader(QTreeWidget *treeWidget);
    bool read(QIODevice *device);

    QString errorString() const;

private:
    void readMission();
    void readTitle(QTreeWidgetItem *item);
    void readSeparator(QTreeWidgetItem *item);
    void readFolder(QTreeWidgetItem *item);
    void readBookmark(QTreeWidgetItem *item);

    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);

    QXmlStreamReader xml;
    QTreeWidget *treeWidget;

    QIcon folderIcon;
    QIcon bookmarkIcon;
};

#endif // MISSIONXMLREADER_H



