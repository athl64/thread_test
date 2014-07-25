#include "mserver.h"

mServer::mServer(QObject *parent) :
    QTcpServer(parent)
{
}

void mServer::startServer()
{
    if(!this->listen(listenHost,listenPort))
    {
        qDebug() << "Can not start server";
    }
    else
    {
        qDebug() << "Server started sucessfuly";
    }
}

void mServer::incomingConnection(int sockDescriptor)
{
    qDebug() << "connecting to " << sockDescriptor;
    mThread *thr = new mThread(sockDescriptor,this);
    connect(thr,SIGNAL(finished()),thr,SLOT(deleteLater()));
    thr->start();
}
