#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QWidget>

namespace Ui {
class FriendItem;
}

class FriendItem : public QWidget
{
    Q_OBJECT

public:
    explicit FriendItem(QWidget *parent = nullptr);
    ~FriendItem();
    Ui::FriendItem *ui;
private:

};

#endif // FRIENDITEM_H
