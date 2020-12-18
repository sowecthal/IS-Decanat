#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "[ IN MAINWINDOW ]";
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
    ui->toolBar->setMovable(false);
    ui->toolBar->orientationChanged(Qt::Vertical);
}
