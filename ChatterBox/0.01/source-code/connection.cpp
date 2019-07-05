#include "connection.h"
#include <QDebug>
#include <string>
#include <cstring>
#include <thread>

Connection::Connection(QString ip,QString sends)
{
    auto th=std::thread([this,ip,sends](void)mutable->void{
        WORD sockVersion = MAKEWORD(2,2);
        WSADATA data;
        if(WSAStartup(sockVersion, &data) != 0)
        {
            qDebug()<<"Connection类WSA启动失败";
            exit(0);
        }

        SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(sclient == INVALID_SOCKET)
        {
            qDebug()<<"非法套接字";
            exit(0);
        }

        sockaddr_in serAddr;
        serAddr.sin_family = AF_INET;
        serAddr.sin_port = htons(8888);
        std::string str=ip.toStdString();
        serAddr.sin_addr.S_un.S_addr = inet_addr(str.c_str());
        qDebug()<<str.c_str();
        if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
        {
            qDebug()<<"Connection类无法连接套接字";
            closesocket(sclient);
            this->status=1;
        }
        char sendData[sends.length()+1];
        std::strcpy(sendData,sends.toStdString().c_str());
        send(sclient, sendData, strlen(sendData), 0);
        closesocket(sclient);
    });
    th.detach();
}
bool Connection::hasErr(){
    return this->status;
}
int Connection::getLastErr(){
    return this->hasErr();
}
