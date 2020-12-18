#include "mainwindow.h"
#include "authwindow.h"
#include "databases.h"

#include <QApplication>
#include <QDialog>
#include <QDebug>

//char *authorization(char)

int main(int argc, char *argv[])
{
    qDebug() << "[ IN MAIN ]";
    QApplication a(argc, argv);
    MainWindow w;
    AuthWindow aw;
    DataBases db;

    if (aw.exec() == QDialog::Accepted)
    {  
        w.show();
        w.setMode(aw.Role);
        w.setTitle(aw.getLineLogin());
    }

    return a.exec();
}


