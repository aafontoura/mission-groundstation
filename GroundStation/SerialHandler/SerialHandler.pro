#-------------------------------------------------
#
# Project created by QtCreator 2012-05-19T10:55:18
#
#-------------------------------------------------

include(../qextserialport/src/qextserialport.pri)

# $$PWD

QT       -= gui

TARGET = SerialHandler
TEMPLATE = lib

DEFINES += SERIALHANDLER_LIBRARY

SOURCES += $$PWD/serialhandler.cpp

HEADERS += $$PWD/serialhandler.h\
        $$PWD/SerialHandler_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE32D7C08
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = SerialHandler.dll
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
