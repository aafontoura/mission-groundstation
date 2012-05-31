#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*QuadCopter = new HelicopterHandler("COM4");

    // connect(QuadCopter,SIGNAL(dataReceived(char,char)),this,SLOT(processData(char,char)));
    connect(QuadCopter,SIGNAL(FCVersionReceived()),this,SLOT(UpdateFCVersion()));
    connect(QuadCopter,SIGNAL(NCVersionReceived()),this,SLOT(UpdateNCVersion()));
    connect(QuadCopter,SIGNAL(FC3DDatareceived()),this,SLOT(UpdateFC3DData()));
    connect(QuadCopter,SIGNAL(NumberOfWaypointsReceived()),this,SLOT(UpdateNumberOfWP()));
    connect(QuadCopter,SIGNAL(commError()),this,SLOT(CommError()));
    connect(QuadCopter,SIGNAL(retried(char,char)),this,SLOT(informRetry(char,char)));*/


    ui->openAct->setShortcuts(QKeySequence::Open);
    connect(ui->openAct, SIGNAL(triggered()), this, SLOT(open()));

    mission = new NetworkMission("COM4");

    missionMap = new GMapWidget(ui->mapWidget);
    missionMap->show();

    mobileNodesWidgetList = QList<QWidget*>();
    staticNodeWidgetList = QList<QWidget*>();



    //ui->tabWidget->hide();
    // missionMap->setContextMenuPolicy(Qt::);
    //missionMap->setDroneCurrentPosition(-30.363882,-51.044922);

    //fitMapBounderies


    //SetUpInfoTable();





    /* --- */


}

MainWindow::~MainWindow()
{
    //heliProtocol->CloseInterface();
    delete ui;
}

void MainWindow::SetUpInfoTable(QTableWidget* tableView)
{
    tableView->setRowCount(7);
    tableView->setColumnCount(2);

    QTableWidgetItem *newItem1,*newItem2,*newItem3,*newItem4,*newItem5;
    QTableWidgetItem *protoV1,*protoV2;
    QStringList header;

    header << "FlightControl Version" << "FlightControl ProtocolVersion" << "NaviCtrl Version";
    header << "NaviControl ProtocolVersion" << "Roll" << "Pitch" << "Yaw";

    tableView->setVerticalHeaderLabels(header);

    //for (int i = 0; i < 3; i++)
    //{
        //ui->HelicopterAttView->setItem(DEBUG_FC_3D_ROW+i,1,&(FC3DDebugItems[i]));
        //ui->HelicopterAttView->setCellWidget(DEBUG_FC_3D_ROW,1,ui->progressBar);
        //ui->HelicopterAttView->setCellWidget(DEBUG_FC_3D_ROW+1,1,ui->progressBar_2);
        //ui->HelicopterAttView->setCellWidget(DEBUG_FC_3D_ROW+2,1,ui->progressBar_3);
    //}

    newItem1 = new QTableWidgetItem("FlightControl Version");
    protoV1 = new QTableWidgetItem("FlightControl ProtocolVersion");
    newItem2 = new QTableWidgetItem("NaviCtrl Version");
    protoV2 = new QTableWidgetItem("NaviControl ProtocolVersion");
    newItem3 = new QTableWidgetItem("3D 1");
    newItem4 = new QTableWidgetItem("3D 2");
    newItem5 = new QTableWidgetItem("3D 3");
    tableView->setItem(0,0,newItem1);
    tableView->setItem(1,0,protoV1);
    tableView->setItem(2,0,newItem2);
    tableView->setItem(3,0,protoV2);
    tableView->setItem(4,0,newItem3);
    tableView->setItem(5,0,newItem4);
    tableView->setItem(6,0,newItem5);
    tableView->setColumnHidden(0,true);




    tableView->resizeColumnToContents(0);//setColumnWidth(0,120);


}

void MainWindow::UpdateFCVersion(int address)
{
    //QTableWidgetItem *newVersion = new QTableWidgetItem(tr(QuadCopter->getFCVersion()));
    //QTableWidgetItem *newProtoVersion = new QTableWidgetItem(tr(QuadCopter->getFCProtoVersion()));
    /*ui->HelicopterAttView->setItem(1,1,newProtoVersion);
    ui->HelicopterAttView->setItem(0,1,newVersion);*/

}

void MainWindow::UpdateNCVersion(int address)
{
    //QTableWidgetItem *newVersion = new QTableWidgetItem(tr(QuadCopter->getNCVersion()));
    //QTableWidgetItem *newProtoVersion = new QTableWidgetItem(tr(QuadCopter->getNCProtoVersion()));
    /*ui->HelicopterAttView->setItem(3,1,newProtoVersion);
    ui->HelicopterAttView->setItem(2,1,newVersion);*/
}

void MainWindow::UpdateFC3DData(int address)
{

    FC3DDebugItems[0].setText(QString::number((QuadCopter->getFCMovementData()->getWinkel(0)+1800)/36));
    FC3DDebugItems[1].setText(QString::number((QuadCopter->getFCMovementData()->getWinkel(1)+1800)/36));
    FC3DDebugItems[2].setText(QString::number(QuadCopter->getFCMovementData()->getWinkel(2)/36));

    /*ui->progressBar->setValue((QuadCopter->getFCMovementData()->getWinkel(0)+1800)/36);
    ui->progressBar_2->setValue((QuadCopter->getFCMovementData()->getWinkel(1)+1800)/36);
    ui->progressBar_3->setValue(QuadCopter->getFCMovementData()->getWinkel(2)/36);*/

}

void MainWindow::UpdateNumberOfWP(int address)
{
    //ui->WPNumber->display(QuadCopter->getNumberOfWaypoints());
}

void MainWindow::CommError()
{
    QMessageBox msgBox;
    msgBox.setText("PORT ERROR.");
    msgBox.exec();
    //ui->plainTextEdit->insertPlainText("Error opening port\n");

    this->close();

}

void MainWindow::informRetry(char typeCommand ,char origin)
{
    //ui->plainTextEdit->insertPlainText("Retried\n");
}




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
    /*QuadCopter->OpenCloseCommunication();*/

}

void MainWindow::on_pushButton_2_clicked()
{
    //QTableWidgetItem *newItem = new QTableWidgetItem("teste");

    /*ui->HelicopterAttView->setRowCount(10);
    ui->HelicopterAttView->setColumnCount(2);
    ui->HelicopterAttView->setItem(1, 1, newItem);*/
    //ui->plainTextEdit->insertPlainText("teste\n");
}

void MainWindow::on_MainWindow_destroyed()
{
    // ui->plainTextEdit->insertPlainText("teste\n");
}

void MainWindow::on_nameSpace_clicked(const QModelIndex &index)
{

}



void MainWindow::open()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open MDL File"),
                                         QDir::currentPath(),
                                         tr("MDL Files (*.xml)"));
    if (fileName.isEmpty())
        return;

    ui->treeWidget->clear();

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("QXmlStream MDL"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    MissionXMLReader reader(ui->treeWidget, mission);
    if (!reader.read(&file)) {
        QMessageBox::warning(this, tr("QXmlStream MDL"),
                             tr("Parse error in file %1:\n\n%2")
                             .arg(fileName)
                             .arg(reader.errorString()));
    } else {
        statusBar()->showMessage(tr("File loaded"), 2000);
    }
    //missionMap->setGMapCenter(-30.363882,-51.044922);

    /* Adjust map view */
    missionMap->fitMapBounderies(mission->missionInformation.NEPointBound,mission->missionInformation.SWPointBound);

    for (int i = 0 ; i < mission->waypointsList.length() ; i++)
    {
        missionMap->addWaypoint(mission->waypointsList[i]);
    }

    /* Add Widgets in the GUI according to the descripted mission */
    for (int i = 0 ; i < mission->missionNodesList.length() ; i++)
    {
        MissionStaticNode* tempStaticNode;
        tempStaticNode = dynamic_cast<MissionStaticNode*>(mission->missionNodesList[i]);


        if (tempStaticNode!=0)
        {
            missionMap->addStaticNode(*tempStaticNode);

            staticNodeButtonWidget *newStaticNodeButton = new staticNodeButtonWidget(ui->gridLayoutWidget_2);
            newStaticNodeButton->setAddress(tempStaticNode->getAddress());

            staticNodeWidgetList << newStaticNodeButton;
            QTreeWidgetItem *staticNodeItem = new QTreeWidgetItem(ui->staticNodesTreeWidget);
            staticNodeItem->setData(0, Qt::UserRole, tempStaticNode->getName());

            connect(newStaticNodeButton,SIGNAL(addressChanged(int,int)),mission,SLOT(changeNodeAddress(int,int)));
        }
    }

    if (0 < staticNodeWidgetList.length())
    {
        ui->gridLayout_2->addWidget(staticNodeWidgetList[0], 0, 1, 1, 1);
    }


    //missionMap->setGMapCenter(mission->waypointsList[0].getLatitude(),mission->waypointsList[0].getLongitude());
    //missionMap->setDroneCurrentPosition(-30.363882,-51.044922);

}

void MainWindow::on_addNewMobileNode_clicked()
{

    MKWidget *newMkCopter;

    newMkCopter = new MKWidget(ui->gridLayoutWidget);

    newMkCopter->setObjectName(QString::fromUtf8("MobileNode" + QString::number(mobileNodesWidgetList.length()+1).toLatin1()));


    newMkCopter->addressSpinBox->setValue(mobileNodesWidgetList.length()+1);





    QString MobileNodeName = "Quadcopter " + QString::number(mobileNodesWidgetList.length()+1);

    /* Add Widget (MobileNode) to the list */
    mobileNodesWidgetList << newMkCopter;

    /* Add mobile Node to the mission */
    mission->addMobileNode(MobileNodeName, mobileNodesWidgetList.length()+1);


    /* Hide all others Mobile Nodes */
    ui->gridLayout->removeItem(ui->tempSpacer);
    if (mobileNodesWidgetList.length()>1)
    {
        ui->gridLayout->removeWidget(mobileNodesWidgetList[mobileNodesWidgetList.length()-2]);
        mobileNodesWidgetList[mobileNodesWidgetList.length()-2]->hide();
    }


    ui->gridLayout->addWidget(newMkCopter, 1, 0, 1, 3);


    ui->mobileNodeNameLabel->setText(MobileNodeName.toLatin1());
    ui->selectMobileNodeCombo->addItem(MobileNodeName);
    ui->selectMobileNodeCombo->setCurrentIndex(ui->selectMobileNodeCombo->count()-1);

}
