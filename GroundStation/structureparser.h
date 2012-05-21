#ifndef STRUCTUREPARSER_H
#define STRUCTUREPARSER_H

#include <qtxml/qxml.h>
#include <QStack>


class QTreeWidget;
class QTreeWidgetItem;
class QString;
class StructureParser: public QXmlDefaultHandler
{
    public:
        StructureParser( QTreeWidget * );
        bool startElement( const QString&, const QString&, const QString& ,
                                const QXmlAttributes& );

        bool endElement( const QString&, const QString&, const QString& );
        void setListView( QTreeWidget * );
    private:
        QStack<QTreeWidgetItem> stack;
        QTreeWidget * table;
};
#endif // STRUCTUREPARSER_H
