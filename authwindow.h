#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();
    //Возвращает значение поля lineLogin
    QString getLineLogin();
    //Возвращает значение поля linePassword
    QString getLinePassword();
    /*Возвращает id роли
     *(0 - администратор, 1 - деспетчер деканата, 2 - студент)
     * если авторизация успешна, иначе возвращает -1
    */
    int findUser(QString login, QString password);

    QString Login;
    QString Password;
    int Role;

public slots:
    //! Обрабатывает подтверждение диалога.
    void accept() Q_DECL_OVERRIDE;

private:
    Ui::AuthWindow *ui;

};

#endif // AUTHWINDOW_H
