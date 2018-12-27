#-------------------------------------------------
#
# Project created by QtCreator 2018-11-18T12:23:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Galaga2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        game.cpp \
    skystar.cpp \
    player.cpp \
    gameobject.cpp \
    shot.cpp \
    enemy.cpp \
    explosion.cpp \
    route.cpp \
    animated.cpp \
    shooter.cpp \
    drawed.cpp \
    physicalobject.cpp \
    routed.cpp

HEADERS += \
        game.h \
    skystar.h \
    player.h \
    gameobject.h \
    shot.h \
    enemy.h \
    explosion.h \
    route.h \
    animated.h \
    shooter.h \
    drawed.h \
    physicalobject.h \
    routed.h

FORMS += \
        game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    game.qrc
