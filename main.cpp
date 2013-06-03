#include "WidgetMain.h"
#include <QApplication>
#include <QDebug>
#include "TcpServer/TcpServer.h"
//#include "Log4Qt/Logger"
//#include "Log4Qt/BasicConfigurator"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Log4Qt::BasicConfigurator::configure();
    //Log4Qt::Logger *pLog = Log4Qt::Logger::rootLogger();

    WidgetMain w;
    TcpServer *pTcpServer = new TcpServer();
    if(pTcpServer->startServer())
    {
        qDebug() << "tcp server start success!";
    }
    else
    {
        qDebug() << "tcp server start fail!";
    }

    w.setWindowTitle("server");
    w.show();
    return a.exec();
}
