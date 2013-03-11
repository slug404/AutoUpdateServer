#ifndef REQUESTUPDATEINFOR_H
#define REQUESTUPDATEINFOR_H

#include "RunnableBase.h"
#include <QTcpSocket>

class RequestUpdateInfor : public RunnableBase
{
    Q_OBJECT
public:
    RequestUpdateInfor(const QByteArray &updateInfor, QTcpSocket *p);

protected:
    void run();

private:
    QByteArray updateInfor_;
    QTcpSocket *pTcpSocket_;
};

#endif // REQUESTUPDATEINFOR_H
