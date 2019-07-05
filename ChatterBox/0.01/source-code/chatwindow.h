#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QString ip,QString name);
    ~ChatWindow();
    Ui::ChatWindow *ui;
    QString ip;
    QString name;
    void autoStroll();
private slots:
    void on_sendButton_clicked();
};

#endif // CHATWINDOW_H
