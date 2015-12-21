#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T18:04:53
#
#-------------------------------------------------

QT       += core
QT       += network

QT       += gui

TARGET = ExplOZ_IA
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    communicator.cpp \
    receiver.cpp \
    sender.cpp \
    motorsender.cpp \
    toolsender.cpp \
    acceleroreceiver.cpp

HEADERS += \
    communicator.h \
    receiver.h \
    sender.h \
    motorsender.h \
    toolsender.h \
    acceleroreceiver.h
