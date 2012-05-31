#-------------------------------------------------
#
# Project created by QtCreator 2012-04-30T12:54:49
#
#-------------------------------------------------
include(./MKProtocol/MKProtocol.pro)

QT       += core gui xml webkit network


TARGET = GroundStation
TEMPLATE = app

DEPENDPATH += ./mkprotocol
INCLUDEPATH += ./mkprotocol

LIBS+= -L./mkprotocol/debug

SOURCES += main.cpp \
        mainwindow.cpp \    
    helicopterhandler.cpp \
    networkmission.cpp \
    missionxmlreader.cpp \
    missionwaypoint.cpp \
    gmapwidget.cpp \
    missionstaticnode.cpp \
    missionnode.cpp \
    zigbeetransparentstaticnode.cpp \
    map.cpp \
    mkwidget.cpp \
    staticnodebuttonwidget.cpp




HEADERS  += mainwindow.h \    
    helicopterhandler.h \
    networkmission.h \
    missionxmlreader.h \
    missionwaypoint.h \
    gmapwidget.h \
    missionstaticnode.h \
    missionnode.h \
    zigbeetransparentstaticnode.h \
    map.h \
    mkwidget.h \
    staticnodebuttonwidget.h





FORMS    += mainwindow.ui

RESOURCES += \
    groundStation.qrc

OTHER_FILES +=
