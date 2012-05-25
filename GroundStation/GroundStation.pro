#-------------------------------------------------
#
# Project created by QtCreator 2012-04-30T12:54:49
#
#-------------------------------------------------
include(./MKProtocol/MKProtocol.pro)

QT       += core gui xml


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
    missionwaypoint.cpp



HEADERS  += mainwindow.h \    
    helicopterhandler.h \
    networkmission.h \
    missionxmlreader.h \
    missionwaypoint.h



FORMS    += mainwindow.ui
