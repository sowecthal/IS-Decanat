#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include <QMessageBox>
#include <QDebug>

EditStudentDialog::EditStudentDialog(User &sStuden, QList<Group> sGroups, QWidget *parent) :
    mStudent(sStuden),
    mGroups(sGroups),
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

    int index = 0;
    for (Group i : mGroups)
    {
        GroupsNumbers.append(i.mNumber);
        ui->groupComboBox->addItem(i.mNumber);
        if (i.mGroupID == mStudent.mGroupID) ui->groupComboBox->setCurrentText(i.mNumber);
    }

    ui->grantComboBox->setCurrentIndex(mStudent.mGrant);
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
             mStudent.mID != ui->lineNumber->text().toInt() ||
             mStudent.mGrant != ui->grantComboBox->currentIndex() ||
             mStudent.mGroupID != mGroups[ui->groupComboBox->currentIndex()].mGroupID)
    {
        mStudent.mSurname = ui->lineSurname->text();
        mStudent.mName = ui->lineName->text();
        mStudent.mPatronymic = ui->linePatronymic->text();
        mStudent.mID = ui->lineNumber->text().toInt();
        mStudent.mGrant = ui->grantComboBox->currentIndex();
        mStudent.mGroupID = mGroups[ui->groupComboBox->currentIndex()].mGroupID;

        QDialog::accept();
    }
    else QDialog::close();
}

