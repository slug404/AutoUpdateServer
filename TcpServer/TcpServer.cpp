#include "TcpServer.h"
#include <QThreadPool>
#include <QThread>
#include <QDebug>
//#include <QMessageBox>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QCryptographicHash>
#include "RequestUpdateInfor.h"
#include "RequestUpdateData.h"
#include "RequestExecutable.h"

long gCountConnect = 0;

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
	, port_(8769)
{
    initData();

	//pThreadPool_ = new QThreadPool(this);
	//pThreadPool_->setMaxThreadCount(QThread::idealThreadCount());
}

bool TcpServer::startServer()
{
	if(!this->listen(QHostAddress::Any, port_))
    {
		qDebug() << ("tcp server bind fail!");
        return false;
    }
	qDebug() << "listen port: " << port_;
	return true;
}

void TcpServer::setListenPort(quint16 port)
{
	port_ = port;
}

void TcpServer::incomingConnection(int handle)
{
    qDebug() << "in comning connection";
    qDebug() << tr("new connect  : ").arg(QString::number(gCountConnect++)) ;
    QTcpSocket *pTcpSocket = new QTcpSocket(this);
    if(!pTcpSocket->setSocketDescriptor(handle))
    {
        qDebug() << "in coming connectionset socket descriptor fail";
        return;
    }
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    pMap_socketDescriptor_tcpSocket_[handle] = pTcpSocket;
    pMap_socketDescriptor_blockSize_[handle] = 0;
}

void TcpServer::slotReadyRead()
{
    QTcpSocket *pTcpSocket = qobject_cast<QTcpSocket *>(sender());
    int socketDescriptor =  pTcpSocket->socketDescriptor();
    if(pMap_socketDescriptor_tcpSocket_.contains(socketDescriptor))
    {
        //qDebug() << "find socketDescriptor!";
        pTcpSocket = pMap_socketDescriptor_tcpSocket_.value(socketDescriptor);
    }
    else
    {
        qDebug() << "can't find sockedescriptor!";
    }

    QDataStream in(pTcpSocket);
    in.setVersion(QDataStream::Qt_4_8);

    qint32 blockSize;

    //这个部分要加锁
    mutex_.lock();
    if(0 == pMap_socketDescriptor_blockSize_.value(socketDescriptor))
    {
        if(pTcpSocket->bytesAvailable() < (qint32)sizeof(qint32))
        {
            return;
        }
        in >> blockSize;
        pMap_socketDescriptor_blockSize_[socketDescriptor] = blockSize;
        qDebug() << "receive request datagram size is:" << blockSize;
    }
    mutex_.unlock();

    qint32 currentSize = pTcpSocket->bytesAvailable();
    if(currentSize < pMap_socketDescriptor_blockSize_[socketDescriptor])
    {
		qDebug() << "currentSize < blockSize" <<"       " << "currentSize:" <<currentSize <<
					"pMap_socketDescriptor_blockSize_[socketDescriptor]:"<<pMap_socketDescriptor_blockSize_[socketDescriptor];
        return;
    }

    qDebug() << "datagram size is" << blockSize;
    qint32 type;
    in >> type;

	//RunnableBase *pRunnable = NULL;
    if(RequestXml == type)
    {
        qDebug() << "request xml message";
		//pRunnable = new RequestUpdateInfor(updateInfor_, pTcpSocket);
		pTcpSocket->write(updateInfor_);
    }
    else if(RequestData == type)
    {
        qDebug() << "request data message";
        int size;
        in >> size;
        qDebug() << "need to update files : " <<size;
        QList<QString> listNames;
        QString name;
        for(int i = 0; i != size; ++i)
        {
            in >> name;
            qDebug() << name;
            listNames.append(name);
        }

        if(listNames.isEmpty())
        {
			qDebug() << ("request update files list is empty");
        }
		//pRunnable = new RequestUpdateData(listNames, &pMap_fileName_data_ , serializeData_, pTcpSocket);
		{
			QDataStream out(&bytes_, QIODevice::WriteOnly);
			out.setVersion(QDataStream::Qt_4_8);
			out << (qint32)0;
			out << (qint32)1; //RequestData
			out << (qint32)listNames.size(); //也是用来占位, 具体返回的数据的数量还需要看下面的计算
			int count = 0;
			for(int i = 0; i != listNames.size(); ++i)
			{
				QString name = listNames.at(i);

				if(!pMap_fileName_data_.contains(name))
				{
					qDebug() << "update data don't contains " << name;
					continue;
				}

				QByteArray data = pMap_fileName_data_.value(name);
				out << name;
				out << data;
				++count;
			}
			if(listNames.size() != count)
			{
				out.device()->seek(2 * (qint32)sizeof(qint32));
				out << count;
			}

			//在这里加入序列化后的数据
			out << serializeData_;

			out.device()->seek(0);
			qint32 size = bytes_.size() - (qint32)sizeof(qint32);
			out << (qint32)size;
		}
    }
    else if(Executable == type)
    {
		qDebug() << ("request executable");
	//	pRunnable = new RequestExecutable(bytes_, pTcpSocket);

    }
    else
    {
        qDebug()<< "fuck";
        return;
    }
//    pRunnable->setSocketDescriptor(socketDescriptor);
//    pRunnable->setAutoDelete(true);    //应该是能delete的, 虚连接是在数据链路层的事情, 那个不管我们的是, 应该只要不调用close, 就不会断开
	//pThreadPool_->start(pRunnable);
    pMap_socketDescriptor_blockSize_[socketDescriptor] = 0;
}

void TcpServer::initData()
{
    qDebug() << "init tcpserver";
    updateInfor_.clear();
    //在这个地方递归的读取这个目录中的所有文件
    //还需要排除不需要的目录
    QFile file("./server.xml");

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "can't open file server.xml";
        return;
    }
    QString buffer = file.readAll();
	qDebug() << (buffer);

    QDataStream out(&updateInfor_, QIODevice::WriteOnly);
    out << (qint32)0;
    out << (qint32)RequestXml;
    out << buffer;

    out.device()->seek(0);
    qint32 size = updateInfor_.size() - (qint32)sizeof(qint32);
    out << (qint32)size;
    file.close();

    QFile file1("./serialize.dat");
    if(!file1.open(QFile::ReadOnly))
    {
        qDebug() << "can't open file : serialize.dat";
        return;
    }

    serializeData_ = file1.readAll();
    file1.close();
    qDebug() << "serialize size :" << serializeData_.size();
    QMap<QString, QString> mapTest;
    QDataStream aaaaaa(&serializeData_, QIODevice::ReadOnly);
    aaaaaa >> mapTest;
    qDebug() << "serialize map :" << mapTest;

    QFile file2("Mind+.exe");
    if(!file2.open(QFile::ReadOnly))
    {
        qDebug() << "can't open file Mind+.exe";
        return;
    }
    QByteArray bytes = file2.readAll();
	qDebug() << (tr("size of Mind+.exe is :") + QString::number(bytes.size()));

    QDataStream out2(&bytes_, QIODevice::WriteOnly);
    out2 << (qint32)0;
    out2 << (qint32)Executable;
    out2 << QString("Mind+.exe");
    out2 << bytes;
    //计算校验值
    QByteArray md5 = QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
    out2 << md5;
	qDebug() << (QString(md5));
    out2.device()->seek(0);
    qint32 size2 = bytes_.size() - (qint32)sizeof(qint32);
    out2 << (qint32)size2;
    file2.close();

    QStringList list;
    list << "./resource/tools";
    traveDirectory("./", list);
}

void TcpServer::traveDirectory(const QString &str, const QStringList &filterFolderPaths)
{
    //好了明天的工作就是开始遍历数据, 然后生成xml
    //先处理files
    QDir dir(str);
    dir.setFilter(QDir::Files);
    if(!dir.entryList().isEmpty())
    {
        foreach (QString fileName, dir.entryList())
        {
            QString path = str + dir.separator() + fileName;

            //Mind+这个名字在xml里面有问题, 特殊情况特殊处理
            if("AutoUpdateServer.exe" == fileName)
            {
                continue;
            }
            else if("AutoCreateVersions.exe" == fileName)
            {
                continue;
            }
            else if("server.xml" == fileName)
            {
                continue;
            }
            else if("serialize.dat" == fileName)
            {
                continue;
            }
            else if ("libLog4Qt.dll" == fileName)
            {
                continue;
            }
            else if("setting.ini" == fileName)
            {
                continue;
            }
            else if("MindUpgrader.exe" == fileName)
            {
                continue;
            }
            else if("Thumbs.db" == fileName)
            {
                continue;
            }
            else if(".DS_Store" == fileName)
            {
                continue;
            }
            else if("Buffer.mpb" == fileName)
            {
                continue;
            }

            QFile file(path);
            if(!file.open(QFile::ReadOnly))
            {
                file.close();
				qDebug() << ("file open error");
                continue;
            }

            QByteArray fileData = file.readAll();
            pMap_fileName_data_[fileName] = fileData;

            file.close();
        }
    }

    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    if(dir.entryList().isEmpty())
    {
        return;
    }
    else
    {
        //然后继续遍历子目录
        dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (QString dirName, dir.entryList())
        {
            QString path = str + dir.separator() + dirName;

            bool bFilter = false;
            foreach (QString tmp, filterFolderPaths)
            {
                if(path.contains(tmp))
                {
                    bFilter = true;
                    break;
                }
            }

            if(bFilter)
            {
                qDebug() << "filter:" << path;
            }
            else
            {
                traveDirectory(path, filterFolderPaths);
            }

        }
    }
}
