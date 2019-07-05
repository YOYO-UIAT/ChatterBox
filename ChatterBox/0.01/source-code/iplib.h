#ifndef IPLIB_H
#define IPLIB_H
#include <QDebug>
#include <QString>
#include <winsock2.h>
#include <string>
namespace iplib{
QString getComputerUserName();
QString GetLocalIpAddress();
}


#endif // IPLIB_H
