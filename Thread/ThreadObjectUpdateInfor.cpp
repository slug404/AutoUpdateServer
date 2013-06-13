#include "ThreadObjectUpdateInfor.h"

ThreadObjectUpdateInfor::ThreadObjectUpdateInfor(const QByteArray &updateInfor, QTcpSocket *p, QObject *parent)
	: ThreadObjectBase(parent)
	, updateInfor_(updateInfor)
	, pTcpSocket_(p)
{
}
