#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QString>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    QString getUserName();
    ~Settings();

private slots:
    void on_pushButton_clicked();

signals:
    void saveUserNameF(QString userName);

private:
    Ui::Settings *ui;
    QWidget *parent;
    QString userName;
};

#endif // SETTINGS_H
