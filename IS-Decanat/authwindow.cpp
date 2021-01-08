#include "authwindow.h"
#include "ui_authwindow.h"

#include "databases.h"
#include "dataclasses/user.h"
#include "config.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

AuthWindow::AuthWindow(DataBases &sDB, QWidget *parent) : db(sDB),
    QDialog(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизация");
    //Ограничение длины логина и пароля.
    ui->lineLogin->setMaxLength(30);
    ui->linePassword->setMaxLength(30);
    //Установка режима отображения пароля.
    ui->linePassword->setEchoMode(QLineEdit::Password);
    //Установка заполнителей.
    ui->lineLogin->setPlaceholderText("Имя пользователя");
    ui->linePassword->setPlaceholderText("Пароль");
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::accept()
{
    //Если значения полей совпадают с авторизационными даннымы резервного администратора - войти как администратор, иначе - поиск пользователя.
    if (ui->lineLogin->text() == Config::reservAdminLogin && ui->linePassword->text() == Config::reservAdminPassword) {
        authUser = new User("", "", 2);
    } else {
        authUser = db.findAuthUser(ui->lineLogin->text(), ui->linePassword->text());
    }

    //Если роль == -1(соответствует отсутствию пользователя в БД) - сообщение об ошибке, иначе - завершение с accept.
    if (authUser->getRole() == -1) {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль, попробуйте заново.");
    } else {
        QDialog::accept();
    }
}

