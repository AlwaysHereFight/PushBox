QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PushBox TEMPLATE = app

SOURCES += main.cpp
mainWidget.cpp
GameWidget.cpp

HEADERS += mainWidget.h
GameWidget.h

RESOURCES +=
pushboxresource.qrc \
