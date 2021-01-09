#include "editstudentdialog.h"
#include "databases.h"
#include "config.h"
#include "ui_editstudentdialog.h"

#include <QMessageBox>

editStudentDialog::editStudentDialog(User &sStuden, QList<Group> sGroups, DataBases &sDB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editStudentDialog),
    mStudent(sStuden),
    mDB(sDB),
    mGroups(sGroups)
{
    ui->setupUi(this);
    //Установка максимальной длины для ФИО, номера СБ.
    ui->lineSurname->setMaxLength(20);
    ui->lineName->setMaxLength(20);
    ui->linePatronymic->setMaxLength(20);
    ui->lineNumber->setMaxLength(10);
    //Установка текущих значений.
    ui->lineSurname->setText(mStudent.mSurname);
    ui->lineName->setText(mStudent.mName);
    ui->linePatronymic->setText(mStudent.mPatronymic);
    ui->lineNumber->setText(QString::number(mStudent.mID));
    //Установка допустимого диапазона.
    QValidator *validator = new QIntValidator(1, 999999999, this);
    ui->lineNumber->setValidator(validator);
    //Установка в QLabel текущeго логина студента.
    ui->labelLogin->setText(mStudent.getLogin());
    //Добавление в QComboBox существующих в ИС(имеющихся в БД) групп.
    for (Group &i : mGroups) {
        GroupsNumbers.append(i.mNumber);
        ui->groupComboBox->addItem(i.mNumber);
        if (i.mGroupID == mStudent.mGroupID) {
            ui->groupComboBox->setCurrentText(i.mNumber);
        }
    }
    //Установка текущей стипендии.
    ui->grantComboBox->setCurrentIndex(getGrantIndex());

    mGroup = mDB.findGroup(mStudent.mGroupID);

    setData();
}

editStudentDialog::~editStudentDialog()
{
    delete ui;
}

int editStudentDialog::findGrade(int fDisciplineID)
{
    for (int i = 0; i <mStudent.mGrades.length(); i+=2) {
        if (fDisciplineID == mStudent.mGrades[i]) {
            return(mStudent.mGrades[i+1]);
        }
    }
    return(-1);
}

void editStudentDialog::setData()
{
    model = new QStandardItemModel(mGroup->mDisciplines.length(), 3, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Наименование дисциплины")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Форма контроля")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Оценка")));

    for(int i = 0; i<mGroup->mDisciplines.length(); i++) {
        model->setItem(i,0,new QStandardItem(QString(mGroup->mDisciplines[i]->mName)));
        model->setItem(i,1,new QStandardItem(QString(Config::disciplineFormOfControl[mGroup->mDisciplines[i]->mForm])));

        int grade = findGrade(mGroup->mDisciplines[i]->mDisciplineID);
        if (grade != -1) {
            if (mGroup->mDisciplines[i]->mForm == 0) {
                if (grade == 0) {
                    model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[0])));
                } else {
                    if (grade > 0) {
                        model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[1])));
                    }
                }
            } else {
                if (mGroup->mDisciplines[i]->mForm == 1) {
                    model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[grade])));
                }
            }
        } else {
            model->setItem(i,2,new QStandardItem(QString("Нет")));
        }
    }
    ui->tableView->setModel(model);
}


void editStudentDialog::setGrade()
{

}

int editStudentDialog::getGrantIndex()
{
    if (mStudent.mGrant == User::grants::HIGHT) {
        return(2);
    }
    if (mStudent.mGrant == User::grants::REGULAR) {
        return(1);
    }
    return(0);
}

User::grants editStudentDialog::getGrantByIndex(int index)
{
    if (index == 2) {
        return(User::grants::HIGHT);
    }
    if (index == 1) {
        return(User::grants::REGULAR);
    }
    return(User::grants::NONE);
}

void editStudentDialog::accept()
{
    //Если обнаруженно несовпадение значений - вызываем метод замены, закрываем с accept
    if (ui->lineSurname->text().isEmpty()|| ui->lineName->text().isEmpty() || ui->lineNumber->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполнены не все поля.");
    } else {
        bool ind = false;
        if (mStudent.mSurname != ui->lineSurname->text()) {
            mStudent.mSurname = ui->lineSurname->text();
            ind = true;
        }
        if (mStudent.mName != ui->lineName->text()) {
            mStudent.mName = ui->lineName->text();
            ind = true;
        }
        if (mStudent.mPatronymic != ui->linePatronymic->text()) {
            mStudent.mPatronymic = ui->linePatronymic->text();
            ind = true;
        }
        if (mStudent.mID != ui->lineNumber->text().toInt()) {
            mStudent.mID = ui->lineNumber->text().toInt();
            ind = true;\

        }
        if (getGrantIndex() != ui->grantComboBox->currentIndex()) {
            mStudent.mGrant = getGrantByIndex(ui->grantComboBox->currentIndex());
            ind = true;
        }
        if (ui->groupComboBox->currentIndex() != -1) {
            if (mStudent.mGroupID != mDB.findGroupName(ui->groupComboBox->currentText())->mGroupID) {
                mStudent.mGroupID = mDB.findGroupName(ui->groupComboBox->currentText())->mGroupID;
                ind = true;
            }
        }
        //Если были изменеия - завершаем с accept
        if (ind) {
            QDialog::accept();
        }
        QDialog::close();
    }
}


