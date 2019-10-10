#-------------------------------------------------
#
# Project created by QtCreator 2019-09-30T10:13:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rpn.cpp

HEADERS  += mainwindow.h \
    rpn.h

FORMS    += mainwindow.ui
