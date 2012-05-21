#include "structureparser.h"
#include <qstring>
#include <qtreewidget>

StructureParser::StructureParser( QTreeWidget * t )
                : QXmlDefaultHandler()
{
    setListView( t );
}



void StructureParser::setListView( QTreeWidget * t )
{
    table = t;
    // table->setsetSorting( -1 );
    QTreeWidgetItem *  element = new QTreeWidgetItem( "Qualified name", element->type());
    table->addTopLevelItem( "Qualified name" );
    table->addTopLevelItem( "Namespace" );
}



bool StructureParser::startElement( const QString& namespaceURI,
                                    const QString& ,
                                    const QString& qName,
                                    const QXmlAttributes& attributes)
{
    QTreeWidgetItem * element;


    if (!stack.isEmpty())
    {
        QTreeWidgetItem *lastChild = stack.top().firstChild();

        if ( lastChild )
        {
            while ( lastChild->nextSibling() )
                lastChild = lastChild->nextSibling();
        }
        element = new QTreeWidgetItem( stack.top(), lastChild, qName, namespaceURI );
    }
    else
    {
        element = new QTreeWidgetItem( table, qName, namespaceURI );
    }

    stack.push( element );
    element->setOpen( TRUE );
    if ( attributes.length() > 0 ) {
        for ( int i = 0 ; i < attributes.length(); i++ ) {
            new QTreeWidgetItem( element, attributes.qName(i), attributes.uri(i) );
        }
    }
    return TRUE;
}


bool StructureParser::endElement( const QString&, const QString&,
                                  const QString& )
{
    stack.pop();
    return TRUE;
}
