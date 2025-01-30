QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH    += $$PWD/../common

SOURCES += \
    Application/application.cpp \
    Controller/controller.cpp \
    DbModelCounters/dbmodelcounters.cpp \
    main.cpp \
    Widget/widget.cpp

HEADERS += \
    Application/application.h \
    Controller/controller.h \
    DbModelCounters/dbmodelcounters.h \
    Widget/widget.h

CONFIG *= common_Settings
CONFIG *= common_DbConnection
CONFIG *= common_DbModelBase

include ($$PWD/../common/common_Settings.pri)
include ($$PWD/../common/common_DbConnection.pri)
include ($$PWD/../common/common_DbModelBase.pri)

CONFIG (debug, debug|release) {
    DESTDIR =  $$PWD/../bin
}else{
    win32 {
        DESTDIR =  $$PWD/../win_deploy
    }
    unix {
        DESTDIR =  $$PWD/../bin
    }
#    DEFINES += QT_NO_DEBUG_OUTPUT
}
