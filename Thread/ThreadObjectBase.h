#ifndef THREADOBJECTBASE_H
#define THREADOBJECTBASE_H

#include <QObject>
#include <QMap>
#include "Common.h"

class ThreadObjectBase : public QObject
{
    Q_OBJECT
public:
    explicit ThreadObjectBase(QObject *parent = 0);
    explicit ThreadObjectBase(QMap<FileInfor, QByteArray> *pDataBuffer, QObject *parent = 0);

    inline void setSocketDescriptor(int socketDescriptor) { tcpSocketDescriptor_ = socketDescriptor ;}
    int getSocketDescriptor() const { return tcpSocketDescriptor_; }

protected:
    int tcpSocketDescriptor_;
    QMap<FileInfor, QByteArray> *pMap_dataBuffer_;
};

#endif // THREADOBJECTBASE_H
