#include "databases.h"
#include "dataclasses/user.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>


DataBases::DataBases()
{
    qDebug() << "[ IN DATABASES ]";
    insertUser("admin", "admin", 2);
    loadAll();
}

void DataBases::insertUser(QString iPassword, QString iLogin, int iRole)
{
    qDebug() << "[ IN DATABASES::INSERT ]";
    QFile outFile("data/Users.bin");

    if (outFile.open(QIODevice::WriteOnly))
    {
        QDataStream outStream(&outFile);
        outStream << iLogin << iPassword << iRole;
    }
    outFile.close();
}

void DataBases::loadAll()
{
    qDebug() << "[ IN DATABASES::LOADALL ]";
    QFile inFile("data/Users.bin");

    if (inFile.open(QIODevice::ReadOnly))
    {
        QDataStream inStream(&inFile);
        while (!inStream.atEnd())
        {
            QString tmpPassword, tmpLogin;
            int tmpRole;
            inStream >> tmpLogin >> tmpPassword >> tmpRole;
            qDebug() << tmpLogin << tmpPassword << tmpRole;
            User newUser(tmpLogin, tmpPassword, tmpRole);
            users.push_back(newUser);
        }
    }
    inFile.close();
}

int DataBases::findUser(User fUser)
{
    qDebug() << "[ IN DATABASES::FINDUSER ]";
    for (int i=0; i<users.length();i++)
    {
        qDebug() << "[ IN DATABASES::FINDUSER] user[i]" << users[i].getLogin() << users[i].getPassword();
        qDebug() << "[ IN DATABASES::FINDUSER] fUser" << fUser.getLogin() << fUser.getPassword();
        if (users[i].getLogin() == fUser.getLogin())
        {
            qDebug() << "[ IN DATABASES::FINDUSER {Login = Login} ]";
            if (users[i].getPassword() == fUser.getPassword())
            {
                qDebug() << "[ IN DATABASES::FINDUSER {Password = Password} ]";
                return(users[i].getRole());
            }
        }
    }
    return(-1);
}
