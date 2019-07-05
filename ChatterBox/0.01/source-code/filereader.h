#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QByteArray>
class FileReader
{
public:
    FileReader(QString filename);
    QString getAll();
    QJsonObject getJson();
private:
    QByteArray val;
};

#endif // FILEREADER_H
