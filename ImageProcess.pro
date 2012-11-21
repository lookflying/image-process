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
    fimage.cpp \
    basicoperationwidget.cpp \
    chartwidget.cpp \
    linearfunction.cpp \
    grayscaletransformwidget.cpp \
    function.cpp \
    imageprocess.cpp \
    logfunction.cpp \
    exponentfunction.cpp \
    convolution.cpp \
    convolutionengine.cpp \
    filterwidget.cpp \
    edgedetect.cpp

HEADERS  += mainwindow.h \
    imageview.h \
    fimage.h \
    basicoperationwidget.h \
    chartwidget.h \
    linearfunction.h \
    grayscaletransformwidget.h \
    function.h \
    imageprocess.h \
    logfunction.h \
    exponentfunction.h \
    convolution.h \
    convolutionengine.h \
    filterwidget.h \
    edgedetect.h

FORMS    +=


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
