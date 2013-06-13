#include "ThreadObjectBase.h"

ThreadObjectBase::ThreadObjectBase(QObject *parent)
	: QObject(parent)
{
}

ThreadObjectBase::ThreadObjectBase(QMap<FileInfor, QByteArray> *pDataBuffer, QObject *parent)
	: QObject(parent)
	, pMap_dataBuffer_(pDataBuffer)
{
}



