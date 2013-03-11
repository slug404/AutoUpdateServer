#include "RunnableBase.h"

RunnableBase::RunnableBase(QObject *parent)
    : QObject(parent)
    , pMap_dataBuffer_(NULL)
    , tcpSocketDescriptor_(-1)
{
}

RunnableBase::RunnableBase(QMap<FileInfor, QByteArray> *pDataBuffer, QObject *parent)
    : QObject(parent)
    , pMap_dataBuffer_(pDataBuffer)
    , tcpSocketDescriptor_(-1)
{
}

