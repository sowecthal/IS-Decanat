#include "databases.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>


DataBases::DataBases()
{
    insert("admin", "abmin", 2);
    loadAll();
}

void DataBases::insert(QString iPassword, QString iLogin, int iRole)
{
    QFile outFile(":/data/Users.isd");

    if (outFile.open(QIODevice::WriteOnly))
    {
        QDataStream outStream(&outFile);
        outStream << iLogin << iPassword << iRole;
    }
    outFile.close();
}

void DataBases::loadAll()
{
    QString tmpPassword, tmpLogin;
    int tmpRole;

    QFile inFile(":/data/Users.isd");

    if (inFile.open(QIODevice::ReadOnly))
    {
        QDataStream inStream(&inFile);
        while (!inStream.atEnd())
        {
            QString tmpPassword, tmpLogin;
            int tmpRole;
            inStream >> tmpLogin >> tmpPassword >> tmpRole;
        }

    }


    qDebug() << tmpPassword;
}
