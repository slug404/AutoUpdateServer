#include "ThreadObjectBase.h"

ThreadObjectBase::ThreadObjectBase(QMap<FileInfor, QByteArray> *pDataBuffer, QObject *parent)
	: QObject(parent)
	, pMap_dataBuffer_(pDataBuffer)
{
}
