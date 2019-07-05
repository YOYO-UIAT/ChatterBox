#include "friends.h"
#include "ui_friends.h"

Friends::Friends(QString name,QString ip,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friends)
{
    ui->setupUi(this);
    ui->friendName->setText(name);
    ui->ip->setText(ip);
    this->ip=ip;
    this->name=name;
    this->count=0;
}

Friends::~Friends()
{
    delete ui;
}
