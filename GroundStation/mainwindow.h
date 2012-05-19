#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMessageBox>
// #include "waypointshandler.h"
#include "helicopterhandler.h"


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
    MKProtocol *heliProtocol;

    //WaypointsHandler *Waypoints;

    HelicopterHandler *QuadCopter;

    QTableWidgetItem FC3DDebugItems[NUM_3D_DEBUGS];
    void SetUpInfoTable();



private slots:
    void UpdateFCVersion();
    void UpdateNCVersion();
    void UpdateFC3DData();
    void UpdateNumberOfWP();
    void CommError();
    void informRetry(char typeCommand, char origin);
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_2_clicked();
    void on_MainWindow_destroyed();
};

#endif // MAINWINDOW_H
