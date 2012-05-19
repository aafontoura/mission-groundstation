#-------------------------------------------------
#
# Project created by QtCreator 2012-05-18T08:27:24
#
#-------------------------------------------------

include(../serialhandler/SerialHandler.pro)

QT       -= gui

TARGET = ZigBeeProtocol
TEMPLATE = lib

DEPENDPATH += $$PWD/../serialhandler
INCLUDEPATH += $$PWD/../serialhandler

LIBS+= -L$$PWD/..serialhandler/debug

DEFINES += ZIGBEEPROTOCOL_LIBRARY

SOURCES += $$PWD/zigbeeprotocol.cpp

HEADERS += $$PWD/zigbeeprotocol.h\
        $$PWD/ZigBeeProtocol_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0AA4032
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ZigBeeProtocol.dll
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
