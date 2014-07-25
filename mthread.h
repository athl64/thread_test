#ifndef MTHREAD_H
#define MTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include "global_vars.h"
#include "header_parser.h"

class mThread : public QThread
{
    Q_OBJECT
public:
    explicit mThread(int sockID, QObject *parent = 0);
    void run();

signals:
    void sockError(QTcpSocket::SocketError);

private:
    QTcpSocket *sock;
    int sockDescriptor;

public slots:
    void connected();
    void readyRead();
    void disconnected();

};

#endif // MTHREAD_H
