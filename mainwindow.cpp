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

MainWindow::MainWindow(DataBases &sDB, QWidget *parent)  : db(sDB),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setMovable(false);
    ui->toolBar->orientationChanged(Qt::Vertical);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMode(int sMode)
{
    if (sMode == 0)
    {
        mMode = sMode;
        this->setWindowTitle("Сеанс студента");
        ui->comboBox->addItems(Config::studentComboBoxItems);
    }
    else if (sMode == 1)
    {
        mMode = sMode;
        this->setWindowTitle("Сеанс диспетчера");
        ui->comboBox->addItems(Config::supervisorComboBoxItems);
    }
    else if (sMode == 2)
    {
        mMode = sMode;
        this->setWindowTitle("Сеанс администратора");
        ui->comboBox->addItems(Config::adminComboBoxItems);
    }
}

void MainWindow::setData()
{
    if (ui->comboBox->currentText() == "Пользователи")
    {
        model = new QStandardItemModel(db.usersList.length(), 3, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Логин")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Пароль")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Роль")));

        for(int i = 0; i < db.usersList.length() ; i++)
        {
            model->setItem(i,0,new QStandardItem(QString(db.usersList[i].getLogin())));
            model->setItem(i,1,new QStandardItem(QString(db.usersList[i].getPassword())));
            model->setItem(i,2,new QStandardItem(QString(Config::roles[db.usersList[i].getRole()])));
        }
        ui->tableView->setModel(model);
    }
    else if (ui->comboBox->currentText() == "Группы")
    {
        model = new QStandardItemModel(db.groupsList.length(), 2, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Кол-во студентов")));

        for(int i = 0; i < db.groupsList.length() ; i++)
        {
            model->setItem(i,0,new QStandardItem(QString(db.groupsList[i].mNumber)));
            model->setItem(i,1,new QStandardItem(QString::number(db.groupsList[i].mStudents.length())));
        }
        ui->tableView->setModel(model);
    }
    else if (ui->comboBox->currentText() == "Студенты")
    {
        students.clear();
        for (User& i : db.usersList)
        {
            if (i.getRole() == 0) students.push_back(&i);
        }

        model = new QStandardItemModel(students.length(), 5, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Фамилия")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Имя")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Отчество")));
        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Группа")));
        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Студенческий билет")));

        for(int i = 0; i<students.length(); i++)
        {
            model->setItem(i,0,new QStandardItem(QString(students[i]->mSurname)));
            model->setItem(i,1,new QStandardItem(QString(students[i]->mName)));
            model->setItem(i,2,new QStandardItem(QString(students[i]->mPatronymic)));
            model->setItem(i,3,new QStandardItem(db.findGroup(students[i]->mGroupID)->mNumber));
            model->setItem(i,4,new QStandardItem(QString::number(students[i]->mID)));
        }
        ui->tableView->setModel(model);
    }
    else if (ui->comboBox->currentText() == "Дисциплины")
    {
        model = new QStandardItemModel(db.disciplinesList.length(), 2, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Наименование")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Форма контроля")));

        for(int i = 0; i < db.disciplinesList.length() ; i++)
        {
            model->setItem(i,0,new QStandardItem(QString(db.disciplinesList[i].mName)));
            model->setItem(i,1,new QStandardItem(Config::disciplineFormOfControl[db.disciplinesList[i].mForm]));
        }
        ui->tableView->setModel(model);
    }
}

void MainWindow::lineFindReturn()
{
    qDebug() << "[MainWindow::lineFindReturn]";
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (ui->comboBox->currentText() == "Студенты")
    {
        ui->addNoteThis->setDisabled(true);
        ui->removeNoteThis->setDisabled(true);
    }
    else if (ui->comboBox->currentText() == "Оценки" || ui->comboBox->currentText() == "Стипендия")
    {
        ui->addNoteThis->setVisible(false);
        ui->removeNoteThis->setVisible(false);
    }
    else
    {
        ui->addNoteThis->setDisabled(false);
        ui->removeNoteThis->setDisabled(false);
    }
    setData();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    if (ui->comboBox->currentText() == "Пользователи")
    {
        //Создаем указатель на соответствующего пользователя - передаем в конструктор окна EditUserDialog
        User* user = &db.usersList[index.row()];
        EditUserDialog eud(*user, this);
        eud.setWindowTitle("Редактирование пользователя");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных пользователей, обновляем модель таблицы
        if (eud.exec() == QDialog::Accepted)
        {
            db.overwriteUsers();
            setData();
        }
    }
    else if (ui->comboBox->currentText() == "Студенты")
    {
        //Создаем указатель на соответствующего пользователя - передаем в конструктор окна EditUserDialog
        User* student = students[index.row()];
        EditStudentDialog esd(*student, db.groupsList, db, this);
        esd.setWindowTitle("Редактирование студента");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных пользователей, обновляем модель таблицы
        if (esd.exec() == QDialog::Accepted)
        {
            qDebug() << "[on_tableView_activated]" << student->mSurname << student->mID << student->mGrant;
            db.reloadGroups();
            db.overwriteUsers();
            setData();
        }
    }
    else if (ui->comboBox->currentText() == "Дисциплины")
    {
        //Создаем указатель на соответствующую дисциплину - передаем в конструктор окна EditUserDialog

        Discipline* discipline = &db.disciplinesList[index.row()];
        EditDisciplineDialog edd(*discipline, db.groupsList, this);
        edd.setWindowTitle("Редактирование дисциплины");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных
        if (edd.exec() == QDialog::Accepted)
        {
            db.overwriteDisciplines();
            db.reloadGroups();
            setData();
        }
        qDebug() << "[MainWindow::on_tableView_activated]";
    }
    else if (ui->comboBox->currentText() == "Группы")
    {
        Group* group = &db.groupsList[index.row()];
        EditGroupDialog egd(*group, this);
        egd.setWindowTitle("Редактирование группы");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных
        if (egd.exec() == QDialog::Accepted)
        {
            db.overwriteGroups();
            setData();
        }
    }
}

void MainWindow::addNoteThis()
{
    if (ui->comboBox->currentText() == "Пользователи")
    {
        User* user = new User("", "", -1);
        EditUserDialog eud(*user, this);
        eud.setWindowTitle("Создание пользователя");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных пользователей, обновляем модель таблицы
        if (eud.exec() == QDialog::Accepted)
        {
            db.usersList.push_back(*user);
            db.overwriteUsers();
            db.reloadGroups();
            setData();
        }
    }
    else if (ui->comboBox->currentText() == "Дисциплины")
    {
        Discipline* discipline = new Discipline("", db.getNextDisciplineID(), 0, {});
        EditDisciplineDialog edd(*discipline, db.groupsList, this);
        edd.setWindowTitle("Создание дисциплины");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных пользователей, обновляем модель таблицы
        if (edd.exec() == QDialog::Accepted)
        {
            db.disciplinesList.push_back(*discipline);
            db.incrementNextDisciplineID();
            db.overwriteDisciplines();
            db.reloadGroups();
            setData();
        }
    }
    else if (ui->comboBox->currentText() == "Группы")
    {
        Group* group = new Group(db.getNextGroupID(), "", {}, {});
        EditGroupDialog egd(*group, this);
        egd.setWindowTitle("Создание группы");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных пользователей, обновляем модель таблицы
        if (egd.exec() == QDialog::Accepted)
        {
            db.groupsList.push_back(*group);
            db.incrementNextDisciplineID();
            db.overwriteGroups();
            setData();
        }
    }
}

void MainWindow::removeNoteThis()
{
    if (ui->comboBox->currentText() == "Пользователи")
    {
        QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();
        if (idc.length() == 0) QMessageBox::warning(this, "Примечание", "Сперва выберете элементы таблицы.");
        else if (QMessageBox::question(this, QString("Подтверждение удаления"),QString("Вы уверены, что хотите удалить заметку?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            db.usersList.removeAt(idc[0].row());
            db.overwriteUsers();
            setData();
        }
    }
    else if (ui->comboBox->currentText() == "Дисциплины")
    {
        QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();
        if (idc.length() == 0) QMessageBox::warning(this, "Примечание", "Сперва выберете элементы таблицы.");
        else if (QMessageBox::question(this, QString("Подтверждение удаления"),QString("Вы уверены, что хотите удалить заметку?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            //Из записей пользователей удалим записи об этой дисциплине
            for (User& i : db.usersList)
            {
                for (int j; j<i.mGrades.length(); j++)
                {
                    if (i.mGrades[j] == db.disciplinesList[idc[0].row()].mDisciplineID && j%2 == 0)
                    {
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
        }
    }
    else if (ui->comboBox->currentText() == "Группы")
    {
        QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();
        if (idc.length() == 0) QMessageBox::warning(this, "Примечание", "Сперва выберете элементы таблицы.");
        else if (QMessageBox::question(this, QString("Подтверждение удаления"),QString("Вы уверены, что хотите удалить заметку?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            db.groupsList.removeAt(idc[0].row());
            db.overwriteGroups();
            db.coinsideGroups();
            setData();
        }
    }

}
