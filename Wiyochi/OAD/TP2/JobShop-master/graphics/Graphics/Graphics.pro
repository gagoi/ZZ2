#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T12:13:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphics
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    ../../compare.cpp \
    ../../Data.cpp \
    ../../Bierwirth.cpp \
    ../../bkr.cpp \
    ../../Operation.cpp \
    ../../window.cpp

HEADERS  += \
    ../../compare.hpp \
    ../../Bierwirth.hpp \
    ../../bkr.hpp \
    ../../Data.h \
    ../../Operation.hpp \
    ../../window.h

FORMS    += mainwindow.ui

