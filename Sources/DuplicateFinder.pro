QT += core
QT -= gui

CONFIG += c++11

include(helperLibrary/helperlibrary.pri)

TARGET = DuplicateFinder
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myfileinfo.cpp

HEADERS += \
    myfileinfo.h

