#include "databases.h"
#include "dataclasses/user.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>


DataBases::DataBases()
{
    qDebug() << "[ IN DATABASES ]";
    insert("admin", "abmin", 2);
    loadAll();
}

void DataBases::insert(QString iPassword, QString iLogin, int iRole)
{
    qDebug() << "[ IN DATABASES::INSERT ]";
    QFile outFile(":/data/Users.isd");

    if (outFile.open(QIODevice::ReadWrite))
    {
        qDebug() << "[ IN DATABASES::INSERT [ outFile.open(QIODevice::WriteOnly) ] ]";
        QDataStream outStream(&outFile);
        outStream << iLogin << iPassword << iRole;
    }
    outFile.close();
}

void DataBases::loadAll()
{
    qDebug() << "[ IN DATABASES::LOADALL ]";
    QFile inFile(":/data/Users.isd");

    if (inFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "[ IN DATABASES::LOADALL [ if (inFile.open(QIODevice::ReadOnly) ] ]";
        QDataStream inStream(&inFile);
        while (!inStream.atEnd())
        {
            QString tmpPassword, tmpLogin;
            int tmpRole;
            inStream >> tmpLogin >> tmpPassword >> tmpRole;
            User newUser(tmpLogin, tmpPassword, tmpRole);
            users->append(newUser);
            //qDebug() << tmpLogin << tmpPassword << tmpRole;
        }
    }
}

