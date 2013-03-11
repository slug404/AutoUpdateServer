#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
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
    QMap<QString, QByteArray> pMap_fileName_data_;
    QMap<FileInfor, QByteArray> pMap_updateDataBuffer_;
    QMap<int, QTcpSocket*> pMap_socketDescriptor_tcpSocket_;
    QMap<int, int> pMap_socketDescriptor_blockSize_;
    QByteArray updateInfor_;
    QByteArray bytes_;
    QByteArray serializeData_;
};

#endif // TCPSERVER_H
