#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T21:30:34
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = FieldGoalKicking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    GLUquadricCylinder.cpp \
    ReflectanceTable.cpp \
    GLUquadricSphere.cpp \
    Cube.cpp \
    Upright.cpp \
    Bleachers.cpp \
    Football.cpp \
    Game.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    GLUquadricCylinder.h \
    ReflectanceTable.h \
    GLUquadricSphere.h \
    Cube.h \
    BufferObject.h \
    Upright.h \
    Bleachers.h \
    Football.h \
    Game.h \
    Timer.hpp

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -lGLEW
