#include "iplib.h"
namespace iplib
{
QString getComputerUserName(){
    const int maxLen=300;
    DWORD dwNameLen;
    dwNameLen=maxLen;
    wchar_t name[maxLen];
    if(!GetUserName(name,&dwNameLen)){
        qDebug()<<"获取计算机用户名错误\n";
        return "未命名";
    }else{
        return QString::fromWCharArray(name);
    }
}

QString GetLocalIpAddress(){
    WORD wVersionRequested = MAKEWORD(2, 2);

    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
        return "";

    char local[255] = {0};
    gethostname(local, sizeof(local));
    hostent* ph = gethostbyname(local);
    if (ph == nullptr)
        return "";

    in_addr addr;
    memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // 这里仅获取第一个ip

    std::string localIP;
    localIP.assign(inet_ntoa(addr));

    //WSACleanup();
    return QString::fromStdString(localIP);
}
}
