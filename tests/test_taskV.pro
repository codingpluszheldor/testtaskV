QT       += testlib sql
QT       -= gui

TARGET = test_taskV
CONFIG   += console
CONFIG   += c++17
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../testtaskv/DbModelCounters/dbmodelcounters.cpp \
    test_taskV.cpp

HEADERS += \
    ../testtaskv/DbModelCounters/dbmodelcounters.h \
    test_taskV.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../common
INCLUDEPATH += $$PWD/../testtaskv

CONFIG *= common_Settings
CONFIG *= common_DbConnection
CONFIG *= common_DbModelBase

include ($$PWD/../common/common_Settings.pri)
include ($$PWD/../common/common_DbConnection.pri)
include ($$PWD/../common/common_DbModelBase.pri)


CONFIG(debug, debug|release): DESTDIR =  $$PWD/../test_bin

DEFINES *= TEST

