#-------------------------------------------------
#
# Project created by QtCreator 2025-07-26T19:15:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = airplane_game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    plane.cpp \
    heroplane.cpp \
    bullet.cpp \
    herobullet.cpp \
    enemybullet.cpp \
    weapon.cpp \
    heroweapon.cpp \
    enemyweapon.cpp \
    enemyplane.cpp \
    herobulletpool.cpp \
    enemyplanepool.cpp \
    enemybulletpool.cpp

HEADERS += \
        widget.h \
    config.h \
    plane.h \
    heroplane.h \
    bullet.h \
    herobullet.h \
    enemybullet.h \
    weapon.h \
    heroweapon.h \
    enemyweapon.h \
    enemyplane.h \
    herobulletpool.h \
    enemyplanepool.h \
    enemybulletpool.h

FORMS += \
        widget.ui

RESOURCES += \
    res.qrc
