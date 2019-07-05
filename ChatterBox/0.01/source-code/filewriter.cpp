#include "filewriter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

FileWriter::FileWriter(QString fileName)
{
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly)){
        qDebug()<<"无法打开文件";
        exit(0);
    }
}
void FileWriter::writeJson(QJsonObject json){
    QJsonDocument jdoc;
    jdoc.setObject(json);
    QByteArray jba=jdoc.toJson(QJsonDocument::Compact);
    file->write(jba);
    file->close();
}
