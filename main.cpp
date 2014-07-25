#include <QCoreApplication>
#include "mthread.h"
#include "mserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    mServer serv;
    serv.startServer();

    return a.exec();
}
