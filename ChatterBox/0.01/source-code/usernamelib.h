#ifndef USERNAMELIB_H
#define USERNAMELIB_H
#include <QString>
#include "filereader.h"
#include <qjsonarray.h>
#include <QCoreApplication>
#include <QDebug>

namespace UserNameLib{
static QString userName="";
QString getUserName(void);
}
#endif //USERNAMELIB_H
