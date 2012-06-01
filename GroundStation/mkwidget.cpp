#include "mkwidget.h"

MKWidget::MKWidget(QWidget *gridLayout) : QWidget(gridLayout)
{
    //heliWidget = new QWidget(gridLayoutWidget);
    //heliWidget->setObjectName(QString::fromUtf8("heliWidget"));
    MKTabWidget_2 = new QTabWidget(this);
    MKTabWidget_2->setObjectName(QString::fromUtf8("MKTabWidget_2"));
    MKTabWidget_2->setGeometry(QRect(0, 0, 1171, 561));
    tab_6 = new QWidget();
    tab_6->setObjectName(QString::fromUtf8("tab_6"));
    tableWidget_2 = new QTableWidget(tab_6);
    tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
    tableWidget_2->setGeometry(QRect(20, 20, 301, 501));
    addressGroupBox_2 = new QGroupBox(tab_6);
    addressGroupBox_2->setObjectName(QString::fromUtf8("addressGroupBox_2"));
    addressGroupBox_2->setGeometry(QRect(360, 20, 201, 151));
    horizontalLayoutWidget_3 = new QWidget(addressGroupBox_2);
    horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
    horizontalLayoutWidget_3->setGeometry(QRect(10, 20, 181, 41));
    horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    addressInfLabel_2 = new QLabel(horizontalLayoutWidget_3);
    addressInfLabel_2->setObjectName(QString::fromUtf8("addressInfLabel_2"));
    QFont font1;
    font1.setPointSize(10);
    font1.setBold(true);
    font1.setWeight(75);
    addressInfLabel_2->setFont(font1);

    horizontalLayout_3->addWidget(addressInfLabel_2);

    addressIndicationLabel_2 = new QLabel(horizontalLayoutWidget_3);
    addressIndicationLabel_2->setObjectName(QString::fromUtf8("addressIndicationLabel_2"));
    QFont font2;
    font2.setPointSize(10);
    addressIndicationLabel_2->setFont(font2);
    addressIndicationLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    horizontalLayout_3->addWidget(addressIndicationLabel_2);

    verticalLayoutWidget_3 = new QWidget(addressGroupBox_2);
    verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
    verticalLayoutWidget_3->setGeometry(QRect(10, 60, 181, 81));
    verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
    verticalLayout_3->setSpacing(6);
    verticalLayout_3->setContentsMargins(11, 11, 11, 11);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    addressSpinBox_3 = new QSpinBox(verticalLayoutWidget_3);
    addressSpinBox_3->setObjectName(QString::fromUtf8("addressSpinBox_3"));
    addressSpinBox_3->setFont(font2);
    addressSpinBox_3->setButtonSymbols(QAbstractSpinBox::UpDownArrows);

    verticalLayout_3->addWidget(addressSpinBox_3);

    changeAddressButton_3 = new QPushButton(verticalLayoutWidget_3);
    changeAddressButton_3->setObjectName(QString::fromUtf8("changeAddressButton_3"));

    verticalLayout_3->addWidget(changeAddressButton_3);

    MKTabWidget_2->addTab(tab_6, QString());
    tab_7 = new QWidget();
    tab_7->setObjectName(QString::fromUtf8("tab_7"));
    terminalPlainTextEdit_2 = new QPlainTextEdit(tab_7);
    terminalPlainTextEdit_2->setObjectName(QString::fromUtf8("terminalPlainTextEdit_2"));
    terminalPlainTextEdit_2->setGeometry(QRect(10, 20, 1141, 501));
    MKTabWidget_2->addTab(tab_7, QString());

    addressGroupBox_2->setTitle("Address");
    addressInfLabel_2->setText("Address:");
    addressIndicationLabel_2->setText("0");
    changeAddressButton_3->setText("Change Address");
    MKTabWidget_2->setTabText(MKTabWidget_2->indexOf(tab_6), "Information");
    MKTabWidget_2->setTabText(MKTabWidget_2->indexOf(tab_7), "Terminal");

    SetUpInfoTable(tableWidget_2);
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
