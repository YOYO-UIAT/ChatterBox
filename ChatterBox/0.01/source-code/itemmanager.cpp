#include "itemmanager.h"
#include <QDebug>
#include "connection.h"
#include <QStringList>
#include "iplib.h"
#include <QFile>
#include <QApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "messagedispatcher.h"
ItemManager::ItemManager(QObject *parent) : QObject(parent){}
/*
 * try:127.0.0.1:Alan
 * callback:192.168.1.107:Robert
 * message:192.168.107.1:Lucy:Hello!
 */
void ItemManager::getItem(const QString msg){
    qDebug()<<"接收消息:"<<msg;
    if(msg.startsWith("try:")){
        auto lst=msg.split(":");
        auto ip=lst[1];
        auto userName=lst[2];
        emit friendRequest(userName,ip);

    }else if(msg.startsWith("callback:")){
        auto lst=msg.split(":");
        auto ip=lst[1];
        auto userName=lst[2];
        emit addFriend(userName,ip);
    }else if(msg.startsWith("message:")){
        auto lst=msg.split(":");
        auto ip=lst[1];
        auto userName=lst[2];
        QString message;
        for(int i=3;i<lst.length();i++){
            if(i!=3)message+=":";
            message+=lst[i];
        }
        MessageDispatcher::dispatch(ip,userName,message);
    }
}
