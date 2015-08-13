#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T12:07:59
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

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
    downloader.cpp \
    downloadwidget.cpp \
    downloadmodel.cpp \
    downloaddelegate.cpp \
    downloaddialog.cpp

HEADERS  += mainwindow.h \
    runmodel.h \
    filemodel.h \
    torrentservermanager.h \
    fileitem.h \
    runitem.h \
    connectbar.h \
    runwidget.h \
    filewidget.h \
    downloader.h \
    downloadwidget.h \
    downloadmodel.h \
    downloaddelegate.h \
    downloaddialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
