#include "mainwindow.h"
#include "authwindow.h"

#include <QApplication>
#include <QDialog>

//char *authorization(char)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AuthWindow aw;
    if (aw.exec() == QDialog::Accepted)
    {  
        w.show();
        w.setMode(aw.Role);
        w.setTitle(aw.getLineLogin());
    }

    return a.exec();
}


