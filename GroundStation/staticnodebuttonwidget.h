#ifndef STATICNODEBUTTONWIDGET_H
#define STATICNODEBUTTONWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QProgressBar>
#include <QString>
#include <QObject>
/* #include <QtCore/qmath.h> */


class staticNodeButtonWidget : public QWidget
{
    Q_OBJECT
public:
    staticNodeButtonWidget(QWidget *gridLayout);

    QWidget *staticNodeWidget;
    QTabWidget *staticNodeTabWidget;

    QWidget *tab_5;
    QWidget *tab_3;

    QGridLayout *gridLayout_4;
    QLabel *nameLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *addressLabel;
    QLabel *addressNodeLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpinBox *addressSpinBox;
    QPushButton *changeAddressButton;

    QGridLayout *gridLayout_3;
    QProgressBar *RSSILevelBar;
    QLabel *RSSILevelLabel;
    QSpacerItem *verticalSpacer;
    QLabel *buttonLabel;
    QLabel *isPressedLabel;

    QWidget *gridLayoutWidget_4;
    QWidget *gridLayoutWidget_5;

    void setAddress(int newAddress);

private slots:
    void changeAddresButton_Clicked();
    void buttonStateChanged(bool state);
    void changeSignalQuality(int newValue);

signals:
    /* Current address, new address */
    void addressChanged(int,int);
};

#endif // STATICNODEBUTTONWIDGET_H
