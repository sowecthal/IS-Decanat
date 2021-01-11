#include "editstudentdialog.h"
#include "config.h"
#include "ui_editstudentdialog.h"

#include <QMessageBox>
#include <QDebug>

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

Grade::grades editStudentDialog::findGrade(int fDisciplineID)
{
    return(mDB.findGrade(mStudent.mID, fDisciplineID));
}

void editStudentDialog::setData()
{
    model = new QStandardItemModel(mGroup->mDisciplines.length(), 3, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Наименование дисциплины")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Форма контроля")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Оценка")));

    for(int i = 0; i<mGroup->mDisciplines.length(); i++) {
        model->setItem(i,0,new QStandardItem(QString(mGroup->mDisciplines[i]->mName)));

        if (mGroup->mDisciplines[i]->mForm == Discipline::forms::PASS) {
            model->setItem(i,1,new QStandardItem(QString(Config::disciplineFormOfControl[0])));
        } else {
            if (mGroup->mDisciplines[i]->mForm == Discipline::forms::EXAM) {
                model->setItem(i,1,new QStandardItem(QString(Config::disciplineFormOfControl[1])));
            }
        }

        Grade::grades grade = findGrade(mGroup->mDisciplines[i]->mDisciplineID);
        if (grade != Grade::NONE) {
            if (grade == Grade::NOPASSED) {
                model->setItem(i,2,new QStandardItem(QString(Config::gradesPass[1])));
            } else {
                if (grade == Grade::PASSED) {
                    model->setItem(i,2,new QStandardItem(QString(Config::gradesPass[2])));
                } else {
                    if (grade == Grade::BAD) {
                       model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[1])));
                    } else {
                        if (grade == Grade::OKAY) {
                            model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[2])));
                        } else {
                            if (grade == Grade::GOOD) {
                                model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[3])));
                            } else {
                                if (grade == Grade::EXCELLENT) {
                                    model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[4])));
                                }
                            }
                        }
                    }
                }
            }
        } else {
            model->setItem(i,2,new QStandardItem(QString("Нет")));
        }
    }
    ui->tableView->setModel(model);
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
        if (mStudent.mID != ui->lineNumber->text().toInt() || mStudent.mID == 0) {
            if (mDB.findStudent(ui->lineNumber->text().toInt()) != nullptr) {
                QMessageBox::warning(this, "Ошибка", "Данный номер студенческого билета уже используется.");
                return;
            } else {
                mStudent.mID = ui->lineNumber->text().toInt();
                ind = true;
            }
        }
        if (getGrantIndex() != ui->grantComboBox->currentIndex()) {
            mStudent.mGrant = getGrantByIndex(ui->grantComboBox->currentIndex());
            ind = true;
        }
        if (ui->groupComboBox->currentIndex() != -1) {
            if (mDB.findGroupName(ui->groupComboBox->currentText()) != nullptr) {
                if (mStudent.mGroupID != mDB.findGroupName(ui->groupComboBox->currentText())->mGroupID) {
                    mStudent.mGroupID = mDB.findGroupName(ui->groupComboBox->currentText())->mGroupID;
                    ind = true;
                }
            }
        }
        //Если были изменеия - завершаем с accept
        if (ind) {
            QDialog::accept();
        }
        QDialog::close();
    }
}

void editStudentDialog::setGradeThis()
{
    QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();
    if (idc.length() == 0) {
        QMessageBox::warning(this, "Примечание", "Сперва выберете элементы таблицы.");
    } else {
        /* Если попытка установить отсутствие оценки - удаляем её.
         * p.s. Определение её наличия в БД встроенно в метод удаления.
         */
        if (ui->gradesComboBox->currentText() == Config::gradesExam[0]) {
            ind = true;
            mDB.deleteGrade(mStudent.mID, mGroup->mDisciplines[idc[0].row()]->mDisciplineID);
        } else {
            Grade::grades tmpGrade = findGrade(mGroup->mDisciplines[idc[0].row()]->mDisciplineID);
            //Если оценка существует - заменяем, иначе - создаем
            if  (tmpGrade != Grade::NONE) {
                //Проверка на "неуд.".
                if (ui->gradesComboBox->currentText() == Config::gradesExam[1] && tmpGrade != Grade::BAD) {
                     ind = true;
                     mDB.resetGrade(mStudent.mID,
                                       mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::BAD);
                } else {
                    if (ui->gradesComboBox->currentText() == Config::gradesExam[2] && tmpGrade != Grade::OKAY) {
                        ind = true;
                        mDB.resetGrade(mStudent.mID,
                                          mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::OKAY);
                    } else {
                        if (ui->gradesComboBox->currentText() == Config::gradesExam[3] && tmpGrade != Grade::GOOD) {
                            ind = true;
                            mDB.resetGrade(mStudent.mID,
                                              mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::GOOD);
                        } else {
                            if (ui->gradesComboBox->currentText() == Config::gradesExam[4] && tmpGrade != Grade::EXCELLENT) {
                                ind = true;
                                mDB.resetGrade(mStudent.mID,
                                                  mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::EXCELLENT);
                            } else {
                                if (ui->gradesComboBox->currentText() == Config::gradesPass[1] && tmpGrade != Grade::NOPASSED) {
                                    ind = true;
                                    mDB.resetGrade(mStudent.mID,
                                                      mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::NOPASSED);
                                } else {
                                    if (ui->gradesComboBox->currentText() == Config::gradesPass[2] && tmpGrade != Grade::PASSED) {
                                        ind = true;
                                        mDB.resetGrade(mStudent.mID,
                                                          mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::PASSED);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                ind = true;
                if (ui->gradesComboBox->currentText() == Config::gradesExam[1]) {
                    mDB.createGrade(mStudent.mID,
                                    mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::BAD);;
                } else {
                    if (ui->gradesComboBox->currentText() == Config::gradesExam[2]) {
                        mDB.createGrade(mStudent.mID,
                                          mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::OKAY);
                    } else {
                        if (ui->gradesComboBox->currentText() == Config::gradesExam[3]) {
                            mDB.createGrade(mStudent.mID,
                                              mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::GOOD);
                        } else {
                            if (ui->gradesComboBox->currentText() == Config::gradesExam[4]) {
                                mDB.createGrade(mStudent.mID,
                                                  mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::EXCELLENT);
                            } else {
                                if (ui->gradesComboBox->currentText() == Config::gradesPass[1]) {
                                    mDB.createGrade(mStudent.mID,
                                                      mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::NOPASSED);
                                } else {
                                    if (ui->gradesComboBox->currentText() == Config::gradesPass[2]) {
                                        mDB.createGrade(mStudent.mID,
                                                          mGroup->mDisciplines[idc[0].row()]->mDisciplineID, Grade::PASSED);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    setData();
}

void editStudentDialog::on_tableView_clicked(const QModelIndex &index)
{
    if (mGroup->mDisciplines[index.row()]->mForm == Discipline::EXAM) {
        ui->gradesComboBox->clear();
        ui->gradesComboBox->addItems(Config::gradesExam);
    } else {
        if (mGroup->mDisciplines[index.row()]->mForm == Discipline::PASS) {
            ui->gradesComboBox->clear();
            ui->gradesComboBox->addItems(Config::gradesPass);
        }
    }
}
