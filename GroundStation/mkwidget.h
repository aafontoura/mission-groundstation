#ifndef MKWIDGET_H
#define MKWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QSpinBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QCheckBox>
#include <QLCDNumber>

#define DEBUG_FC_3D_ROW 2

class MKWidget : public QWidget
{
    Q_OBJECT
public:
    MKWidget(QWidget *gridLayout);


    QTabWidget *MKTabWidget_2;
    QWidget *tab_6;
    QTableWidget *tableWidget_2;
    QGroupBox *addressGroupBox_2;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *addressInfLabel_2;
    QLabel *addressIndicationLabel_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *addressSpinBox_3;
    QPushButton *changeAddressButton_3;
    QWidget *tab_7;
    QPlainTextEdit *terminalPlainTextEdit_2;

    QWidget *tab_2;
    QGroupBox *groupBox;
    QSlider *verticalSlider;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *enableMotorCheckBox;
    QComboBox *selectMotorComboBox;
    QLCDNumber *motorSpeedIndicator;

    QGroupBox *targetPositionBox;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_5;
    QLabel *targetLatLabel;
    QDoubleSpinBox *targetLatEdit;
    QLabel *targetLongLabel;
    QDoubleSpinBox *targetLongEdit;
    QPushButton *sendTargetPosButton;

    QProgressBar *progressBarRoll;
    QProgressBar *progressBarPitch;
    QProgressBar *progressBarYaw;

    QTableWidgetItem *latitudeIndication;
    QTableWidgetItem *longitudeIndication;
    QTableWidgetItem *altitudeIndication;

    QTableWidgetItem *targetLatitudeIndication;
    QTableWidgetItem *targetLongitudeIndication;
    QTableWidgetItem *targetAltitudeIndication;


    void SetUpInfoTable(QTableWidget* tableView);

public slots:
    void changeAddresButton_Clicked();
    void sendTargetPosButton_Clicked();
    void enableMotorCheckBox_Toggled(bool state);
    void selectMotorComboBox_currentIndexChanged(int index);
    void verticalSlider_sliderMoved(int value);

    void UpdateFCVersion(QString version);
    void UpdateNCVersion(QString version);
    void UpdateFC3DData(int winkel0, int winkel1, int winkel2);

    void updateTerminal(QByteArray newData);

signals:
    /* Current address, new address */
    void addressChanged(int,int);
    void sendTargetPosition(double,double);
    void sendMotorSpeed(int,int);

};

#endif // MKWIDGET_H
