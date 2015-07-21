#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T12:07:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TorrentDownloader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    runmodel.cpp \
    filemodel.cpp \
    torrentservermanager.cpp \
    fileitem.cpp \
    runitem.cpp \
    connectbar.cpp \
    runwidget.cpp \
    filewidget.cpp \
    fileitemdelegate.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    runmodel.h \
    filemodel.h \
    torrentservermanager.h \
    fileitem.h \
    runitem.h \
    connectbar.h \
    runwidget.h \
    filewidget.h \
    fileitemdelegate.h \
    downloader.h

FORMS    += mainwindow.ui
