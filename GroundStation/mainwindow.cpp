#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QuadCopter = new HelicopterHandler("COM4");

    // connect(QuadCopter,SIGNAL(dataReceived(char,char)),this,SLOT(processData(char,char)));
    connect(QuadCopter,SIGNAL(FCVersionReceived()),this,SLOT(UpdateFCVersion()));
    connect(QuadCopter,SIGNAL(NCVersionReceived()),this,SLOT(UpdateNCVersion()));
    connect(QuadCopter,SIGNAL(FC3DDatareceived()),this,SLOT(UpdateFC3DData()));
    connect(QuadCopter,SIGNAL(NumberOfWaypointsReceived()),this,SLOT(UpdateNumberOfWP()));
    connect(QuadCopter,SIGNAL(commError()),this,SLOT(CommError()));
    connect(QuadCopter,SIGNAL(retried(char,char)),this,SLOT(informRetry(char,char)));

    SetUpInfoTable();
}

MainWindow::~MainWindow()
{
    //heliProtocol->CloseInterface();
    delete ui;
}

void MainWindow::SetUpInfoTable()
{
    ui->HelicopterAttView->setRowCount(7);
    ui->HelicopterAttView->setColumnCount(2);

    QTableWidgetItem *newItem1,*newItem2,*newItem3,*newItem4,*newItem5;
    QTableWidgetItem *protoV1,*protoV2;
    QStringList header;

    header << "FlightControl Version" << "FlightControl ProtocolVersion" << "NaviCtrl Version";
    header << "NaviControl ProtocolVersion" << "3D 1" << "3D 2" << "3D 3";

    ui->HelicopterAttView->setVerticalHeaderLabels(header);

    //for (int i = 0; i < 3; i++)
    //{
        //ui->HelicopterAttView->setItem(DEBUG_FC_3D_ROW+i,1,&(FC3DDebugItems[i]));
        ui->HelicopterAttView->setCellWidget(DEBUG_FC_3D_ROW,1,ui->progressBar);
        ui->HelicopterAttView->setCellWidget(DEBUG_FC_3D_ROW+1,1,ui->progressBar_2);
        ui->HelicopterAttView->setCellWidget(DEBUG_FC_3D_ROW+2,1,ui->progressBar_3);
    //}

    newItem1 = new QTableWidgetItem("FlightControl Version");
    protoV1 = new QTableWidgetItem("FlightControl ProtocolVersion");
    newItem2 = new QTableWidgetItem("NaviCtrl Version");
    protoV2 = new QTableWidgetItem("NaviControl ProtocolVersion");
    newItem3 = new QTableWidgetItem("3D 1");
    newItem4 = new QTableWidgetItem("3D 2");
    newItem5 = new QTableWidgetItem("3D 3");
    ui->HelicopterAttView->setItem(0,0,newItem1);
    ui->HelicopterAttView->setItem(1,0,protoV1);
    ui->HelicopterAttView->setItem(2,0,newItem2);
    ui->HelicopterAttView->setItem(3,0,protoV2);
    ui->HelicopterAttView->setItem(4,0,newItem3);
    ui->HelicopterAttView->setItem(5,0,newItem4);
    ui->HelicopterAttView->setItem(6,0,newItem5);
    ui->HelicopterAttView->setColumnHidden(0,true);




    ui->HelicopterAttView->resizeColumnToContents(0);//setColumnWidth(0,120);


}

void MainWindow::UpdateFCVersion()
{
    QTableWidgetItem *newVersion = new QTableWidgetItem(tr(QuadCopter->getFCVersion()));
    QTableWidgetItem *newProtoVersion = new QTableWidgetItem(tr(QuadCopter->getFCProtoVersion()));
    ui->HelicopterAttView->setItem(1,1,newProtoVersion);
    ui->HelicopterAttView->setItem(0,1,newVersion);

}

void MainWindow::UpdateNCVersion()
{
    QTableWidgetItem *newVersion = new QTableWidgetItem(tr(QuadCopter->getNCVersion()));
    QTableWidgetItem *newProtoVersion = new QTableWidgetItem(tr(QuadCopter->getNCProtoVersion()));
    ui->HelicopterAttView->setItem(3,1,newProtoVersion);
    ui->HelicopterAttView->setItem(2,1,newVersion);
}

void MainWindow::UpdateFC3DData()
{

    FC3DDebugItems[0].setText(QString::number((QuadCopter->getFCMovementData()->getWinkel(0)+1800)/36));
    FC3DDebugItems[1].setText(QString::number((QuadCopter->getFCMovementData()->getWinkel(1)+1800)/36));
    FC3DDebugItems[2].setText(QString::number(QuadCopter->getFCMovementData()->getWinkel(2)/36));

    ui->progressBar->setValue((QuadCopter->getFCMovementData()->getWinkel(0)+1800)/36);
    ui->progressBar_2->setValue((QuadCopter->getFCMovementData()->getWinkel(1)+1800)/36);
    ui->progressBar_3->setValue(QuadCopter->getFCMovementData()->getWinkel(2)/36);

}

void MainWindow::UpdateNumberOfWP()
{
    ui->WPNumber->display(QuadCopter->getNumberOfWaypoints());
}

void MainWindow::CommError()
{
    QMessageBox msgBox;
    msgBox.setText("PORT ERROR.");
    msgBox.exec();
    ui->plainTextEdit->insertPlainText("Error opening port\n");

    this->close();

}

void MainWindow::informRetry(char typeCommand ,char origin)
{
    ui->plainTextEdit->insertPlainText("Retried\n");
}


/*
void MainWindow::processData(char p1, char p2)
{
    if (0 != p2)
    {
        switch(p2)
        {

            case SEND_WAYPOINT_REPLY:

                ui->plainTextEdit->insertPlainText("WPs: " + QString::number(Waypoints->getNumberOfWaypoints()) + "\n");

                break;

            case REQUEST_WAYPOINT_REPLY:
                break;

            case REQUEST_OSD_REPLY:
                break;

            case VERSION_INFO_HEADER_REPLY:
                switch (p1)
                {
                    case 'b':

                        ui->plainTextEdit->insertPlainText("Version: " + FCVersion->getSwVersion() + "\n");
                        break;
                    case 'c':

                        ui->plainTextEdit->insertPlainText("Version: " + NCVersion->getSwVersion() + "\n");
                        break;
                    default:
                        break;
                }
                break;

            case DEBUG_OUT_HEADER_REPLY:

                ui->lcdNumber->display(HeliDebugOut->getStatus(0));
                ui->lcdNumber_2->display(HeliDebugOut->getStatus(1));
                ui->progressBar->setValue(HeliDebugOut->getAnalog(0));
                ui->progressBar_2->setValue(HeliDebugOut->getAnalog(1));
                //ui->plainTextEdit->insertPlainText("Debug Received!\n");
                //for (int i = 0 ; i < 32 ; i++)
                //    ui->plainTextEdit->insertPlainText(QString::number(HeliDebugOut->getAnalog(i))+" ");
                //ui->plainTextEdit->insertPlainText("\n");
                break;

            case DATA_3D_HEADER_REPLY:

                ui->lcdNumber->setDigitCount(5);
                ui->lcdNumber->display(MovementData->getWinkel(0));
                ui->progressBar->setValue((MovementData->getWinkel(0)+1800)/36);
                ui->progressBar_2->setValue((MovementData->getWinkel(1)+1800)/36);
                ui->progressBar_3->setValue(MovementData->getWinkel(2)/36);
                ui->lcdNumber_2->setDigitCount(5);
                ui->lcdNumber_2->display(MovementData->getCentroid(0));
                ui->progressBar_4->setValue(MovementData->getCentroid(0)/3);
                ui->progressBar_5->setValue(MovementData->getCentroid(1)/3);
                ui->progressBar_6->setValue(MovementData->getCentroid(2)/3);
               // for (int i = 0 ; i < 3 ; i++)
               //     ui->plainTextEdit->insertPlainText(QString::number(MovementData->getWinkel(i))+" ");
               // for (int i = 0 ; i < 3 ; i++)
                //    ui->plainTextEdit->insertPlainText(QString::number(MovementData->getCentroid(i))+" ");
                //ui->plainTextEdit->insertPlainText("\n");
                break;

            default:
                //ui->plainTextEdit->insertPlainText("No Module\n");
                break;
        }

        //ui->plainTextEdit->insertPlainText("Received: " + QString::fromLatin1(Data.toHex())+"\n");


    }
    else;
        //ui->plainTextEdit->insertPlainText(QString::fromLatin1(Data));

    heliProtocol->checkPackages();
}*/

void MainWindow::on_pushButton_clicked()
{
    QuadCopter->SendWaypoint();

}

void MainWindow::on_pushButton_3_clicked()
{


}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{
   //WaypointsHandler::WaypointStruct newWP = Waypoints->CreateNewWaypoint();
   //heliProtocol->RequestData(Waypoints->SendNewWaypoint(newWP));
   //ui->plainTextEdit->insertPlainText("New WP Sent\n");
}

void MainWindow::on_pushButton_6_clicked()
{

}

void MainWindow::on_pushButton_7_clicked()
{
    QuadCopter->OpenCloseCommunication();

}

void MainWindow::on_pushButton_2_clicked()
{
    QTableWidgetItem *newItem = new QTableWidgetItem("teste");

    ui->HelicopterAttView->setRowCount(10);
    ui->HelicopterAttView->setColumnCount(2);
    ui->HelicopterAttView->setItem(1, 1, newItem);
    ui->plainTextEdit->insertPlainText("teste\n");
}

void MainWindow::on_MainWindow_destroyed()
{
    // ui->plainTextEdit->insertPlainText("teste\n");
}
