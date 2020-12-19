#include "authwindow.h"
#include "ui_authwindow.h"
#include "databases.h"
#include "dataclasses/user.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

AuthWindow::AuthWindow(DataBases sDB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthWindow)
{
    qDebug() << "[ IN AUTHWINDOW ]";
    db = sDB;
    ui->setupUi(this);
    this->setWindowTitle("Авторизация");
    ui->lineLogin->setMaxLength(30);
    ui->linePassword->setMaxLength(30);
    ui->linePassword->setEchoMode(QLineEdit::Password);
    ui->lineLogin->setPlaceholderText("Имя пользователя");
    ui->linePassword->setPlaceholderText("Пароль");
}

AuthWindow::~AuthWindow()
{
    delete ui;
}



void AuthWindow::accept()
{
    User nUser(ui->lineLogin->text(), ui->linePassword->text(), -1);

    nUser.setRole(db.findUser(nUser));

    if (nUser.getRole() == -1)
    {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль, попробуйте заново.");
    }
    else
    {
        QDialog::accept();
    }
}

QString AuthWindow::getLineLogin()
{
    return(ui->lineLogin->text());
}

QString AuthWindow::getLinePassword()
{
    return(ui->linePassword->text());
}
