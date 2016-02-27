QT += core
QT -= gui

include(D:\git_projects\HelperLibrary\Sources\helperlibrary.pri)

CONFIG += c++11

TARGET = DuplicateFinder
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myfileinfo.cpp

HEADERS += \
    myfileinfo.h

