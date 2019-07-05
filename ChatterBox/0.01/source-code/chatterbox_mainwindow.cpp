#include <messagedispatcher.h>
#include <winsock2.h>
#include "friends.h"
#include "chatterbox_mainwindow.h"
#include "ui_chatterbox_mainframe.h"
#include <thread>
#include "QDebug"
#include "itemmanager.h"
#include <QJsonObject>
#include <mutex>
#include <QJsonDocument>
#include <QFile>
#include "settings.h"
#include "iplib.h"
#include "searchfriend.h"
#include "filewriter.h"
#include "usernamelib.h"
#include <QSystemTrayIcon>
#include "chatwindow.h"
#include "ui_friends.h"


std::mutex mu;
void Listen(Chatterbox_MainWindow *cmw){
    WORD sockVersion=MAKEWORD(2,2);
    WSADATA wsadata;
    if(WSAStartup(sockVersion,&wsadata)!=0){
        qDebug()<<"启动错误\n";
        exit(0);
    }
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        qDebug()<<"套接字错误\n";
        exit(0);
    }
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        qDebug()<<"绑定失败\n";
    }
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
        qDebug()<<"监听错误\n";
        exit(0);
    }
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[2000];
    while (true)
    {
        qDebug()<<"等待连接...\n";
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            qDebug()<<"接受错误\n";
            continue;
        }
        qDebug()<<"接受到一个连接："<<inet_ntoa(remoteAddr.sin_addr)<<"\n";

        //接收数据
        int ret = recv(sClient, revData, 2000, 0);
        if(ret > 0)
        {
            revData[ret] = 0x00;
            qDebug()<<revData<<'\n';
            mu.lock();
            emit cmw->recvMsg(QString(revData));
            mu.unlock();
        }
    }
    closesocket(slisten);
    WSACleanup();
}

Chatterbox_MainWindow::Chatterbox_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chatterbox_MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(QApplication::applicationDirPath()+"\\EXEICON.ico"));
    this->setCentralWidget(ui->fw);
    this->im=new ItemManager();
    this->nfm=new NewFriendMessage();
    sys=new QSystemTrayIcon(this);
    QObject::connect(this,&Chatterbox_MainWindow::recvMsg,im,&ItemManager::getItem);
    QObject::connect(im,&ItemManager::addFriend,this,&Chatterbox_MainWindow::addFriend);
    QObject::connect(im,&ItemManager::friendRequest,nfm,&NewFriendMessage::addNewFriendRequest);
    QObject::connect(ui->fw,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleclicked(QListWidgetItem*)));
    connect(ui->actionsettings,&QAction::triggered,this,&Chatterbox_MainWindow::settingTriggered);
    connect(ui->actionSearch,&QAction::triggered,this,&Chatterbox_MainWindow::SearchF);
    connect(ui->actionmessage,&QAction::triggered,this,&Chatterbox_MainWindow::messageTriggered);
    connect(sys, &QSystemTrayIcon::activated, this, &Chatterbox_MainWindow::activeTray);
    std::thread the(Listen,this);
    the.detach();
}
void Chatterbox_MainWindow::SearchF(){
    sf=new SearchFriend();
    this->sf->show();
}
void Chatterbox_MainWindow::messageTriggered(){
    this->nfm->show();
}
void Chatterbox_MainWindow::activeTray(QSystemTrayIcon::ActivationReason reason){
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
            show();
            break;
        case QSystemTrayIcon::Trigger:
            show();
            break;
    }
}

void Chatterbox_MainWindow::doubleclicked(QListWidgetItem *item){
    auto window=new ChatWindow((qobject_cast<Friends*>(ui->fw->itemWidget(item)))->ip,
                               (qobject_cast<Friends*>(ui->fw->itemWidget(item)))->name);
    MessageDispatcher::windows.append(window);
    window->show();
}
void Chatterbox_MainWindow::closeEvent(QCloseEvent *event){
    event->ignore();
    this->hide();
    QIcon icon(QCoreApplication::applicationDirPath()+"\\EXEICON.ico");
    sys->setIcon(icon);
    sys->setToolTip("Chatterbox: "+UserNameLib::getUserName());
    sys->show();
}
Chatterbox_MainWindow::~Chatterbox_MainWindow()
{
    delete ui;
}

void Chatterbox_MainWindow::settingTriggered(){
    qDebug()<<"设置";
    s=new Settings(nullptr);
    s->show();
    QObject::connect(s,&Settings::saveUserNameF,this,&Chatterbox_MainWindow::changeUserName);
}

void Chatterbox_MainWindow::setUp(QString username,QJsonArray friends){
    this->username=username;
    this->friends=friends;
    if(username==""){
        this->username=iplib::getComputerUserName();
    }
    this->setWindowTitle(QString("ChatterBox: ")+this->username);
    for(int i=0;i<this->friends.size();i++){
        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(0,50));
        ui->fw->addItem(item);
        auto Fw=new Friends(friends.at(i).toObject().value("name").toString(),friends.at(i).toObject().value("ip").toString(),ui->fw);
        Fw->ui->messageCount->setVisible(false);
        MessageDispatcher::friends.append(Fw);
        ui->fw->setItemWidget(item,Fw);
    }
    ui->fw->setResizeMode(QListView::Adjust);
    ui->fw->setAutoScroll(true);
}
void Chatterbox_MainWindow::changeUserName(QString name){
    this->username=name;
    this->setWindowTitle(QString("ChatterBox: ")+name);
    QJsonObject json;
    UserNameLib::userName=this->username;
    json.insert("name",this->username);
    json.insert("friends",this->friends);
    FileWriter writer(QCoreApplication::applicationDirPath()+"\\data.json");
    writer.writeJson(json);
}
void Chatterbox_MainWindow::addFriend(QString name,QString ip){
    QJsonObject newFr;
    newFr.insert("name",name);
    newFr.insert("ip",ip);
    for(auto i:this->friends){
        if(i.toObject().take("ip").toString()==ip){
            return;
        }
    }
    this->friends.append(newFr);
    QListWidgetItem *item=new QListWidgetItem();
    item->setSizeHint(QSize(0,50));
    ui->fw->addItem(item);
    auto Fw=new Friends(name,ip,ui->fw);
    Fw->ui->messageCount->setVisible(false);
    ui->fw->setItemWidget(item,Fw);
    MessageDispatcher::friends.append(Fw);
    QJsonObject json;
    json.insert("name",this->username);
    json.insert("friends",this->friends);
    QJsonDocument jdoc;
    jdoc.setObject(json);
    FileWriter w(QCoreApplication::applicationDirPath()+"\\data.json");
    w.writeJson(json);
}
