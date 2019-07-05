#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <QString>
#include <QList>
#include <chatwindow.h>
#include <friends.h>
#include <QDebug>
#include <ui_chatwindow.h>
#include <ui_friends.h>
#include <usernamelib.h>
namespace MessageDispatcher {
static QList<ChatWindow*> windows;
static QList<Friends*> friends;
static void dispatch(QString ip,QString sender,QString message){
    int len=MessageDispatcher::windows.length();
    ChatWindow *w;
    bool flag=0;
    for(int i=0;i<len;i++){
        if(MessageDispatcher::windows[i]->ip==ip){
            w=MessageDispatcher::windows[i];flag=1;break;
        }
    }
    if(!flag){
        qDebug()<<QString("分发消息")+"\""+message+"\""+"时出错：无法找到IP地址"+ip;
    }else{
        int len2=MessageDispatcher::friends.length();
        for(int i=0;i<len2;i++){
            if(MessageDispatcher::friends[i]->ip==ip){
                auto &f=MessageDispatcher::friends[i];
                f->count++;
                f->ui->messageCount->show();
                f->ui->messageCount->setText(QString::number(f->ui->messageCount->text().toInt()+1));
                break;
            }
        }
        w->ui->messages->setText(w->ui->messages->toPlainText()+"\n\n"+sender+'\n'+message);
    }
}
}


#endif // MESSAGEDISPATCHER_H
