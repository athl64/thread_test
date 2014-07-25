#include "parser.h"

parser::parser()
{

}

parser::~parser()
{

}

QByteArray parser::getFile(QString filePath)
{
    QByteArray fileBin;

    QFile file(filePath);
    if(file.exists())
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw "file open error!";
        }
        fileBin = file.readAll();
        return fileBin;
    }
    else
    {
        throw "file doesn't exist!";
    }
}

QString parser::getRequestContentLength(QString requestIn)
{
    QString contentLength;


    return contentLength;
}

QString parser::getRequestFilePath(QString requestIn)
{
    QString filePath;
    int posFrom = 0, posTo = 0;

    posFrom = requestIn.indexOf(" ", 0);
    posTo = requestIn.indexOf(" ", posFrom + 1);
    filePath = requestIn.mid(posFrom + 1, posTo - posFrom);

    return filePath;
}

QString parser::getRequestMethod(QString requestIn)
{
    QString method;
    int pos = 0;

    pos = requestIn.indexOf(" ", 0);
    method = requestIn.left(pos);

    return method;
}
