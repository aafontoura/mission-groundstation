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

class MKWidget : public QWidget
{
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

    void SetUpInfoTable(QTableWidget* tableView);


};

#endif // MKWIDGET_H
