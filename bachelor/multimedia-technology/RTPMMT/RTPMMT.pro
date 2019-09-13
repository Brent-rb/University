#-------------------------------------------------
#
# Project created by QtCreator 2015-12-25T19:50:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTPMMT
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    RTPCompare.cpp \
    RTPConnector.cpp \
    RTPFrame.cpp \
    RTPQueue.cpp \
    RTPSyncer.cpp \
    semaphore.cpp \
    rtpplayer.cpp

HEADERS  += mainwindow.h \
    RTPCompare.h \
    RTPConnector.h \
    RTPFrame.h \
    RTPQueue.h \
    RTPSyncer.h \
    semaphore.h \
    jrtplib3/rtcpapppacket.h \
    jrtplib3/rtcpbyepacket.h \
    jrtplib3/rtcpcompoundpacket.h \
    jrtplib3/rtcpcompoundpacketbuilder.h \
    jrtplib3/rtcppacket.h \
    jrtplib3/rtcppacketbuilder.h \
    jrtplib3/rtcprrpacket.h \
    jrtplib3/rtcpscheduler.h \
    jrtplib3/rtcpsdesinfo.h \
    jrtplib3/rtcpsdespacket.h \
    jrtplib3/rtcpsrpacket.h \
    jrtplib3/rtcpunknownpacket.h \
    jrtplib3/rtpaddress.h \
    jrtplib3/rtpbyteaddress.h \
    jrtplib3/rtpcollisionlist.h \
    jrtplib3/rtpconfig.h \
    jrtplib3/rtpdebug.h \
    jrtplib3/rtpdefines.h \
    jrtplib3/rtperrors.h \
    jrtplib3/rtpexternaltransmitter.h \
    jrtplib3/rtphashtable.h \
    jrtplib3/rtpinternalsourcedata.h \
    jrtplib3/rtpipv4address.h \
    jrtplib3/rtpipv4destination.h \
    jrtplib3/rtpipv6address.h \
    jrtplib3/rtpipv6destination.h \
    jrtplib3/rtpkeyhashtable.h \
    jrtplib3/rtplibraryversion.h \
    jrtplib3/rtpmemorymanager.h \
    jrtplib3/rtpmemoryobject.h \
    jrtplib3/rtppacket.h \
    jrtplib3/rtppacketbuilder.h \
    jrtplib3/rtppollthread.h \
    jrtplib3/rtprandom.h \
    jrtplib3/rtprandomrand48.h \
    jrtplib3/rtprandomrands.h \
    jrtplib3/rtprandomurandom.h \
    jrtplib3/rtprawpacket.h \
    jrtplib3/rtpsession.h \
    jrtplib3/rtpsessionparams.h \
    jrtplib3/rtpsessionsources.h \
    jrtplib3/rtpsourcedata.h \
    jrtplib3/rtpsources.h \
    jrtplib3/rtpstructs.h \
    jrtplib3/rtptimeutilities.h \
    jrtplib3/rtptransmitter.h \
    jrtplib3/rtptypes.h \
    jrtplib3/rtptypes_win.h \
    jrtplib3/rtpudpv4transmitter.h \
    jrtplib3/rtpudpv6transmitter.h \
    jthread/jmutex.h \
    jthread/jmutexautolock.h \
    jthread/jthread.h \
    jthread/jthreadconfig.h \
    rtpplayer.h

FORMS    += mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -ljrtplib_
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -ljrtplib_d

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -ljthread_
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -ljthread_d

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
