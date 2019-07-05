#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QJsonObject>
#include <QByteArray>
#include <QFile>

class FileWriter
{
public:
    FileWriter(QString fileName);
    void writeJson(QJsonObject json);
private:
    QFile *file;
};

#endif // FILEWRITER_H
