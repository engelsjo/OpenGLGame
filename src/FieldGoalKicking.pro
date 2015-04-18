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
    ReflectanceTable.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    GLUquadricCylinder.h \
    ReflectanceTable.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include
