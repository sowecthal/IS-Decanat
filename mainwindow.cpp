#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTitle(QString str)
{
    this->setWindowTitle(str);
}

void MainWindow::setMode(int key)
{
    if (key == 0)
    {
        ui->tabWidget->setTabText(0, "Пользователи");
        ui->tabWidget->setTabText(1, "Группы");
        ui->tabWidget->setTabText(2, "Дисциплины");
    }
}
