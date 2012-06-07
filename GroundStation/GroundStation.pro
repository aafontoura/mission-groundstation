#-------------------------------------------------
#
# Project created by QtCreator 2012-04-30T12:54:49
#
#-------------------------------------------------

QWT_ROOT = C:/QtCreatorSDK/QWT/
include( $${QWT_ROOT}/qwtconfig.pri )
include( $${QWT_ROOT}/qwtbuild.pri )
include(./MKProtocol/MKProtocol.pro)

QT       += core gui xml webkit network qwt


TARGET = GroundStation
TEMPLATE = app

INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src


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
    staticnodebuttonwidget.cpp \
    PFD/attitude_indicator.cpp \
    PFD/cockpit_grid.cpp \
    PFD/compass_grid.cpp




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
    staticnodebuttonwidget.h \    
    zigBeeDefs.h \
    PFD/attitude_indicator.h \
    PFD/cockpit_grid.h \
    PFD/compass_grid.h


QMAKE_RPATHDIR *= $${QWT_ROOT}/lib

contains(QWT_CONFIG, QwtFramework) {

    LIBS      += -F$${QWT_ROOT}/lib
}
else {

    LIBS      += -L$${QWT_ROOT}/lib
}

IPATH       = $${INCLUDEPATH}
qtAddLibrary(qwt)
INCLUDEPATH = $${IPATH}

contains(QWT_CONFIG, QwtSvg) {

    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


win32 {
    contains(QWT_CONFIG, QwtDll) {
        DEFINES    += QT_DLL QWT_DLL
    }
}


FORMS    += mainwindow.ui

RESOURCES += \
    groundStation.qrc

OTHER_FILES +=




