#include "filereader.h"
#include <QDebug>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>

FileReader::FileReader(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"无法打开文件";
        exit(0);
    }
    QByteArray ba=file.readAll();
    file.close();
    this->val=ba;
}
QString FileReader::getAll(){
    return this->val;
}
QJsonObject FileReader::getJson(){
    QJsonParseError err;
    QJsonDocument jdoc(QJsonDocument::fromJson(this->val,&err));
    if(err.error != QJsonParseError::NoError){
        qDebug()<<val<<"\n";
        qDebug()<<"JSON文件错误"<<'\n';
        exit(0);
    }
    QJsonObject jobj=jdoc.object();
    return jobj;
}
