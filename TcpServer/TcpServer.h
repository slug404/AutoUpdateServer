#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QMutex>
#include "RunnableBase.h"
#include "Log4Qt/Logger"

class QThreadPool;
struct FileInfor;
class QTcpSocket;

class TcpServer : public QTcpServer
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER

public:
    enum RequestType
    {
        RequestXml,
        RequestData,
        Executable
    };

    explicit TcpServer(QObject *parent = 0);
    bool startServer();

signals:

public slots:

protected:
    void incomingConnection(int handle);

private slots:
    void slotReadyRead();

private:
    void initData();
    void traveDirectory(const QString &str, const QStringList &filterFolderPaths);

private:
    QThreadPool *pThreadPool_;
    //文件名和对应数据
    QMap<QString, QByteArray> pMap_fileName_data_;
    QMap<FileInfor, QByteArray> pMap_updateDataBuffer_;
    //socket描述符和tcp socket
    QMap<int, QTcpSocket*> pMap_socketDescriptor_tcpSocket_;
    //socket描述符和对应模块大小
    QMap<int, int> pMap_socketDescriptor_blockSize_;
    //服务端的xml
    QByteArray updateInfor_;
    QByteArray bytes_;
    //序列化file和对应的path
    QByteArray serializeData_;

    //锁
    QMutex mutex_;
};

#endif // TCPSERVER_H
