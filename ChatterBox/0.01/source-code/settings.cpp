#include "settings.h"
#include "ui_settings.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <iplib.h>
#include "filereader.h"
#include <QApplication>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->IPAddress->setText(iplib::GetLocalIpAddress());
    FileReader fr(QCoreApplication::applicationDirPath()+"\\data.json");
    auto r=fr.getJson();
    ui->UserName->setText(r.take("name").toString());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    //this->parent->setWindowTitle(QString("ChatterBox: ")+ui->UserName->text());
    this->userName=ui->UserName->text();
    emit saveUserNameF(this->userName);
}
QString Settings::getUserName(){
    return this->userName;
}

