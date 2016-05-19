#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T16:44:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reversi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    brettwidget.cpp \
    spielbrett.cpp

HEADERS  += mainwindow.h \
    settings.h \
    brettwidget.h \
    spielbrett.h

FORMS    += mainwindow.ui \
    settings.ui

DISTFILES +=
