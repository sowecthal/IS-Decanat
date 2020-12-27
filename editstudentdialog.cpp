#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include <QMessageBox>
#include <QDebug>

EditStudentDialog::EditStudentDialog(User &sStuden, QWidget *parent) : mStudent(sStuden),
    QDialog(parent),
    ui(new Ui::editStudentDialog)
{
    ui->setupUi(this);
    ui->lineSurname->setMaxLength(20);
    ui->lineName->setMaxLength(20);
    ui->linePatronymic->setMaxLength(20);
    ui->lineNumber->setMaxLength(10);
    ui->lineSurname->setText(mStudent.mSurname);
    ui->lineName->setText(mStudent.mName);
    ui->linePatronymic->setText(mStudent.mPatronymic);
    ui->lineNumber->setText(QString::number(mStudent.mID));

    QValidator *validator = new QIntValidator(1, 999999999, this);
    ui->lineNumber->setValidator(validator);
    ui->labelLogin->setText(mStudent.getLogin());

    switch (mStudent.mGrant)
    {
        case 0:
            ui->grantComboBox->setCurrentIndex(0);
            break;
        case 1:
            ui->grantComboBox->setCurrentIndex(1);
            break;
        case 2:
            ui->grantComboBox->setCurrentIndex(2);
            break;
    }

}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::accept()
{
    //Если обнаруженно несовпадение значений - вызываем метод замены, закрываем с accept
    if (ui->lineSurname->text().isEmpty()|| ui->lineName->text().isEmpty() || ui->lineNumber->text().isEmpty())
        QMessageBox::warning(this, "Ошибка", "Заполнены не все поля.");
    else if (mStudent.mSurname != ui->lineSurname->text() ||
             mStudent.mName != ui->lineName->text() ||
             mStudent.mPatronymic != ui->linePatronymic->text() ||
             mStudent.mID != ui->lineNumber->text().toInt())
    {
        mStudent.mSurname = ui->lineSurname->text();
        mStudent.mName = ui->lineName->text();
        mStudent.mPatronymic = ui->linePatronymic->text();
        mStudent.mID = ui->lineNumber->text().toInt();
        QDialog::accept();
    }
    else QDialog::close();
}

