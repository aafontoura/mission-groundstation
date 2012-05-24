#-------------------------------------------------
#
# Project created by QtCreator 2012-05-17T22:49:45
#
#-------------------------------------------------

include(../zigbeeprotocol/ZigBeeProtocol.pro)

QT       -= gui

TARGET = MKProtocol
TEMPLATE = lib

DEFINES += MKPROTOCOL_LIBRARY

DEPENDPATH += $$PWD/../zigbeeprotocol
INCLUDEPATH += $$PWD/../zigbeeprotocol

LIBS+= -L$$PWD/..zigbeeprotocol/debug

SOURCES += $$PWD/mkprotocol.cpp \
    $$PWD/parameterrequest.cpp \
    $$PWD/modules/heliwaypoint.cpp \
    $$PWD/modules/waypointshandler.cpp \
    $$PWD/modules/waypointinfo.cpp \
    $$PWD/modules/versioninfo.cpp \
    $$PWD/modules/helicopterattribute.cpp \
    $$PWD/modules/generalwaypoint.cpp \
    $$PWD/modules/debuganalogs.cpp \
    $$PWD/modules/data3d.cpp \
    MKProtocol/gpsposition.cpp


HEADERS += $$PWD/mkprotocol.h \
        $$PWD/MKProtocol_global.h \
    $$PWD/parameterrequest.h \
    $$PWD/MKProtocol_global.h \
    $$PWD/modules/heliwaypoint.h \
    $$PWD/modules/HelicopterDefs.h \
    $$PWD/modules/helicopterattribute.h \
    $$PWD/modules/waypointshandler.h \
    $$PWD/modules/waypointinfo.h \
    $$PWD/modules/generalwaypoint.h \
    $$PWD/modules/debuganalogs.h \
    $$PWD/modules/data3d.h \
    $$PWD/modules/versioninfo.h \
    MKProtocol/gpsposition.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE35A73DE
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MKProtocol.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    MKProtocol.pro.user \
    MKProtocol.pro
