SOURCES += main.cpp \
 khusba.cpp
TEMPLATE = app
CONFIG += warn_on thread qt precompile_header
TARGET = ../bin/khusba4

INCLUDEPATH += /usr/include/qt4/

QT -= gui

QT += opengl

LIBS += -lQtDBus

HEADERS += khusba.h

