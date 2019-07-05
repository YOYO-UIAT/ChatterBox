#-------------------------------------------------
#
# Project created by QtCreator 2019-07-01T12:22:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatterBox
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        chatterbox_mainwindow.cpp \
    itemmanager.cpp \
    friends.cpp \
    settings.cpp \
    connection.cpp \
    searchfriend.cpp \
    iplib.cpp \
    filereader.cpp \
    filewriter.cpp \
    newfriendmessage.cpp \
    frienditem.cpp \
    usernamelib.cpp \
    chatwindow.cpp \
    messagedispatcher.cpp

HEADERS += \
        chatterbox_mainwindow.h \
    itemmanager.h \
    friends.h \
    settings.h \
    connection.h \
    iplib.h \
    searchfriend.h \
    filereader.h \
    filewriter.h \
    newfriendmessage.h \
    frienditem.h \
    usernamelib.h \
    chatwindow.h \
    messagedispatcher.h

FORMS += \
        chatterbox_mainframe.ui \
    friends.ui \
    settings.ui \
    searchfriend.ui \
    newfriendmessage.ui \
    frienditem.ui \
    chatwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS=EXEICON.ico
DISTFILES +=

RESOURCES += \
    toolbar.qrc
LIBS += -lWs2_32
