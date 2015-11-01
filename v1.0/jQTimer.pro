#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T13:28:57
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jQTimer
TEMPLATE = app


SOURCES += main.cpp\
    listener.cpp \
    mainwindow.cpp \
    adddialog.cpp \
    threadrunner.cpp

HEADERS  += \
    listener.h \
    mainwindow.h \
    adddialog.h \
    threadrunner.h

FORMS    += cmainwindow.ui \
    adddialog.ui

RESOURCES += \
    Resources/resource_file.qrc
