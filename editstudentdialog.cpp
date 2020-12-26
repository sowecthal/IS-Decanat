#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

EditStudentDialog::EditStudentDialog(User &sStuden, QWidget *parent) : mStuden(sStuden),
    QDialog(parent),
    ui(new Ui::editStudentDialog)
{
    ui->setupUi(this);
    ui->lineSurname->setMaxLength(20);
    ui->lineName->setMaxLength(20);
    ui->linePatronymic->setMaxLength(20);
    ui->lineNumber->setMaxLength(10);
    ui->lineSurname->setText(mStuden.mSurname);
    ui->lineName->setText(mStuden.mName);
    ui->linePatronymic->setText(mStuden.mPatronymic);
    ui->lineNumber->setText(QString(mStuden.mID));

    switch (mStuden.mGrant)
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
