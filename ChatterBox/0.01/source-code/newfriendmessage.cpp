#include "newfriendmessage.h"
#include "ui_newfriendmessage.h"
#include <QApplication>
#include "frienditem.h"
#include "ui_frienditem.h"
#include "filereader.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "filewriter.h"
#include <QPushButton>
#include "connection.h"
#include "usernamelib.h"
#include "iplib.h"

NewFriendMessage::NewFriendMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewFriendMessage)
{
    ui->setupUi(this);
    ui->friendsList->setGeometry(0,0,width(),height());
    FileReader fr(QCoreApplication::applicationDirPath()+"\\newfriend.json");
    auto json=fr.getJson();
    auto arr=json.take("newfriend").toArray();
    this->ja=arr;
    int c=0;
    for(auto i:arr){
        QListWidgetItem *item=new QListWidgetItem(ui->friendsList);
        item->setSizeHint(QSize(0,50));
        ui->friendsList->addItem(item);
        auto fi=new FriendItem();
        fi->ui->accept->setObjectName(QString::number(c));
        fi->ui->ignore->setObjectName(QString::number(c));
        connect(fi->ui->accept,SIGNAL(clicked()),this,SLOT(accept()));
        connect(fi->ui->ignore,SIGNAL(clicked()),this,SLOT(ignore()));
        fi->ui->ip->setText(i.toObject().take("ip").toString());
        fi->ui->name->setText(i.toObject().take("name").toString());
        ui->friendsList->setItemWidget(item,fi);
        c++;
    }
}

NewFriendMessage::~NewFriendMessage()
{
    delete ui;
}
void NewFriendMessage::accept(){
    qDebug()<<"Accept";
    QPushButton *qp=qobject_cast<QPushButton*>(sender());
    auto *item=ui->friendsList->item(qp->objectName().toInt());
    auto p=qobject_cast<FriendItem*>(qp->parentWidget());
    this->ja.removeAt(qp->objectName().toInt());
    Connection c(p->ui->ip->text(),"callback:"+iplib::GetLocalIpAddress()+":"+UserNameLib::getUserName());
    delete item;
    FileWriter fw(QCoreApplication::applicationDirPath()+"\\newfriend.json");
    QJsonObject jo;
    jo.insert("newfriend",ja);
    fw.writeJson(jo);
}
void NewFriendMessage::ignore(){
    qDebug()<<"ignore";
    QPushButton *qp=qobject_cast<QPushButton*>(sender());
    this->ja.removeAt(qp->objectName().toInt());
    auto *item=ui->friendsList->item(qp->objectName().toInt());
    delete item;
    FileWriter fw(QCoreApplication::applicationDirPath()+"\\newfriend.json");
    QJsonObject jo;
    jo.insert("newfriend",ja);
    fw.writeJson(jo);
}
void NewFriendMessage::addNewFriendRequest(QString name,QString ip){
    QListWidgetItem *item=new QListWidgetItem(ui->friendsList);
    item->setSizeHint(QSize(0,50));
    ui->friendsList->addItem(item);
    auto fi=new FriendItem();
    fi->ui->ip->setText(ip);
    fi->ui->name->setText(name);
    fi->ui->accept->setObjectName(QString::number(ui->friendsList->count()-1));
    fi->ui->ignore->setObjectName(QString::number(ui->friendsList->count()-1));
    connect(fi->ui->accept,SIGNAL(clicked()),this,SLOT(accept()));
    connect(fi->ui->ignore,SIGNAL(clicked()),this,SLOT(ignore()));
    ui->friendsList->setItemWidget(item,fi);
    QJsonObject o;
    o.insert("name",name);
    o.insert("ip",ip);
    ja.append(o);
    FileWriter fw(QCoreApplication::applicationDirPath()+"\\newfriend.json");
    QJsonObject jo;
    jo.insert("newfriend",ja);
    fw.writeJson(jo);
}
