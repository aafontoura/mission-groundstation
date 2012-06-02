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

    QProgressBar *progressBarRoll;
    QProgressBar *progressBarPitch;
    QProgressBar *progressBarYaw;


    void SetUpInfoTable(QTableWidget* tableView);

public slots:
    void changeAddresButton_Clicked();

    void UpdateFCVersion(QString version);
    void UpdateNCVersion(QString version);
    void UpdateFC3DData(int winkel0, int winkel1, int winkel2);

    void updateTerminal(QByteArray newData);

signals:
    /* Current address, new address */
    void addressChanged(int,int);

};

#endif // MKWIDGET_H
