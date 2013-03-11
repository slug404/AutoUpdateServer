#include "RequestUpdateData.h"
#include <QTcpSocket>
#include <QDomDocument>
#include <QDomNode>

RequestUpdateData::RequestUpdateData(QList<QString> list, QMap<QString, QByteArray> *pUpdateData, QByteArray &serialize, QTcpSocket *tcpSocket)
    : pTcpSocket_(tcpSocket)
{
    //胖客户端, 瘦服务端

    QDataStream out(&bytes_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (qint32)0;
    out << (qint32)1; //RequestData
    out << (qint32)list.size(); //也是用来占位, 具体返回的数据的数量还需要看下面的计算
    int count = 0;
    for(int i = 0; i != list.size(); ++i)
    {
        QString name = list.at(i);

        if(!pUpdateData->contains(name))
        {
            qDebug() << "update data don't contains " << name;
            continue;
        }

        QByteArray data = pUpdateData->value(name);
        out << name;
        out << data;
        ++count;
    }
    if(list.size() != count)
    {
        out.device()->seek(2 * (qint32)sizeof(qint32));
        out << count;
    }

    //在这里加入序列化后的数据
    out << serialize;

    out.device()->seek(0);
    qint32 size = bytes_.size() - (qint32)sizeof(qint32);
    out << (qint32)size;
}

void RequestUpdateData::run()
{
    pTcpSocket_->write(bytes_);
    pTcpSocket_->waitForBytesWritten();
}
