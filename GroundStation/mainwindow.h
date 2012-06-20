#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QStringList>
#include <QString>
#include <QTableWidgetItem>
#include <QMessageBox>
// #include "waypointshandler.h"
#include "helicopterhandler.h"
#include "missionxmlreader.h"
#include "networkmission.h"
#include <QtXML/QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QSpinBox>
//#include "C:\QtSDK\QWT\examples\dials\cockpit_grid.h"
#include "map.h"
#include "gmapwidget.h"
#include "mkwidget.h"
#include "staticnodebuttonwidget.h"


#define RET_OK true

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    




private:
    Ui::MainWindow *ui;

    // QList<QWidget*> mobileNodesWidgetList;
    // QList<QWidget*> staticNodeWidgetList;
    QList<QWidget*> nodesWidgetList;

    NetworkMission *mission;

    GMapWidget *missionMap;

    //CockpitGrid *cockpit;


    //WaypointsHandler *Waypoints;

    //HelicopterHandler *QuadCopter;

    //QTableWidgetItem FC3DDebugItems[NUM_3D_DEBUGS];
    void SetUpInfoTable(QTableWidget *tableView);
    void addMkCopter();


    MKWidget *getMkCopterNodeWidget(int address);



private slots:
    void UpdateNavigationData(int address);
    void UpdateFCVersion(QString version, int address);
    void UpdateNCVersion(QString version, int address);
    void UpdateFC3DData(int winkel0, int winkel1, int winkel2, int address);
    void UpdateRSSIData(int newRSSI, int address);
    void UpdateNumberOfWP(int address);    

    void changeMapNodeAddress(int address, int newAddress);
    void CommError();
    void open();
    void on_addNewMobileNode_clicked();
    void on_staticNodesTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void UpdateTerminal(QByteArray data,int address);
    void on_assignWPs_clicked();
};

#endif // MAINWINDOW_H
