#ifndef MKWIDGET_H
#define MKWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QSpinBox>

class MKWidget : public QTabWidget
{
public:
    MKWidget(QWidget *gridLayout);

    //QTabWidget *tabWidget;
    QWidget *tabVersion;
    QWidget *tabTerminal;

    QPushButton *pushButton;
    QTableWidget *HelicopterAttView;
    QSpinBox *addressSpinBox;

    void SetUpInfoTable(QTableWidget* tableView);


};

#endif // MKWIDGET_H
