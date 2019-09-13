#-------------------------------------------------
#
# Project created by QtCreator 2012-05-25T12:54:51
#
#-------------------------------------------------

QT       += core widgets

TARGET = observer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        textfile.cpp \
        textfileview.cpp \
    textfilestats.cpp \
    textfilesubject.cpp

HEADERS  += mainwindow.h \
        textfile.h \
        textfileview.h \
    textfilestats.h \
    textfilesubject.h \
    textfileobserver.h

FORMS    += mainwindow.ui \
    textfilestats.ui

RESOURCES +=

OTHER_FILES += \
    test.txt
