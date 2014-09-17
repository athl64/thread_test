#include "mserver.h"

mServer::mServer(QObject *parent) :
    QTcpServer(parent)
{
}

void mServer::startServer(qint32 port)
{
    if(!this->listen(listenHost,port))
    {
        qDebug() << "Can not start server";
    }
    else
    {
        qDebug() << "Server started sucessfuly, listen port " << port;
    }
}

void mServer::incomingConnection(int sockDescriptor)
{
    //qDebug() << "connecting to " << sockDescriptor;
    mThread *thr = new mThread(sockDescriptor,this);
    connect(thr,SIGNAL(finished()),thr,SLOT(deleteLater()));
    thr->start();
}
