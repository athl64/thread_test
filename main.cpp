#include <QCoreApplication>
#include "mthread.h"
#include "mserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    mServer serv;

    //
    if(argc > 1)
    {
        serv.startServer(QString(argv[1]).toInt());
    }
    else
    {
        serv.startServer();
    }
    //

    //serv.startServer();

    return a.exec();
}
