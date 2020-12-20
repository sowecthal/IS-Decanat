#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <QDebug>
#include <QStandardItemModel>

MainWindow::MainWindow(DataBases &sDB, QWidget *parent)  : db(sDB),
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setMovable(false);
    ui->toolBar->orientationChanged(Qt::Vertical);
    ui->lineFind->setPlaceholderText("Поиск по таблице");
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
    QStandardItemModel* model = new QStandardItemModel(db.usersList.length(), 3, this);
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

void MainWindow::on_lineEdit_returnPressed()
{
    qDebug() << "[MainWindow::on_lineEdit_returnPressed]";
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (mMode == 2)
    {
        if (arg1 == "Пользователи")
        {
            setData();
        }
    }
}
