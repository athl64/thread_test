#include "mthread.h"

mThread::mThread(int sockID, QObject *parent) :
    QThread(parent)
{
    this->sockDescriptor = sockID;
}

void mThread::run()
{
    sock = new QTcpSocket();
    if(!sock->setSocketDescriptor(sockDescriptor))
    {
        emit sockError(sock->error());
        return;
    }
    connect(sock,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(sock,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    connect(sock,SIGNAL(connected()),this,SLOT(connected()),Qt::DirectConnection);

    //qDebug() << "thread for socket ID " << sockDescriptor;

    //qDebug() << "connecting from IP: " << sock->peerAddress().toString();

    exec();
}

void mThread::readyRead()
{
    QByteArray dataReceived = sock->readAll();
    QByteArray dataSent;
    headerStorage HeadData;
    fileInfoStorage FileData;
    header_parser *parse = new header_parser();

    HeadData = parse->getHeaderData(QString(dataReceived));
    FileData = parse->getFileInfo(HeadData.filePath);
    parse->writeLog(&HeadData);

    if(HeadData.method == "GET")
    {
        if(FileData.fileOk)
        {
            dataSent.append("HTTP/1.1 200 OK \r\n");
            dataSent.append("Content-Length: " + QString::number(FileData.contentLength) + "\r\n");
            dataSent.append("Content-Type: " + FileData.mimeType + "\r\n\r\n");
            sock->write(dataSent);

            QFile fileToSend(HeadData.filePath);
            if(fileToSend.open(QIODevice::ReadOnly))
            {
                QByteArray fileContent = fileToSend.readAll();
                sock->write(fileContent);
            }
        }
        else
        {
            dataSent.append("HTTP/1.1 404 \r\n\r\nFile too large or not found, sorry");
            sock->write(dataSent);
        }
    }
    else if(HeadData.method == "POST")
    {
        dataSent.append("HTTP/1.1 404 \r\n\r\nPOST will be added later");
        sock->write(dataSent);
    }
    else
    {
        dataSent.append("HTTP/1.1 400/405 \r\n\r\nUnrecognized or bad request");
    }

    //close instantly when sent response
    sock->close();
}

void mThread::connected()
{
    //qDebug() << "connected " << sockDescriptor << " socket";
}

void mThread::disconnected()
{
    sock->deleteLater();
    //qDebug() << "disconnected " << sockDescriptor << " socket";
    exit(0);
}
