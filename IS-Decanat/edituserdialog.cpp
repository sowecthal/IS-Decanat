#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include <QDebug>
#include <QMessageBox>

EditUserDialog::EditUserDialog(User &sUser, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog),
    mUser(sUser)
{
    ui->setupUi(this);
    //Ограничение длины логина и пароля
    ui->lineLogin->setMaxLength(30);
    ui->linePassword->setMaxLength(30);
    //Установка текущих значений.
    ui->linePassword->setText(mUser.getPassword());
    ui->lineLogin->setText(mUser.getLogin());
    if (mUser.getRole() == User::roles::STUDENT) ui->radioStudent->setChecked(true);
    if (mUser.getRole() == User::roles::SUPERVISOR) ui->radioSupervisor->setChecked(true);
    if (mUser.getRole() == User::roles::ADMIN) ui->radioAdmin->setChecked(true);
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

User::roles EditUserDialog::getSelectedRole()
{
    //Если выбранна радио-кнопка - вернуть соответствующую ей роль.
    if (ui->radioStudent->isChecked()) {
        return(User::roles::STUDENT);
    }
    if (ui->radioSupervisor->isChecked()) {
        return(User::roles::SUPERVISOR);
    }
    if (ui->radioAdmin->isChecked()) {
        return(User::roles::ADMIN);
    }
    return(User::roles::UNKNOWN);
}

void EditUserDialog::accept()
{
    //Если обнаруженно несовпадение значений - вызываем метод замены, закрываем с accept.
    if ((getSelectedRole() == User::roles::UNKNOWN || ui->lineLogin->text().isEmpty()) || ui->linePassword->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполнены не все поля.");
    } else {
        if (((mUser.getLogin() != ui->lineLogin->text()) || mUser.getPassword() != ui->linePassword->text()) ||  mUser.getRole() != getSelectedRole()) {
            mUser.editUser(ui->lineLogin->text(), ui->linePassword->text(), getSelectedRole());
            QDialog::accept();
        }
        QDialog::close();
    }
}
