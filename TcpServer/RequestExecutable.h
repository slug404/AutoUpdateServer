#ifndef REQUESTEXECUTABLE_H
#define REQUESTEXECUTABLE_H

#include "RunnableBase.h"
//#include "Log4Qt/Logger"
class QTcpSocket;

class RequestExecutable : public RunnableBase
{
    Q_OBJECT
	//LOG4QT_DECLARE_QCLASS_LOGGER

public:
    explicit RequestExecutable(const QByteArray &bytes, QTcpSocket *p);
    
signals:
    
public slots:
protected:
    void run();

private:
    QByteArray bytes_;
    QTcpSocket *pTcpSocket_;
};

#endif // REQUESTEXECUTABLE_H
