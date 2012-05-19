#-------------------------------------------------
#
# Project created by QtCreator 2012-04-30T12:54:49
#
#-------------------------------------------------
include(./MKProtocol/MKProtocol.pro)

QT       += core gui

TARGET = GroundStation
TEMPLATE = app

DEPENDPATH += ./mkprotocol
INCLUDEPATH += ./mkprotocol

LIBS+= -L./mkprotocol/debug

SOURCES += main.cpp \
        mainwindow.cpp \    
    helicopterhandler.cpp



HEADERS  += mainwindow.h \    
    helicopterhandler.h



FORMS    += mainwindow.ui
