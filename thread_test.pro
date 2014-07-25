#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T18:32:39
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = thread_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mserver.cpp \
    mthread.cpp \
    header_parser.cpp

HEADERS += \
    mserver.h \
    mthread.h \
    global_vars.h \
    header_parser.h
