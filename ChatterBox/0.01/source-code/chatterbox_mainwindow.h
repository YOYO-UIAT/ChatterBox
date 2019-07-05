#ifndef CHATTERBOX_MAINWINDOW_H
#define CHATTERBOX_MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QString>
#include "settings.h"
#include "itemmanager.h"
#include "searchfriend.h"
#include "newfriendmessage.h"
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QListWidgetItem>

namespace Ui {
class Chatterbox_MainWindow;
}

class Chatterbox_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chatterbox_MainWindow(QWidget *parent=nullptr);
    void settingTriggered();
    void setUp(QString username,QJsonArray friends);
    void changeUserName(QString name);
    void addFriend(QString name,QString ip);
    void SearchF();
    void messageTriggered();
    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void closeEvent(QCloseEvent *event);
    ~Chatterbox_MainWindow();
signals:
    void recvMsg(QString msg);
private:
    Ui::Chatterbox_MainWindow *ui;
    QString username;
    QJsonArray friends;
    Settings *s;
    ItemManager *im;
    SearchFriend *sf;
    NewFriendMessage *nfm;
    QSystemTrayIcon *sys;
private slots:
    void doubleclicked(QListWidgetItem *item);
};

#endif // CHATTERBOX_MAINWINDOW_H
