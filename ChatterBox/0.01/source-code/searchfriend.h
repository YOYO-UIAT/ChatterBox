#ifndef SEARCHFRIEND_H
#define SEARCHFRIEND_H

#include <QWidget>

namespace Ui {
class SearchFriend;
}

class SearchFriend : public QWidget
{
    Q_OBJECT

public:
    explicit SearchFriend(QWidget *parent = nullptr);
    void Search_for_Friend(QString ip);
    ~SearchFriend();

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::SearchFriend *ui;
};

#endif // SEARCHFRIEND_H
