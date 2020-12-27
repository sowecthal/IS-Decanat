#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "edituserdialog.h"
#include "editstudentdialog.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>

MainWindow::MainWindow(DataBases &sDB, QWidget *parent)  : db(sDB),
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setMovable(false);
    ui->toolBar->orientationChanged(Qt::Vertical);
    ui->lineFind->setPlaceholderText("Поиск по таблице");
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
            model->setItem(i,0,new QStandardItem(QString(db.groupsList[i].getLogin())));
            model->setItem(i,1,new QStandardItem(QString(db.groupsList[i].getPassword())));
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
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Студенческий билет")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Фамилия")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Имя")));
        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Отчество")));
        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Группа")));
        model->setHorizontalHeaderItem(5, new QStandardItem(QString("Стипендия")));

        for(int i = 0; i<students.length(); i++)
        {
            model->setItem(i,0,new QStandardItem(QString(students[i]->mID)));
            model->setItem(i,1,new QStandardItem(QString(students[i]->mSurname)));
            model->setItem(i,2,new QStandardItem(QString(students[i]->mName)));
            model->setItem(i,3,new QStandardItem(QString(students[i]->mPatronymic)));
            model->setItem(i,4,new QStandardItem(QString(students[i]->mGroupID)));
            model->setItem(i,5,new QStandardItem(QString(students[i]->mGrant)));
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
        ui->addNoteThis->setCheckable(true);
        ui->removeNoteThis->setCheckable(true);
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
        qDebug() << "[MainWindow::on_tableView_activated]";
    }
    else if (ui->comboBox->currentText() == "Студенты")
    {
        //Создаем указатель на соответствующего пользователя - передаем в конструктор окна EditUserDialog
        User* student = students[index.row()];
        EditStudentDialog esd(*student, this);
        esd.setWindowTitle("Редактирование студента");

        //Если диалог закрыт с accept(были внесены изменения) - перезаписываем базу данных пользователей, обновляем модель таблицы
        if (esd.exec() == QDialog::Accepted)
        {
            db.overwriteUsers();
            setData();
        }
        qDebug() << "[MainWindow::on_tableView_activated]";
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
            setData();
        }
    }
    qDebug() << "[MainWindow::on_tableView_activated]";
}

void MainWindow::removeNoteThis()
{
    if (ui->comboBox->currentText() == "Пользователи")
    {
        QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();
        //User dUser = db.usersList.value(idc[0].row());
        if (idc.length() == 0) QMessageBox::warning(this, "Примечание", "Сперва выберете элементы таблицы.");
        else if (QMessageBox::question(this, QString("Подтверждение удаления"),QString("Вы уверены, что хотите удалить заметку?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            db.usersList.removeAt(idc[0].row());
        db.overwriteUsers();
        setData();

    }
}
