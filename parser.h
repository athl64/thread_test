#ifndef PARSER_H
#define PARSER_H

#include <QtCore>
#include <QString>
#include <QMimeDatabase>

class parser
{
public:
    parser();
    ~parser();

private:
    //QString request;

public:
    QByteArray getFile(QString filePath);
    QString getRequestMethod(QString requestIn);
    QString getRequestContentLength(QString requestIn);
    QString getRequestFilePath(QString requestIn);
};

#endif // PARSER_H
