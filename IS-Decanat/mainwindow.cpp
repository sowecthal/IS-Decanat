#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "edituserdialog.h"
#include "editstudentdialog.h"
#include "editdisciplinedialog.h"
#include "editgroupdialog.h"

#include "dataclasses/user.h"
#include "dataclasses/discipline.h"
#include "dataclasses/group.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>

MainWindow::MainWindow(DataBases &sDB, QWidget *parent)  :
    QMainWindow(parent),
    db(sDB),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setMovable(false);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUser(User* sUser)
{
    mUser = sUser;
    if (mUser->getRole() == User::roles::STUDENT) {
        mMode = 0;
        this->setWindowTitle("Сеанс студента");
        ui->comboBox->addItems(Config::studentComboBoxItems);
    } else {
        if (mUser->getRole() == User::roles::SUPERVISOR){
            mMode = 1;
            this->setWindowTitle("Сеанс диспетчера");
            ui->comboBox->addItems(Config::supervisorComboBoxItems);
         } else {
            if (mUser->getRole() == User::roles::ADMIN) {
                mMode = 2;
                this->setWindowTitle("Сеанс администратора");
                ui->comboBox->addItems(Config::adminComboBoxItems);
            }
        }
    }
}

int MainWindow::findGrade(int fDisciplineID)
{
    for (int i= 0; i < mUser->mGrades.length(); i += 2) {
        if (fDisciplineID == mUser->mGrades[i]) {
            return(mUser->mGrades[i+1]);
        }
    }
    return(-1);
}

void MainWindow::setData()
{
    if (ui->comboBox->currentText() == "Пользователи") {
        model = new QStandardItemModel(db.usersList.length(), 3, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Логин")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Пароль")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Роль")));

        for(int i = 0; i < db.usersList.length() ; i++) {
            model->setItem(i,0,new QStandardItem(QString(db.usersList[i].getLogin())));
            model->setItem(i,1,new QStandardItem(QString(db.usersList[i].getPassword())));
            if (db.usersList[i].getRole() == User::roles::STUDENT) {
                model->setItem(i,2,new QStandardItem(QString("Студент")));
            } else {
                if (db.usersList[i].getRole() == User::roles::SUPERVISOR) {
                    model->setItem(i,2,new QStandardItem(QString("Диспетчер деканата")));
                } else {
                    if (db.usersList[i].getRole() == User::roles::ADMIN) {
                        model->setItem(i,2,new QStandardItem(QString("Администратор")));
                    }
                }
            }
        }
        ui->tableView->setModel(model);
    } else {
        if (ui->comboBox->currentText() == "Группы") {
            model = new QStandardItemModel(db.groupsList.length(), 2, this);
            model->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));
            model->setHorizontalHeaderItem(1, new QStandardItem(QString("Кол-во студентов")));

            for(int i = 0; i < db.groupsList.length() ; i++) {
                model->setItem(i,0,new QStandardItem(QString(db.groupsList[i].mNumber)));
                model->setItem(i,1,new QStandardItem(QString::number(db.groupsList[i].mStudents.length())));
            }
            ui->tableView->setModel(model);
        } else {
            if (ui->comboBox->currentText() == "Студенты")
            {
                students.clear();
                for (User &i : db.usersList) {
                    if (i.getRole() == User::roles::STUDENT) students.push_back(&i);
                }

                model = new QStandardItemModel(students.length(), 5, this);
                model->setHorizontalHeaderItem(0, new QStandardItem(QString("Фамилия")));
                model->setHorizontalHeaderItem(1, new QStandardItem(QString("Имя")));
                model->setHorizontalHeaderItem(2, new QStandardItem(QString("Отчество")));
                model->setHorizontalHeaderItem(3, new QStandardItem(QString("Группа")));
                model->setHorizontalHeaderItem(4, new QStandardItem(QString("Студенческий билет")));

                for(int i = 0; i<students.length(); i++) {
                    model->setItem(i,0,new QStandardItem(QString(students[i]->mSurname)));
                    model->setItem(i,1,new QStandardItem(QString(students[i]->mName)));
                    model->setItem(i,2,new QStandardItem(QString(students[i]->mPatronymic)));
                    model->setItem(i,3,new QStandardItem(db.findGroup(students[i]->mGroupID)->mNumber));
                    model->setItem(i,4,new QStandardItem(QString::number(students[i]->mID)));
                }
                ui->tableView->setModel(model);
            } else {
                if (ui->comboBox->currentText() == "Дисциплины") {
                    model = new QStandardItemModel(db.disciplinesList.length(), 2, this);
                    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Наименование")));
                    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Форма контроля")));

                    for(int i = 0; i < db.disciplinesList.length() ; i++)
                    {
                        model->setItem(i,0,new QStandardItem(QString(db.disciplinesList[i].mName)));
                        model->setItem(i,1,new QStandardItem(Config::disciplineFormOfControl[db.disciplinesList[i].mForm]));
                    }
                    ui->tableView->setModel(model);
                } else {
                    if (ui->comboBox->currentText() == "Оценки") {
                        model = new QStandardItemModel(db.findGroup(mUser->mGroupID)->mDisciplines.length(), 3, this);
                        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Наименование дисциплины")));
                        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Форма контроля")));
                        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Оценка")));

                        Group* nowGroup = db.findGroup(mUser->mGroupID);
                        for(int i = 0; i<nowGroup->mDisciplines.length(); i++) {
                            model->setItem(i,0,new QStandardItem(QString(nowGroup->mDisciplines[i]->mName)));
                            model->setItem(i,1,new QStandardItem(QString(Config::disciplineFormOfControl[nowGroup->mDisciplines[i]->mForm])));

                            int grade = findGrade(nowGroup->mDisciplines[i]->mDisciplineID);
                            if (grade != -1) {
                                if (nowGroup->mDisciplines[i]->mForm == 0) {
                                    if (grade == 0) {
                                        model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[0])));
                                    } else {
                                        if (grade > 0) {
                                            model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[1])));
                                        } else {
                                            if (nowGroup->mDisciplines[i]->mForm == 1) {
                                                model->setItem(i,2,new QStandardItem(QString(Config::gradesExam[grade])));
                                            } else {
                                                model->setItem(i,2,new QStandardItem(QString("Нет")));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        ui->tableView->setModel(model);
                    } else {
                        if (ui->comboBox->currentText() == "Стипендия") {
                            model = new QStandardItemModel(1, 1, this);
                            model->setHorizontalHeaderItem(0, new QStandardItem(QString("Статус")));

                            if (mUser->mGrant == User::grants::HIGHT) {
                                model->setItem(0,0,new QStandardItem(QString(Config::grant[2])));
                            } else {
                                if (mUser->mGrant == User::grants::REGULAR) {
                                    model->setItem(0,0,new QStandardItem(QString(Config::grant[1])));
                                } else {
                                    model->setItem(0,0,new QStandardItem(QString(Config::grant[0])));
                                }
                            }
                            ui->tableView->setModel(model);
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    //Если выбрано - "Студенты" - ограничить использование кнопок "+" и "-", иначе:
    if (arg1 == "Студенты") {
        ui->addNoteThis->setDisabled(true);
        ui->removeNoteThis->setDisabled(true);
    } else {
        //Если выбрано - "Оценки" или "Стипендия" - вовсе убрать тулбар, иначе - снять все ограничения.
        if (arg1 == "Оценки" || arg1 == "Стипендия") {
            ui->addNoteThis->setVisible(false);
            ui->removeNoteThis->setVisible(false);
        } else {
            ui->addNoteThis->setDisabled(false);
            ui->removeNoteThis->setDisabled(false);
        }
    }

    setData();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    if (ui->comboBox->currentText() == "Пользователи") {
        //Взятие указателя на соответствующего пользователя, передача в конструктор окна EditUserDialog.
        User* user = &db.usersList[index.row()];
        EditUserDialog eud(*user, this);
        eud.setWindowTitle("Редактирование пользователя");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписать файл пользователей, обновить модель таблицы.
        if (eud.exec() == QDialog::Accepted) {
            db.overwriteUsers();
            setData();
        }

        //Дальше по аналогии:
    } else {
        if (ui->comboBox->currentText() == "Студенты") {
            ///Я случайно написала с маленькой "е" ;(
            User* student = students[index.row()];
            editStudentDialog esd(*student, db.groupsList, db, this);
            esd.setWindowTitle("Редактирование студента");

            if (esd.exec() == QDialog::Accepted) {
                db.reloadGroups();
                db.overwriteUsers();
                setData();
            }
        } else {
            if (ui->comboBox->currentText() == "Дисциплины") {
                Discipline* discipline = &db.disciplinesList[index.row()];
                EditDisciplineDialog edd(*discipline, db, this);
                edd.setWindowTitle("Редактирование дисциплины");

                if (edd.exec() == QDialog::Accepted) {
                    db.overwriteDisciplines();
                    db.reloadGroups();
                    setData();
                }
            } else {
                if (ui->comboBox->currentText() == "Группы") {
                    Group* group = &db.groupsList[index.row()];
                    EditGroupDialog egd(*group, this);
                    egd.setWindowTitle("Редактирование группы");

                    if (egd.exec() == QDialog::Accepted)
                    {
                        db.overwriteGroups();
                        setData();
                    }
                }
            }
        }
    }
}

void MainWindow::addNoteThis()
{
    if (ui->comboBox->currentText() == "Пользователи") {
        //Создание пустого объекта.
        User* user = new User("", "", User::roles::UNKNOWN);
        EditUserDialog eud(*user, this);
        eud.setWindowTitle("Создание пользователя");

        //Если диалог закрыт с accept(были внесены изменения) - добавить объект в нужный список, переписать двоичный файл
        if (eud.exec() == QDialog::Accepted) {
            db.usersList.push_back(*user);
            db.overwriteUsers();
            db.reloadGroups();
            setData();
        }
        delete user;

        //Дальше по аналогии:
    } else {
        if (ui->comboBox->currentText() == "Дисциплины") {
            Discipline* discipline = new Discipline("", db.getNextDisciplineID(), 0, {});
            EditDisciplineDialog edd(*discipline, db, this);
            edd.setWindowTitle("Создание дисциплины");

            if (edd.exec() == QDialog::Accepted) {
                db.disciplinesList.push_back(*discipline);
                db.incrementNextDisciplineID();
                db.overwriteDisciplines();
                db.reloadGroups();
                setData();
            }
            delete discipline;
        } else {
            if (ui->comboBox->currentText() == "Группы") {
                Group* group = new Group(db.getNextGroupID(), "", {}, {});
                EditGroupDialog egd(*group, this);
                egd.setWindowTitle("Создание группы");

                if (egd.exec() == QDialog::Accepted) {
                    db.groupsList.push_back(*group);
                    db.incrementNextDisciplineID();
                    db.overwriteGroups();
                    setData();
                }
                delete group;
            }
        }
    }
}

void MainWindow::removeNoteThis()
{
    QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();
    if (idc.length() == 0) {
        QMessageBox::warning(this, "Примечание", "Сперва выберете элементы таблицы.");
    } else {
        if (QMessageBox::question(this, QString("Подтверждение удаления"),QString("Вы уверены, что хотите удалить заметку?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            if (ui->comboBox->currentText() == "Пользователи") {
                    db.usersList.removeAt(idc[0].row());
                    db.overwriteUsers();
                    setData();
            } else {
                if (ui->comboBox->currentText() == "Дисциплины") {
                    for (User& i : db.usersList) {
                        for (int j = 0; j<i.mGrades.length(); j++) {
                            if (i.mGrades[j] == db.disciplinesList[idc[0].row()].mDisciplineID && j%2 == 0) {
                                i.mGrades.removeAt(j);
                                i.mGrades.removeAt(j+1);
                                db.overwriteUsers();
                                break;
                            }
                        }
                    }

                    db.disciplinesList.removeAt(idc[0].row());
                    db.overwriteDisciplines();
                    db.reloadGroups();
                    setData();
                } else {
                    if (ui->comboBox->currentText() == "Группы") {
                        db.groupsList.removeAt(idc[0].row());
                        db.overwriteGroups();
                        db.coinsideGroups();
                        setData();
                    }
                }
            }
        }
    }
}
