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
    map.cpp \
    gmapwidget.cpp \
    missionstaticnode.cpp \
    zigbeetransparentstaticnode.cpp \
    missionnode.cpp





HEADERS  += mainwindow.h \    
    helicopterhandler.h \
    networkmission.h \
    missionxmlreader.h \
    missionwaypoint.h \
    map.h \
    gmapwidget.h \
    missionstaticnode.h \
    zigbeetransparentstaticnode.h \
    missionnode.h





FORMS    += mainwindow.ui

RESOURCES += \
    groundStation.qrc

OTHER_FILES +=
