#include "RequestExecutable.h"
#include <QTcpSocket>

RequestExecutable::RequestExecutable(const QByteArray &bytes, QTcpSocket *p)
    : bytes_(bytes)
    , pTcpSocket_(p)
{
}

void RequestExecutable::run()
{
    //logger()->debug("start send executable!!!");
    pTcpSocket_->write(bytes_);
    pTcpSocket_->waitForBytesWritten();
    //logger()->debug("send executable done!!!");
}
