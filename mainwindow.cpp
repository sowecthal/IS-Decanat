#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <QDebug>
#include <QStandardItemModel>

MainWindow::MainWindow(DataBases sDB, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    db = &sDB;
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
    qDebug() << db->getListUserLen();
    QStandardItemModel model(db->getListUserLen(), 3);
     qDebug() << "Y";
    model.setHorizontalHeaderItem(0, new QStandardItem(QString("Логин")));
    model.setHorizontalHeaderItem(1, new QStandardItem(QString("Пароль")));
    model.setHorizontalHeaderItem(2, new QStandardItem(QString("Роль")));
    qDebug() << "Y";
    for(int i = 0; i < db->getListUserLen() ; i++)
    {
        User nowUser = db->getUser(i);
        model.setItem(i,0,new QStandardItem(QString(nowUser.getLogin())));
        model.setItem(i,1,new QStandardItem(QString(nowUser.getPassword())));
        model.setItem(i,2,new QStandardItem(QString(nowUser.getRole())));
    }
    qDebug() << "Y";
    ui->tableView->setModel(&model);
    qDebug() << "Y";
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
