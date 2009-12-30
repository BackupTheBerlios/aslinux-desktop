SOURCES += main.cpp \
 khusba.cpp
TEMPLATE = app
CONFIG += warn_on thread qt
TARGET = ../bin/khusba4

INCLUDEPATH += /usr/include/qt4/

QT -= gui


LIBS += -lQtDBus

HEADERS += khusba.h

INSTALLS += target

target.path = /${DESTDIR}/usr/bin

