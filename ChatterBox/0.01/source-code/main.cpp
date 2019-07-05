
#include <messagedispatcher.h>
#include "chatterbox_mainwindow.h"
#include <QApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QJsonParseError>
#include <QDebug>
#include "filereader.h"
#include <thread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QFile file("F:\\Python\\Qt\\build-ChatterBox-Desktop_Qt_5_11_2_MinGW_32bit-Debug\\debug\\data.json");
    FileReader fr(QCoreApplication::applicationDirPath()+"\\data.json");
    QJsonObject jobj=fr.getJson();
    QString name;
    if(jobj.contains("name")){
        name=jobj.value("name").toString();
    }else{
        qDebug()<<"JSON文件遭到损坏：无法找到name";
        exit(0);
    }
    QJsonArray farr;
    if(jobj.contains("friends")){
        farr=jobj.value("friends").toArray();
    }else{
        qDebug()<<"JSON文件遭到损坏：无法找到friends";
        exit(0);
    }
    Chatterbox_MainWindow w;w.show();
    w.setUp(name,farr);
    return a.exec();
}
