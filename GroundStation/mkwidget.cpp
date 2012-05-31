#include "mkwidget.h"

MKWidget::MKWidget(QWidget *gridLayout) : QTabWidget(gridLayout)
{
    /* Create Tab Widget */
    //tabWidget = new QTabWidget(gridLayout);
    /*tabWidget->setObjectName(QString::fromUtf8("MobileNode" + QString::number(mobileNodesWidgetList.length()+1).toLatin1()));*/
    this->setEnabled(true);

        /* Create Tab */
        tabVersion = new QWidget();
        tabVersion->setObjectName(QString::fromUtf8("tabVersion"));

            /* Create info table */
            HelicopterAttView = new QTableWidget(tabVersion);
            HelicopterAttView->setObjectName(QString::fromUtf8("HelicopterAttView"));
            HelicopterAttView->setGeometry(QRect(20, 20, 411, 300));

            SetUpInfoTable(HelicopterAttView);

            /* Create a pushbutton */
            pushButton = new QPushButton(tabVersion);
            pushButton->setObjectName(QString::fromUtf8("pushButton_7"));
            pushButton->setGeometry(QRect(10, 470, 150, 23));
            pushButton->setText("Open Communication");

            /* Create an address spinBox */
            addressSpinBox = new QSpinBox(tabVersion);
            addressSpinBox->setObjectName(QString::fromUtf8("addressSpinBox"));
            addressSpinBox->setGeometry(QRect(450, 20, 75, 23));
            /* addressSpinBox->setValue(mobileNodesWidgetList.length()+1); */
            addressSpinBox->setMaximum(65534);
            addressSpinBox->setMinimum(1);
            addressSpinBox->setSingleStep(1);

        this->addTab(tabVersion, QString());
        this->setTabText(0,"Info");

        /* Create Tab */
        tabTerminal = new QWidget();
        tabTerminal->setObjectName(QString::fromUtf8("tabTerminal"));
        this->addTab(tabTerminal, QString());
}


void MKWidget::SetUpInfoTable(QTableWidget* tableView)
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
