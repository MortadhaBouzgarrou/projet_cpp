#-------------------------------------------------
#
# Project created by QtCreator 2018-10-31T08:31:47
#
#-------------------------------------------------

QT+= core gui printsupport
QT+= sql
QT += core gui charts
QT += core gui network


CONFIG+=console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Crud_Vf
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
    client.cpp \
    client_ticket.cpp \
    ticket.cpp \
        main.cpp \
    connexion.cpp \
    smtp.cpp\
    notification.cpp

HEADERS += \
    client.h \
    client_ticket.h \
    connexion.h \
    ticket.h \
    smtp.h\
    notification.h

FORMS += \
    client_ticket.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
