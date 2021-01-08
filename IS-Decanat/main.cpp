#include "mainwindow.h"
#include "authwindow.h"
#include "databases.h"

#include <QApplication>
#include <QDialog>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QDir().mkdir("data");
    QApplication a(argc, argv);

    DataBases* db = new DataBases;
    MainWindow mw(*db);
    AuthWindow aw(*db);

    if (aw.exec() == QDialog::Accepted)
    {
        mw.show();
        mw.setUser(aw.authUser);
    }
    return a.exec();
}


