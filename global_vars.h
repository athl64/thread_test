#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <QtCore>
#include <QHostAddress>

//constants for config
const qint32 listenPort = 3000;                         //listen port
const QHostAddress listenHost = QHostAddress::Any;      //listen host
const qint64 headLen = 8000;                            //HTTP header max lenghth
const qint64 fileLen = 5000000000;                      //file max length
const qint64 fileReadBuferLen = 1000;                   //read files by X-bytes blocks

struct headerStorage {
    QString method;
    QString filePath;
    QString host;
    QString httpVer;
    qint64 contentLength;
};

struct fileInfoStorage {
    QString mimeType;
    qint64 contentLength;
    bool fileOk;
};

class ResponseCodes
{
private:
    QMap<QString, qint32> map;
public:
    ResponseCodes()
    {
        map.insert("",0);
        map.insert("GET",1);
        map.insert("POST",2);
        map.insert("HEAD",3);
        map.insert("LIST",4);
    }
    QMap<QString, qint32> getResponseCodes()
    {
        return map;
    }
};

#endif // GLOBAL_VARS_H
