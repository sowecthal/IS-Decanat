#include "databases.h"
#include "dataclasses/user.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTableView>
#include <QStandardItemModel>

DataBases::DataBases()
{
    loadAll();
}

void DataBases::insertUser(QString iLogin, QString iPassword,  int iRole)
{
    QFile outFile("data/Users.bin");

    if (outFile.open(QIODevice::Append))
    {
        QDataStream outStream(&outFile);
        outStream << iLogin << iPassword << iRole;
        qDebug() << "[DataBases::insertUser] Insert: " << iLogin << iPassword << iRole;
    }
    outFile.close();
}

void DataBases::loadAll()
{
    QFile inFile("data/Users.bin");

    if (inFile.open(QIODevice::ReadOnly))
    {
        QDataStream inStream(&inFile);
        while (!inStream.atEnd())
        {
            qDebug() << "[DataBases::loadAll] New iteration";
            QString tmpPassword, tmpLogin;
            int tmpRole;
            inStream >> tmpLogin >> tmpPassword >> tmpRole;

            User newUser(tmpLogin, tmpPassword, tmpRole);
            usersList.push_back(newUser);
        }
    }
    qDebug() << usersList.length();
    inFile.close();
}

int DataBases::findUser(User fUser)
{
    for (int i=0; i<usersList.length();i++)
    {
        qDebug() << "[DataBases::findUser] Pair comparison (" << i+1 << "/" << usersList.length() << "): " << "(L: " << usersList[i].getLogin() << " P: " << usersList[i].getPassword() << ") & (L: "
                 << fUser.getLogin() << " P: " << fUser.getPassword() << ")";
        if (usersList[i].getLogin() == fUser.getLogin())
        {
            qDebug() << "[DataBases::findUser] Login match.";
            if (usersList[i].getPassword() == fUser.getPassword())
            {
                qDebug() << "[DataBases::findUser] Passwords match.";
                return(usersList[i].getRole());
            }
            qDebug() << "[DataBases::findUser] Passwords unmatch.";
        }
        qDebug() << "[DataBases::findUser] Login unmatch.";
    }
    return(-1);
}

int DataBases::getListUserLen()
{
    qDebug() << usersList.length();
    return(usersList.length());
}

User DataBases::getUser(int i)
{
    return(usersList[i]);
}
