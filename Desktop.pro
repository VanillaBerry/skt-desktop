#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T15:53:02
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    app_database.cpp \
    img_edit/img_effects.cpp

HEADERS  += mainwindow.h \
    app_database.h \
    img_edit/img_effects.h

FORMS    += mainwindow.ui
