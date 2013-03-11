#ifndef REQUESTUPDATEDATA_H
#define REQUESTUPDATEDATA_H

#include "RunnableBase.h"
class QTcpSocket;

class RequestUpdateData : public RunnableBase
{
    Q_OBJECT
public:
    RequestUpdateData(QList<QString> list, QMap<QString, QByteArray> *pUpdateData, QByteArray &serialize, QTcpSocket *tcpSocket);

protected:
    void run();

private:
    QTcpSocket *pTcpSocket_;
    QByteArray bytes_;
};

#endif // REQUESTUPDATEDATA_H
