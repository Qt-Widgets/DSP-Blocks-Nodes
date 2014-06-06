#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T21:07:24
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = MusicBlocks

CONFIG += console

win32: DESTDIR = ../App
else:  DESTDIR = ../App/bin

#win32: QMAKE_LIBDIR += ../App
#else:  QMAKE_LIBDIR += ../App/lib
win32: LIBS += -L../App -lwinmm
else:  LIBS += -L../App/lib -lrt
LIBS += -lMusicBlocks

SOURCES += main.cpp MainWindow.cpp Thread.cpp BlocksTree.cpp SchemeView.cpp SimSettings.cpp
HEADERS +=          MainWindow.hpp Thread.hpp BlocksTree.hpp SchemeView.hpp SimSettings.hpp
FORMS   +=          MainWindow.ui                                           SimSettings.ui

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/rcc

INCLUDEPATH += . ../Lib
DEPENDPATH  += . ../Lib
