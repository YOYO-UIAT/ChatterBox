#include "searchfriend.h"
#include "ui_searchfriend.h"
#include "connection.h"
#include "iplib.h"
#include <QMessageBox>
#include "usernamelib.h"

SearchFriend::SearchFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchFriend)
{
    ui->setupUi(this);
}

SearchFriend::~SearchFriend()
{
    delete ui;
}

void SearchFriend::on_lineEdit_returnPressed()
{
    Search_for_Friend(ui->lineEdit->text());
}

void SearchFriend::on_pushButton_clicked()
{
    Search_for_Friend(ui->lineEdit->text());
}
void SearchFriend::Search_for_Friend(QString ip){
    Connection c(ip,"try:"+iplib::GetLocalIpAddress()+":"+UserNameLib::getUserName());
    if(c.getLastErr()){
        QMessageBox::critical(nullptr, "错误", "未找到此好友", QMessageBox::Ok, QMessageBox::Ok);
    }
}
