#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>

class ItemManager : public QObject
{
    Q_OBJECT
public:
    explicit ItemManager(QObject *parent = nullptr);
    void getItem(const QString msg);
signals:
    void addFriend(QString name,QString ip);
    void friendRequest(QString name,QString ip);

public slots:

};

#endif // ITEMMANAGER_H
