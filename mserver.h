#ifndef MSERVER_H
#define MSERVER_H

#include <QTcpServer>
#include "mthread.h"
#include "global_vars.h"
#include <QDebug>

class mServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit mServer(QObject *parent = 0);

signals:

public slots:
    void startServer();

protected:
    void incomingConnection(int sockID);

};

#endif // MSERVER_H
