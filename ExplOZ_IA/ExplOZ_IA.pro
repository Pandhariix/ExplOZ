#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T18:04:53
#
#-------------------------------------------------

QT       += core
QT       += network

QT       += gui
QT       += widgets

TARGET = ExplOZ_IA
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += C:/opencv/build/install/include
LIBS += "C:/opencv/build/bin/*.dll"

SOURCES += main.cpp \
    communicator.cpp \
    receiver.cpp \
    sender.cpp \
    motorsender.cpp \
    toolsender.cpp \
    acceleroreceiver.cpp \
    lidarreceiver.cpp \
    houghdetector.cpp \
    motioncontrol.cpp

HEADERS += \
    communicator.h \
    receiver.h \
    sender.h \
    motorsender.h \
    toolsender.h \
    acceleroreceiver.h \
    lidarreceiver.h \
    houghdetector.h \
    motioncontrol.h
