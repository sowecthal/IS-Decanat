#include "editstudentdialog.h"
#include "databases.h"
#include "ui_editstudentdialog.h"

#include <QMessageBox>
#include <QDebug>

EditStudentDialog::EditStudentDialog(User &sStuden, QList<Group> sGroups, DataBases &sDB, QWidget *parent) :
    mStudent(sStuden),
    mDB(sDB),
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
    else
    {
        bool ind = false;
        if (mStudent.mSurname != ui->lineSurname->text()){ mStudent.mSurname = ui->lineSurname->text(); ind = true;}
        if (mStudent.mName != ui->lineName->text()){ mStudent.mName = ui->lineName->text(); ind = true;}
        if (mStudent.mPatronymic != ui->linePatronymic->text()){ mStudent.mPatronymic = ui->linePatronymic->text(); ind = true;}
        if (mStudent.mID != ui->lineNumber->text().toInt()){ mStudent.mID = ui->lineNumber->text().toInt(); ind = true;}
        if (mStudent.mGrant != ui->grantComboBox->currentIndex()){ mStudent.mGrant = ui->grantComboBox->currentIndex(); ind = true;}
        if (ui->groupComboBox->currentIndex() != -1)
            if (mStudent.mGroupID != mDB.findGroupName(ui->groupComboBox->currentText())->mGroupID){ mStudent.mGroupID = mDB.findGroupName(ui->groupComboBox->currentText())->mGroupID; ind = true;}
        //Если были изменеия - завершаем с accept
        if (ind) QDialog::accept();
        QDialog::close();
    }
}

