#-------------------------------------------------
#
# Project created by QtCreator 2013-02-04T18:24:24
#
#-------------------------------------------------

QT += core gui
QT += network
QT += xml
QT += testlib
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoUpadteServer
TEMPLATE = app

#LIBS += -llibLog4Qt
INCLUDEPATH += . \
    ./TcpServer \
    ./Thread

SOURCES += main.cpp\
        WidgetMain.cpp \
    TcpServer/TcpServer.cpp \
    TcpServer/RunnableBase.cpp \
    TcpServer/RequestUpdateInfor.cpp \
    TcpServer/RequestUpdateData.cpp \
    TcpServer/RequestExecutable.cpp \
    Thread/ThreadObjectBase.cpp \
    Thread/ThreadObjectUpdateInfor.cpp \
    Thread/ThreadObjectUpdateData.cpp
#    qabstractsocket.cpp \
#    qiodevice.cpp

HEADERS  += WidgetMain.h \
	dptr.h \
    TcpServer/TcpServer.h \
    TcpServer/RunnableBase.h \
    TcpServer/RequestUpdateInfor.h \
    TcpServer/RequestUpdateData.h \
    TcpServer/RequestExecutable.h \
    Thread/ThreadObjectBase.h \
    Common.h \
    Thread/ThreadObjectUpdateInfor.h \
    Thread/ThreadObjectUpdateData.h

FORMS    += WidgetMain.ui

win32{
MOC_DIR = _moc
OBJECTS_DIR = _obj
RCC_DIR = _rcc
UI_DIR = _ui
UI_HEADERS_DIR = _ui
UI_SOURCES_DIR = _ui
}else{
MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .rcc
UI_DIR = .ui
UI_HEADERS_DIR = .ui
UI_SOURCES_DIR = .ui
}

