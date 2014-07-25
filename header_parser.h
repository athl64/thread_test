#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H

#include "global_vars.h"
#include <QtCore>

class header_parser
{
public:
    header_parser();
    ~header_parser();
    headerStorage getHeaderData(QString HeadString);
    int writeLog(headerStorage *storage);
    fileInfoStorage getFileInfo(QString filePath);

private:
    QString getHeaderParam(QString *header, QString paramName);
    void repairFilePath(QString *filePath);
};

#endif // HEADER_PARSER_H
