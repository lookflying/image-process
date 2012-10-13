#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T18:29:51
#
#-------------------------------------------------

QT       += core gui

TARGET = ImageProcess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageview.cpp \
    fimage.cpp

HEADERS  += mainwindow.h \
    imageview.h \
    fimage.h

FORMS    +=


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
