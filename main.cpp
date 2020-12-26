#include "mainwindow.h"
#include "authwindow.h"
#include "databases.h"

#include <QApplication>
#include <QDialog>
#include <QDebug>
#include <QDir>

//char *authorization(char)

int main(int argc, char *argv[])
{
    qDebug() << "[ IN MAIN ]";
    QDir().mkdir("data");
    QApplication a(argc, argv);

    DataBases* db = new DataBases;
    MainWindow w(*db);
    AuthWindow aw(*db);

    if (aw.exec() == QDialog::Accepted)
    {
        w.show();

        w.setMode(aw.mode);
    }

    return a.exec();
}


