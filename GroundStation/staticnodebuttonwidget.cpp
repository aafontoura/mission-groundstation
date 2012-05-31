#include "staticnodebuttonwidget.h"

staticNodeButtonWidget::staticNodeButtonWidget(QWidget *gridLayout) : QWidget(gridLayout)
{

    //this->setObjectName(QString::fromUtf8("staticNodeWidget"));
    staticNodeTabWidget = new QTabWidget(this);
    staticNodeTabWidget->setObjectName(QString::fromUtf8("staticNodeTabWidget"));
    staticNodeTabWidget->setGeometry(QRect(0, 0, 851, 611));
    tab_5 = new QWidget();
    tab_5->setObjectName(QString::fromUtf8("tab_5"));
    gridLayoutWidget_5 = new QWidget(tab_5);
    gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
    gridLayoutWidget_5->setGeometry(QRect(10, 10, 821, 51));
    gridLayout_4 = new QGridLayout(gridLayoutWidget_5);
    gridLayout_4->setSpacing(6);
    gridLayout_4->setContentsMargins(11, 11, 11, 11);
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    gridLayout_4->setContentsMargins(0, 0, 0, 0);
    nameLabel = new QLabel(gridLayoutWidget_5);
    nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
    QFont font1;
    font1.setPointSize(16);
    font1.setBold(true);
    font1.setItalic(true);
    font1.setWeight(75);
    nameLabel->setFont(font1);

    gridLayout_4->addWidget(nameLabel, 0, 0, 1, 1);

    horizontalLayoutWidget = new QWidget(tab_5);
    horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(10, 70, 192, 53));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    addressLabel = new QLabel(horizontalLayoutWidget);
    addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

    horizontalLayout->addWidget(addressLabel);

    addressNodeLabel = new QLabel(horizontalLayoutWidget);
    addressNodeLabel->setObjectName(QString::fromUtf8("addressNodeLabel"));

    horizontalLayout->addWidget(addressNodeLabel);

    verticalLayoutWidget = new QWidget(tab_5);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(10, 130, 191, 61));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    addressSpinBox = new QSpinBox(verticalLayoutWidget);
    addressSpinBox->setObjectName(QString::fromUtf8("addressSpinBox"));

    verticalLayout->addWidget(addressSpinBox);

    changeAddressButton = new QPushButton(verticalLayoutWidget);
    changeAddressButton->setObjectName(QString::fromUtf8("changeAddressButton"));

    verticalLayout->addWidget(changeAddressButton);

    staticNodeTabWidget->addTab(tab_5, QString());
    gridLayoutWidget_5->raise();
    horizontalLayoutWidget->raise();
    addressLabel->raise();
    verticalLayoutWidget->raise();
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    gridLayoutWidget_4 = new QWidget(tab_3);
    gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
    gridLayoutWidget_4->setGeometry(QRect(10, 10, 821, 151));
    gridLayout_3 = new QGridLayout(gridLayoutWidget_4);
    gridLayout_3->setSpacing(6);
    gridLayout_3->setContentsMargins(11, 11, 11, 11);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    gridLayout_3->setContentsMargins(0, 0, 0, 0);
    RSSILevelBar = new QProgressBar(gridLayoutWidget_4);
    RSSILevelBar->setObjectName(QString::fromUtf8("RSSILevelBar"));
    RSSILevelBar->setValue(24);

    gridLayout_3->addWidget(RSSILevelBar, 1, 0, 1, 1);

    RSSILevelLabel = new QLabel(gridLayoutWidget_4);
    RSSILevelLabel->setObjectName(QString::fromUtf8("RSSILevelLabel"));
    RSSILevelLabel->setFont(font1);

    gridLayout_3->addWidget(RSSILevelLabel, 0, 0, 1, 1);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

    buttonLabel = new QLabel(gridLayoutWidget_4);
    buttonLabel->setObjectName(QString::fromUtf8("buttonLabel"));
    QFont font2;
    font2.setPointSize(14);
    font2.setBold(true);
    font2.setItalic(true);
    font2.setWeight(75);
    buttonLabel->setFont(font2);

    gridLayout_3->addWidget(buttonLabel, 3, 0, 1, 1);

    isPressedLabel = new QLabel(gridLayoutWidget_4);
    isPressedLabel->setObjectName(QString::fromUtf8("isPressedLabel"));
    QFont font3;
    font3.setPointSize(12);
    font3.setBold(true);
    font3.setWeight(75);
    isPressedLabel->setFont(font3);
    isPressedLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    isPressedLabel->setMargin(0);
    isPressedLabel->setIndent(20);

    gridLayout_3->addWidget(isPressedLabel, 4, 0, 1, 1);

    staticNodeTabWidget->addTab(tab_3, QString());


    nameLabel->setText("TextLabel");
    addressLabel->setText("Address:");
    addressNodeLabel->setText("TextLabel");
    changeAddressButton->setText("Change Address");
    staticNodeTabWidget->setTabText(staticNodeTabWidget->indexOf(tab_5), "Page");
    RSSILevelLabel->setText("Signal Quality:");
    buttonLabel->setText("Button:");
    isPressedLabel->setText("Released");

    connect(changeAddressButton,SIGNAL(clicked()),this,SLOT(changeAddresButton_Clicked()));

}

void staticNodeButtonWidget::setAddress(int newAddress)
{
    addressNodeLabel->setText(QString::number(newAddress));
    addressSpinBox->setValue(newAddress);
}

void staticNodeButtonWidget::changeAddresButton_Clicked()
{
    emit(addressChanged(addressNodeLabel->text().toInt(),addressSpinBox->value()));
    addressNodeLabel->setText(QString::number(addressSpinBox->value()));



}
