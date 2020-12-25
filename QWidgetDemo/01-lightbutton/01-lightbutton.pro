QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET      = 01-lightbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += \
    lightbuttoncontrol.cpp \
    lightbuttonwidget.cpp \
    main.cpp

HEADERS += \
    lightbuttoncontrol.h \
    lightbuttonwidget.h

FORMS +=

