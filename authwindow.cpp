#include "authwindow.h"
#include "ui_authwindow.h"
#include "databases.h"
#include "dataclasses/user.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

AuthWindow::AuthWindow(DataBases &sDB, QWidget *parent) : db(sDB),
    QDialog(parent),
    ui(new Ui::AuthWindow)
{
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
    int role = db.findAuthUser(ui->lineLogin->text(), ui->linePassword->text());

    if (role == -1)
    {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль, попробуйте заново.");
    }
    else
    {
        mode = role;
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
