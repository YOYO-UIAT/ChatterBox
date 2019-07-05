#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <winsock2.h>

class Connection
{
public:
    explicit Connection(QString ip,QString sends);
    bool hasErr();
    int getLastErr();

private:
    bool status=0;
};

#endif // CONNECTION_H
