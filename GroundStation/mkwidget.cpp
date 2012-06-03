#include "mkwidget.h"

MKWidget::MKWidget(QWidget *gridLayout) : QWidget(gridLayout)
{

    MKTabWidget_2 = new QTabWidget(this);
    MKTabWidget_2->setObjectName(QString::fromUtf8("MKTabWidget_2"));
    MKTabWidget_2->setGeometry(QRect(0, 0, 851, 569));
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
    terminalPlainTextEdit_2->setGeometry(QRect(10, 20, 820, 501));
    MKTabWidget_2->addTab(tab_7, QString());

    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    groupBox = new QGroupBox(tab_2);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(20, 30, 271, 201));
    verticalSlider = new QSlider(groupBox);
    verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
    verticalSlider->setGeometry(QRect(30, 30, 19, 160));
    verticalSlider->setOrientation(Qt::Vertical);
    verticalLayoutWidget_2 = new QWidget(groupBox);
    verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
    verticalLayoutWidget_2->setGeometry(QRect(90, 30, 160, 161));
    verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    enableMotorCheckBox = new QCheckBox(verticalLayoutWidget_2);
    enableMotorCheckBox->setObjectName(QString::fromUtf8("enableMotorCheckBox"));

    verticalLayout_2->addWidget(enableMotorCheckBox);

    selectMotorComboBox = new QComboBox(verticalLayoutWidget_2);
    selectMotorComboBox->setObjectName(QString::fromUtf8("selectMotorComboBox"));

    verticalLayout_2->addWidget(selectMotorComboBox);

    motorSpeedIndicator = new QLCDNumber(verticalLayoutWidget_2);
    motorSpeedIndicator->setObjectName(QString::fromUtf8("motorSpeedIndicator"));

    verticalLayout_2->addWidget(motorSpeedIndicator);

    MKTabWidget_2->addTab(tab_2, QString());

    targetPositionBox = new QGroupBox(tab_6);
    targetPositionBox->setObjectName(QString::fromUtf8("targetPositionBox"));
    targetPositionBox->setGeometry(QRect(360, 190, 201, 161));
    gridLayoutWidget_6 = new QWidget(targetPositionBox);
    gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
    gridLayoutWidget_6->setGeometry(QRect(10, 20, 181, 131));
    gridLayout_5 = new QGridLayout(gridLayoutWidget_6);
    gridLayout_5->setSpacing(6);
    gridLayout_5->setContentsMargins(11, 11, 11, 11);
    gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
    gridLayout_5->setVerticalSpacing(30);
    gridLayout_5->setContentsMargins(0, 0, 0, 0);
    targetLatLabel = new QLabel(gridLayoutWidget_6);
    targetLatLabel->setObjectName(QString::fromUtf8("targetLatLabel"));

    gridLayout_5->addWidget(targetLatLabel, 1, 0, 1, 1);





    targetLongLabel = new QLabel(gridLayoutWidget_6);
    targetLongLabel->setObjectName(QString::fromUtf8("targetLongLabel"));

    gridLayout_5->addWidget(targetLongLabel, 2, 0, 1, 1);

    targetLatEdit = new QDoubleSpinBox(gridLayoutWidget_6);
    targetLatEdit->setObjectName(QString::fromUtf8("targetLatEdit"));
    targetLatEdit->setDecimals(5);
    targetLatEdit->setMinimum(-180);
    targetLatEdit->setMaximum(180);

    gridLayout_5->addWidget(targetLatEdit, 1, 1, 1, 1);

    targetLongEdit = new QDoubleSpinBox(gridLayoutWidget_6);
    targetLongEdit->setObjectName(QString::fromUtf8("targetLongEdit"));
    targetLongEdit->setDecimals(5);
    targetLongEdit->setMinimum(-180);
    targetLongEdit->setMaximum(180);

    gridLayout_5->addWidget(targetLongEdit, 2, 1, 1, 1);


    sendTargetPosButton = new QPushButton(gridLayoutWidget_6);
    sendTargetPosButton->setObjectName(QString::fromUtf8("sendTargetPosButton"));

    gridLayout_5->addWidget(sendTargetPosButton, 3, 0, 1, 2);

    addressGroupBox_2->setTitle("Address");
    addressInfLabel_2->setText("Address:");
    addressIndicationLabel_2->setText("0");
    changeAddressButton_3->setText("Change Address");
    MKTabWidget_2->setTabText(MKTabWidget_2->indexOf(tab_6), "Information");
    MKTabWidget_2->setTabText(MKTabWidget_2->indexOf(tab_7), "Terminal");
    MKTabWidget_2->setTabText(MKTabWidget_2->indexOf(tab_2), "Tests");

    targetPositionBox->setTitle("Target Position");
    targetLatLabel->setText("Latitude");
    targetLongLabel->setText("Longitude");
    sendTargetPosButton->setText("Send Target Position");

    groupBox->setTitle("Motor Test");
    enableMotorCheckBox->setText("Enable");
    selectMotorComboBox->clear();
    selectMotorComboBox->insertItems(0, QStringList()
     << "1"
     << "2"
     << "3"
     << "4"
     << "5"
     << "6"
     << "7"
     << "8"
     << "9"
     << "10"
     << "11"
     << "12"
     << "13"
     << "14"
     << "15"
     << "16"
    );

    SetUpInfoTable(tableWidget_2);

    connect(changeAddressButton_3,SIGNAL(clicked()),this,SLOT(changeAddresButton_Clicked()));
    connect(sendTargetPosButton,SIGNAL(clicked()),this,SLOT(sendTargetPosButton_Clicked()));

    connect(enableMotorCheckBox,SIGNAL(toggled(bool)),this,SLOT(enableMotorCheckBox_Toggled(bool)));
    connect(selectMotorComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(selectMotorComboBox_currentIndexChanged(int)));
    connect(verticalSlider,SIGNAL(sliderMoved(int)),this,SLOT(verticalSlider_sliderMoved(int)));
    connect(verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(verticalSlider_sliderMoved(int)));


}


void MKWidget::SetUpInfoTable(QTableWidget* tableView)
{
    tableView->setRowCount(8);
    tableView->setColumnCount(2);

    QStringList header;

    progressBarRoll = new QProgressBar();
    progressBarPitch = new QProgressBar();
    progressBarYaw = new QProgressBar();

    header << "FlightControl Version" << "NaviCtrl Version";
    header << "Roll" << "Pitch" << "Yaw";
    header << "Latitude" << "Longitude" << "Altitude";
    header << "Target Latitude" << "Target Longitude" << "Target Altitude";


    tableView->setVerticalHeaderLabels(header);


    tableView->setCellWidget(DEBUG_FC_3D_ROW,1,progressBarRoll);
    tableView->setCellWidget(DEBUG_FC_3D_ROW+1,1,progressBarPitch);
    tableView->setCellWidget(DEBUG_FC_3D_ROW+2,1,progressBarYaw);

    tableView->setColumnHidden(0,true);




    tableView->resizeColumnToContents(0);//setColumnWidth(0,120);


}

void MKWidget::changeAddresButton_Clicked()
{
    emit(addressChanged(addressIndicationLabel_2->text().toInt(),addressSpinBox_3->value()));
    addressIndicationLabel_2->setText(QString::number(addressSpinBox_3->value()));

}

void MKWidget::sendTargetPosButton_Clicked()
{
    emit sendTargetPosition(targetLatEdit->value(),targetLongEdit->value());
}

void MKWidget::enableMotorCheckBox_Toggled(bool state)
{
    verticalSlider->setValue(0);
    verticalSlider_sliderMoved(0);
}

void MKWidget::selectMotorComboBox_currentIndexChanged(int index)
{
    enableMotorCheckBox_Toggled(0);
}

void MKWidget::verticalSlider_sliderMoved(int value)
{
    motorSpeedIndicator->display(value);
    emit sendMotorSpeed(value,selectMotorComboBox->currentIndex());
}


void MKWidget::UpdateFCVersion(QString version)
{
    QTableWidgetItem *newVersion = new QTableWidgetItem(version);
    tableWidget_2->setItem(0,0,newVersion);

}

void MKWidget::UpdateNCVersion(QString version)
{
    QTableWidgetItem *newVersion = new QTableWidgetItem(version);
    tableWidget_2->setItem(1,0,newVersion);
}

void MKWidget::UpdateFC3DData(int winkel0, int winkel1, int winkel2 )
{
    progressBarRoll->setValue((winkel0+1800)/36);
    progressBarPitch->setValue((winkel1+1800)/36);
    progressBarYaw->setValue(winkel2/36);
}

void MKWidget::updateTerminal(QByteArray newData)
{
    terminalPlainTextEdit_2->insertPlainText(newData);
}

/*void MKWidget::UpdateNumberOfWP(int address)
{
    //ui->WPNumber->display(QuadCopter->getNumberOfWaypoints());
}*/
