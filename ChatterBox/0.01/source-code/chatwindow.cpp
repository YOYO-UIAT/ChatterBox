#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "connection.h"
#include <QDebug>
#include "usernamelib.h"
ChatWindow::ChatWindow(QString ip,QString name) :
    QWidget(nullptr),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    this->ip=ip;
    setWindowTitle("聊天: "+name);
    this->name=name;
    connect(this->ui->messages,&QTextBrowser::textChanged,this,&ChatWindow::autoStroll);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}
void ChatWindow::autoStroll(){
    QTextCursor cur=ui->messages->textCursor();
    cur.movePosition(QTextCursor::End);
    ui->messages->setTextCursor(cur);
}

void ChatWindow::on_sendButton_clicked()
{
    auto txt=ui->textInput->toPlainText();
    Connection c(this->ip,txt);
    if(c.getLastErr()){
        qDebug()<<"错误:无法发送给"+this->ip;
    }else{
        ui->textInput->clear();
        ui->messages->setText(ui->messages->toPlainText()+"\n\n"+UserNameLib::getUserName()+'\n'+txt);
    }
}
