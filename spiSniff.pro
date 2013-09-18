#-------------------------------------------------
#
# Project created by QtCreator 2013-07-19T18:26:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spiSniff
TEMPLATE = app

CONFIG += qxt
QXT += core gui



SOURCES += main.cpp\
        mainwindow.cpp \
    widgetsetup.cpp \
    widgetdata.cpp \
    widgetcom.cpp hled.cpp \
    widgetzdroj.cpp

HEADERS  += mainwindow.h \
    widgetsetup.h \
    widgetdata.h \
    widgetcom.h hled.h \
    widgetzdroj.h

FORMS    += mainwindow.ui \
    widgetsetup.ui \
    widgetdata.ui \
    widgetcom.ui \
    widgetzdroj.ui


include (qextserialport/src/qextserialport.pri)
