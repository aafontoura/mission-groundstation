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

    //mobileNodesWidgetList = QList<QWidget*>();
    nodesWidgetList = QList<QWidget*>();



    //ui->networkMissionTab->removeTab(3);
    //cockpit = new CockpitGrid(ui->tab);

    ui->networkMissionTab->removeTab(0);
    //ui->tab->hide();
    //ui->MobileNodesTab->hide();
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

MKWidget *MainWindow::getMkCopterNodeWidget(int address)
{
    for (int i = 0 ; i < nodesWidgetList.length() ; i++)
    {
        MKWidget* MkCopterWidget = dynamic_cast<MKWidget*>(nodesWidgetList[i]);
        if (0 != MkCopterWidget)
        {
            if (address == MkCopterWidget->addressIndicationLabel_2->text().toInt())
            {
                return MkCopterWidget;
            }
        }
    }
    return 0;

}

void MainWindow::UpdateNavigationData(int address)
{
    MKWidget *tempCopterWidget = this->getMkCopterNodeWidget(address);
    tempCopterWidget->latitudeIndication->setText(QString::number(mission->getMisisonNode(address)->getLatitude()));
    tempCopterWidget->longitudeIndication->setText(QString::number(mission->getMisisonNode(address)->getLongitude()));
    tempCopterWidget->altitudeIndication->setText(QString::number(mission->getMisisonNode(address)->getAltitude()));

    HelicopterHandler *tempNode = dynamic_cast<HelicopterHandler*>(mission->getMisisonNode(address));
    if(0 != tempNode)
    {

        tempCopterWidget->targetLatitudeIndication->setText(QString::number(((double)tempNode->getNavigationData()->getData()->TargetPosition.Latitude / (double) 10000000)));
        tempCopterWidget->targetLongitudeIndication->setText(QString::number(((double)tempNode->getNavigationData()->getData()->TargetPosition.Longitude) / (double)10000000));
        tempCopterWidget->targetAltitudeIndication->setText(QString::number(((double)tempNode->getNavigationData()->getData()->TargetPosition.Altitude) / (double)1000));
    }

    missionMap->setMobileNodePosition(mission->getMisisonNode(address));


}




void MainWindow::UpdateFCVersion(QString version, int address)
{    
    QTableWidgetItem *newVersion = new QTableWidgetItem(version);
    this->getMkCopterNodeWidget(address)->tableWidget_2->setItem(0,1,newVersion);

    /*for (int i = 0 ; i < nodesWidgetList.length() ; i++)
    {
        MKWidget* MkCopterWidget = dynamic_cast<MKWidget*>(nodesWidgetList[i]);
        if (0 != MkCopterWidget)
        {
            if (address == MkCopterWidget->addressIndicationLabel_2->text().toInt())
            {
                QTableWidgetItem *newVersion = new QTableWidgetItem(version);
                MkCopterWidget->tableWidget_2->setItem(0,1,newVersion);
            }
        }
    }*/

}

void MainWindow::UpdateNCVersion(QString version, int address)
{
    QTableWidgetItem *newVersion = new QTableWidgetItem(version);
    this->getMkCopterNodeWidget(address)->tableWidget_2->setItem(1,1,newVersion);
    /*for (int i = 0 ; i < nodesWidgetList.length() ; i++)
    {
        MKWidget* MkCopterWidget = dynamic_cast<MKWidget*>(nodesWidgetList[i]);
        if (0 != MkCopterWidget)
        {
            if (address == MkCopterWidget->addressIndicationLabel_2->text().toInt())
            {
                MkCopterWidget->UpdateNCVersion(version);
            }
        }
    }*/

}

void MainWindow::UpdateFC3DData(int winkel0, int winkel1, int winkel2, int address)
{
    for (int i = 0 ; i < nodesWidgetList.length() ; i++)
    {
        MKWidget* MkCopterWidget = dynamic_cast<MKWidget*>(nodesWidgetList[i]);
        if (0 != MkCopterWidget)
        {
            if (address == MkCopterWidget->addressIndicationLabel_2->text().toInt())
            {
                MkCopterWidget->UpdateFC3DData(winkel0,winkel1,winkel2);
            }
        }
    }

}

void MainWindow::UpdateTerminal(QByteArray data, int address)
{
    for (int i = 0 ; i < nodesWidgetList.length() ; i++)
    {
        MKWidget* MkCopterWidget = dynamic_cast<MKWidget*>(nodesWidgetList[i]);
        if (0 != MkCopterWidget)
        {
            if (address == MkCopterWidget->addressIndicationLabel_2->text().toInt())
            {
                MkCopterWidget->updateTerminal(data);
            }
        }
    }

}

void MainWindow::UpdateNumberOfWP(int address)
{
    //ui->WPNumber->display(QuadCopter->getNumberOfWaypoints());
}

void MainWindow::changeMapNodeAddress(int address, int newAddress)
{
    missionMap->changeNodeAddress(address,newAddress);
}



void MainWindow::CommError()
{
    QMessageBox msgBox;
    msgBox.setText("PORT ERROR.");
    msgBox.exec();
    //ui->plainTextEdit->insertPlainText("Error opening port\n");

    this->close();

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
        /* Analisar possivel BUG!!!
          dynamic cast pra ponteiro */
        MissionStaticNode* tempStaticNode;
        tempStaticNode = dynamic_cast<MissionStaticNode*>(mission->missionNodesList[i]);


        if (tempStaticNode!=0)
        {
            missionMap->addStaticNode(tempStaticNode);

            staticNodeButtonWidget *newStaticNodeButton = new staticNodeButtonWidget(ui->gridLayoutWidget_2);
            newStaticNodeButton->setAddress(tempStaticNode->getAddress());
            newStaticNodeButton->nameLabel->setText(tempStaticNode->getName());

            nodesWidgetList << newStaticNodeButton;

            QTreeWidgetItem *staticNodeItem = new QTreeWidgetItem(ui->staticNodesTreeWidget);
            staticNodeItem->setText(0, tempStaticNode->getName());

            connect(newStaticNodeButton,SIGNAL(addressChanged(int,int)),mission,SLOT(changeNodeAddress(int,int)));

            ZigBeeTransparentStaticNode* tempZigBeeNode =dynamic_cast<ZigBeeTransparentStaticNode*>(mission->missionNodesList[i]);
            if (tempZigBeeNode!=0)
            {
                connect(tempZigBeeNode,SIGNAL(discrete1Changed(bool)),newStaticNodeButton,SLOT(buttonStateChanged(bool)));
                connect(tempZigBeeNode,SIGNAL(newRSSIReceived(int)),newStaticNodeButton,SLOT(changeSignalQuality(int)));
            }

        }
    }
    if (0 < mission->missionNodesList.length())
    {
        ui->gridLayout_2->removeWidget(ui->staticNodeWidget);
        ui->staticNodeWidget->hide();

        ui->gridLayout_2->addWidget(nodesWidgetList[mission->missionNodesList.length()-1], 0, 1, 1, 1);
    }



    if (0 < nodesWidgetList.length())
    {
        ui->gridLayout_2->addWidget(nodesWidgetList[0], 0, 1, 1, 1);
    }



}

void MainWindow::on_addNewMobileNode_clicked()
{
    addMkCopter();
}

void MainWindow::addMkCopter()
{
    MKWidget *newMkCopter;
    int nodeAddress = mission->getEmptyAddress();
    newMkCopter = new MKWidget(ui->gridLayoutWidget_2);


    QString MobileNodeName = "Quadcopter " + QString::number(nodesWidgetList.length()+1);

    /* Add Widget (MobileNode) to the list */
    nodesWidgetList << newMkCopter;

    /* Add mobile Node to the mission */

    newMkCopter->addressSpinBox_3->setValue(nodeAddress);
    newMkCopter->addressIndicationLabel_2->setText(QString::number(nodeAddress));

    HelicopterHandler *heliHandlerTemp = mission->addMobileNode(MobileNodeName, nodeAddress);
    connect(heliHandlerTemp,SIGNAL(FCVersionReceived(QString,int)),this,SLOT(UpdateFCVersion(QString,int)));
    connect(heliHandlerTemp,SIGNAL(NCVersionReceived(QString,int)),this,SLOT(UpdateNCVersion(QString,int)));
    connect(heliHandlerTemp,SIGNAL(FC3DDatareceived(int,int,int,int)),this,SLOT(UpdateFC3DData(int,int,int,int)));
    connect(heliHandlerTemp,SIGNAL(navigationDataReceived(int)),this,SLOT(UpdateNavigationData(int)));




    /* Hide all others Mobile Nodes */
    if (0 < nodesWidgetList.length())
    {
        ui->gridLayout_2->itemAtPosition(0,1)->widget()->hide();
        ui->gridLayout_2->removeWidget(ui->gridLayout_2->itemAtPosition(0,1)->widget());

    }

    ui->gridLayout_2->addWidget(newMkCopter, 0, 1, 1, 1);
    newMkCopter->show();

    QTreeWidgetItem *staticNodeItem = new QTreeWidgetItem(ui->staticNodesTreeWidget);
    staticNodeItem->setText(0, heliHandlerTemp->getName());

    missionMap->addMobileNode(heliHandlerTemp);

    connect(newMkCopter,SIGNAL(addressChanged(int,int)),mission,SLOT(changeNodeAddress(int,int)));
    connect(newMkCopter,SIGNAL(addressChanged(int,int)),this,SLOT(changeMapNodeAddress(int,int)));
    connect(newMkCopter,SIGNAL(sendTargetPosition(double,double,int)),mission,SLOT(sendTargetPosition(double,double,int)));

}




void MainWindow::on_staticNodesTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if (0 < mission->missionNodesList.length())
    {
        ui->gridLayout_2->itemAtPosition(0,1)->widget()->hide();
        ui->gridLayout_2->removeWidget(ui->gridLayout_2->itemAtPosition(0,1)->widget());


        int i = ui->staticNodesTreeWidget->indexOfTopLevelItem(item);

        ui->gridLayout_2->addWidget(nodesWidgetList[i], 0, 1, 1, 1);
        nodesWidgetList[i]->show();
    }

}


