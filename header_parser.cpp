#include "header_parser.h"

header_parser::header_parser()
{

}

header_parser::~header_parser()
{

}

QString header_parser::getHeaderParam(QString *header, QString paramName)
{
    QString resultParam;
    int posFrom = 0;
    int posTo = 0;
    int len = 0;

    posFrom = header->indexOf(paramName,0);
    len = paramName.length() + 1;
    posTo = header->indexOf("\r\n",posFrom + len);
    resultParam = header->mid(posFrom,posTo);

    return resultParam;
}

headerStorage header_parser::getHeaderData(QString HeadString)
{
    headerStorage storage;
    int posEndMethod = 0;
    int posEndFilePath = 0;
    int posEndHttpVer = 0;

    posEndMethod = HeadString.indexOf(" ",0);
    posEndFilePath = HeadString.indexOf(" ", posEndMethod + 1);
    posEndHttpVer = HeadString.indexOf(" ", posEndFilePath + 1);

    storage.method = HeadString.mid(0, posEndMethod);
    storage.filePath = HeadString.mid(posEndMethod, posEndFilePath - posEndMethod);
    storage.httpVer = HeadString.mid(posEndFilePath, posEndHttpVer - posEndFilePath);
    storage.contentLength = getHeaderParam(&HeadString,"Content-Length: ").toInt();
    storage.host = getHeaderParam(&HeadString,"Host: ");

    repairFilePath(&storage.filePath);

    return storage;
}

int header_parser::writeLog(headerStorage *storage)
{
    QFile logFile("Access.log");
    QTextStream streamLog(&logFile);

    if(logFile.open(QIODevice::Append))
    {
        streamLog << QDateTime::currentDateTime().toString() << endl;
        streamLog << storage->method << endl;
        streamLog << storage->filePath << endl;
        streamLog << storage->httpVer << endl;
        streamLog << storage->host << endl;
        streamLog << storage->contentLength << endl << endl;
    }
    else
    {
        return -1;
    }

    logFile.close();

    return 0;
}

fileInfoStorage header_parser::getFileInfo(QString filePath)
{
    fileInfoStorage storage;
    QFile file(filePath);
    QMimeDatabase fileMime;

    if(file.exists() && file.size() <= fileLen)
    {
        storage.fileOk = true;
        storage.contentLength = file.size();
        storage.mimeType = fileMime.mimeTypeForFile(filePath).name();
    }
    else
    {
        storage.fileOk = false;
        storage.contentLength = 0;
        storage.mimeType = "";
    }

    return storage;
}

void header_parser::repairFilePath(QString *filePath)
{
    //remove first space
    if(filePath->at(0) == ' ')
    {
        filePath->remove(0,1);
    }
    //remove first slash
    if(filePath->at(0) == '/')
    {
        filePath->remove(0,1);
    }
    //remove last space
    if(filePath->at(filePath->length() - 1) == ' ')
    {
        filePath->remove(filePath->length() - 1,1);
    }
    //remove host
    if(filePath->indexOf("http://",0))
    {
        int pos = 0;
        pos = filePath->indexOf("/",7);
        filePath->remove(0,pos + 1);
    }
}
