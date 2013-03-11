#-------------------------------------------------
#
# Project created by QtCreator 2013-02-04T18:24:24
#
#-------------------------------------------------

QT += core gui
QT += network
QT += xml
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nimei
TEMPLATE = app

LIBS += -llibLog4Qt

SOURCES += main.cpp\
        WidgetMain.cpp \
    TcpServer/TcpServer.cpp \
    TcpServer/RunnableBase.cpp \
    TcpServer/RequestUpdateInfor.cpp \
    TcpServer/RequestUpdateData.cpp \
    TcpServer/RequestExecutable.cpp

HEADERS  += WidgetMain.h \
	dptr.h \
    TcpServer/TcpServer.h \
    TcpServer/RunnableBase.h \
    TcpServer/RequestUpdateInfor.h \
    TcpServer/RequestUpdateData.h \
    TcpServer/RequestExecutable.h

FORMS    += WidgetMain.ui
