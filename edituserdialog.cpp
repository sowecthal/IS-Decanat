#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include <QDebug>

EditUserDialog::EditUserDialog(User &sUser, QWidget *parent) : mUser(sUser),
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);
    ui->lineLogin->setMaxLength(30);
    ui->linePassword->setMaxLength(30);
    ui->lineLogin->setPlaceholderText("Имя пользователя");
    ui->linePassword->setPlaceholderText("Пароль");
    ui->linePassword->setText(mUser.getPassword());
    ui->lineLogin->setText(mUser.getLogin());
    if (mUser.getRole() == 0) ui->radioStudent->setChecked(true);
    if (mUser.getRole() == 1) ui->radioSupervisor->setChecked(true);
    if (mUser.getRole() == 2) ui->radioAdmin->setChecked(true);
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}


void EditUserDialog::accept()
{

}
