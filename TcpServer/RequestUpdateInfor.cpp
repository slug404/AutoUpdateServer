#include "RequestUpdateInfor.h"
#include <QTcpSocket>

RequestUpdateInfor::RequestUpdateInfor(const QByteArray &updateInfor, QTcpSocket *p)
    : updateInfor_(updateInfor)
    , pTcpSocket_(p)
{
}

void RequestUpdateInfor::run()
{
    //qDebug() << "server send update xml";

    pTcpSocket_->write(updateInfor_);
    pTcpSocket_->waitForBytesWritten();
    //qDebug() << "server send update xml done";
}
