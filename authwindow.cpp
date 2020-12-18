#include "authwindow.h"
#include "ui_authwindow.h"

#include <QMessageBox>
#include <QFile>

AuthWindow::AuthWindow(QWidget *parent) :
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

int AuthWindow::findUser(QString login, QString password)
{
    QFile infile(":/data/Users.isd");

    // Открываем файл только для чтения
    if (!infile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Программе не удалось обнаружить необходимый для авторизациии файл");
        throw std::runtime_error((tr("open(): ") + infile.errorString()).toStdString());
    }

    return(1);
}

void AuthWindow::accept()
{
    int state = findUser(ui->lineLogin->text(), ui->linePassword->text());
    if (state == -1)
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
