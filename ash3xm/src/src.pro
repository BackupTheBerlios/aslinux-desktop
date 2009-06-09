SOURCES += main.cpp \
 mclient.cpp \
 client.cpp \
 response.cpp \
 request.cpp \
 variant.cpp \
 cmsgbox.cpp
TEMPLATE = app
CONFIG += qt \
 windows \
 x11 \
 warn_off
TARGET = ../bin/ash3xm

FORMS += mclient.ui \
 CMessageBox.ui

HEADERS += mclient.h \
client.h \
 stable.h \
 request.h \
 variant.h \
 response.h \
 cmsgbox.h
QT += xml \
 network

RESOURCES += systray.qrc

CONFIG -= warn_on \
exceptions \
thread
dlink.path = /usr/share/autostart

desktop.path = /usr/share/autostart/

desktop.files += *.desktop

DISTFILES += ash3xm.desktop

