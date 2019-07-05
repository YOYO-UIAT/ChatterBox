#ifndef NEWFRIENDMESSAGE_H
#define NEWFRIENDMESSAGE_H

#include <QWidget>
#include <QJsonArray>

namespace Ui {
class NewFriendMessage;
}

class NewFriendMessage : public QWidget
{
    Q_OBJECT

public:
    explicit NewFriendMessage(QWidget *parent = nullptr);
    void addNewFriendRequest(QString name,QString ip);
    ~NewFriendMessage();
public slots:
    void accept();
    void ignore();

private:
    Ui::NewFriendMessage *ui;
    QJsonArray ja;
};

#endif // NEWFRIENDMESSAGE_H
