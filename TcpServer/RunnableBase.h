#ifndef RUNNABLEBASE_H
#define RUNNABLEBASE_H

#include <QObject>
#include <QRunnable>
#include <QMap>
#include <QString>

struct FileInfor
{
    bool operator < (const FileInfor &other) const
    {
        if(fileName < other.fileName)
        {
            return true;
        }
        else if(fileName == other.fileName)
        {
            if(filePath < other.filePath)
            {
               return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    QString fileName;
    QString filePath;
};

class RunnableBase : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RunnableBase(QObject *parent = 0);
    explicit RunnableBase(QMap<FileInfor, QByteArray> *pDataBuffer, QObject *parent = 0);
    
    inline void setSocketDescriptor(int socketDescriptor) { tcpSocketDescriptor_ = socketDescriptor ;}
    int getSocketDescriptor() const { return tcpSocketDescriptor_; }

protected:
    int tcpSocketDescriptor_;
    QMap<FileInfor, QByteArray> *pMap_dataBuffer_;
};

#endif // RUNNABLEBASE_H
