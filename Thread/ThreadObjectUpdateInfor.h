#ifndef THREADOBJECTUPDATEINFOR_H
#define THREADOBJECTUPDATEINFOR_H

#include "ThreadObjectBase.h"
#include <QTcpSocket>

class ThreadObjectUpdateInfor : public ThreadObjectBase
{
	Q_OBJECT
public:
	explicit ThreadObjectUpdateInfor(const QByteArray &updateInfor, QTcpSocket *p, QObject *parent = 0);
	
signals:
	
public slots:

private:
	QByteArray updateInfor_;
	QTcpSocket *pTcpSocket_;
	
};

#endif // THREADOBJECTUPDATEINFOR_H
