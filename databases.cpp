#include "databases.h"
#include "dataclasses/user.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTableView>
#include <QStandardItemModel>

DataBases::DataBases()
{
    qDebug() << "NEW DATABASES";
    loadAll();
}

void DataBases::insertUser(QString iLogin, QString iPassword,  int iRole, int sID, int sGroupID, QString sSurname, QString sName, QString sPatronymic, int sGrant, QList<int> sGrades)
{
    QFile outFile("data/Users.bin");

    if (outFile.open(QIODevice::Append))
    {
        QDataStream outStream(&outFile);
        outStream << iLogin << iPassword << iRole;
        if (iRole == 0)
        {
            qDebug() << "[DataBases::insertUser] Insert: " << iLogin << iPassword << iRole << sID << sGroupID << sSurname << sName << sPatronymic << sGrant << sGrades.length();
            outStream << sID << sGroupID << sSurname << sName << sPatronymic << sGrant << sGrades.length();
            for (int j; j<sGrades.length(); j++)
            {
                outStream << sGrades[j];
            }
        }
        //qDebug() << "[DataBases::insertUser] Insert: " << iLogin << iPassword << iRole;
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
            QString tmpPassword, tmpLogin;
            int tmpRole;
            inStream >> tmpLogin >> tmpPassword >> tmpRole;
            if (tmpRole == 0)
            {
                QString tmpsSurname, tmpName, tmpPatronymic;
                int tmpID, tmpGroupID, tmpLen, tmpGrade, tmpGrant, tmpDisc;
                QList<int> tmpGrades;
                //, int sGroupID, QString sName,
                //, bool sGrant, QList<int> sGrades
                inStream >> tmpID >> tmpGroupID >> tmpsSurname >> tmpName >> tmpPatronymic >> tmpGrant >> tmpLen;
                for (int i; i<tmpLen; i++)
                {
                    inStream >> tmpDisc;
                    inStream >> tmpGrade;
                    tmpGrades.push_back(tmpDisc);
                    tmpGrades.push_back(tmpGrade);
                }

                User newUser(tmpLogin, tmpPassword, tmpRole, tmpID, tmpGroupID,
                             tmpsSurname, tmpName, tmpPatronymic, tmpGrant, tmpGrades);
                usersList.push_back(newUser);
            }
            else
            {
                User newUser(tmpLogin, tmpPassword, tmpRole);
                usersList.push_back(newUser);
            }

        }
    }

    inFile.close();
}

int DataBases::findAuthUser(QString fLogin, QString fPassword)
{
    for (int i=0; i<usersList.length();i++)
    {
        qDebug() << "[DataBases::findUser] Pair comparison (" << i+1 << "/" << usersList.length() << "): " << "(L: " << usersList[i].getLogin() << " P: " << usersList[i].getPassword() << ") & (L: "
                 << fLogin << " P: " << fPassword << ")";
        if (usersList[i].getLogin() == fLogin)
        {
            qDebug() << "[DataBases::findUser] Login match.";
            if (usersList[i].getPassword() == fPassword)
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
