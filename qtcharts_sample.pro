#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T14:03:01
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtcharts_sample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chartview.cpp \
    clsChrono.cpp

HEADERS  += mainwindow.h \
    chartview.h \
    clsChrono.h

FORMS    += mainwindow.ui

target.path = /home/pi
INSTALLS += target
