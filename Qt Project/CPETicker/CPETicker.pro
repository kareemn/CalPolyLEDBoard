#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T10:50:57
#
#-------------------------------------------------

QT       += core gui

TARGET = CPETicker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES +=

include(../qextserialport-1.2rc/src/qextserialport.pri)
