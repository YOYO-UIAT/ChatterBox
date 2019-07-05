#ifndef FRIENDS_H
#define FRIENDS_H

#include <QWidget>
#include <QString>

namespace Ui {
class friends;
}

class Friends : public QWidget
{
    Q_OBJECT

public:
    explicit Friends(QString name,QString ip,QWidget *parent);
    ~Friends();
    QString ip;
    QString name;
    Ui::friends *ui;
    int count=0;
};

#endif // FRIENDS_H
