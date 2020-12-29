#include "databases.h"
#include "dataclasses/user.h"
#include "dataclasses/group.h"
#include "dataclasses/discipline.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTableView>
#include <QStandardItemModel>

DataBases::DataBases()
{
    loadUsers();
    loadDisciplines();
    loadGroups();
    coinsideGroups();
}

void DataBases::loadUsers()
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
                qDebug() << "[DataBases::loadUsers] Load student: " << tmpLogin << tmpPassword << tmpRole << tmpID << tmpGroupID <<
                        tmpsSurname << tmpName << tmpPatronymic << tmpGrant;
                usersList.push_back(newUser);
            }
            else
            {
                User newUser(tmpLogin, tmpPassword, tmpRole);
                qDebug() << "[DataBases::loadUsers] Load user: " << tmpLogin << tmpPassword << tmpRole;
                usersList.push_back(newUser);
            }
        }
        qDebug() << "[DataBases::loadUsers] End. " << usersList.length();
    }
    inFile.close();
}

void DataBases::loadDisciplines()
{
    QFile inFile("data/Disciplines.bin");

    if (inFile.open(QIODevice::ReadOnly))
    {
        QDataStream inStream(&inFile);
        inStream >> nextDisciplineID;
        while (!inStream.atEnd())
        {
            QString tmpName;
            int tmpDisciplinesID, tmpForm, tmpLength, tmpGroupID;
            inStream >> tmpName >> tmpDisciplinesID >> tmpForm >> tmpLength;

            QList <int> groups;
            for (int i; i<tmpLength; i++)
            {
               inStream >> tmpGroupID;
               groups.append(tmpGroupID);
            }
            Discipline newDiscipline(tmpName, tmpDisciplinesID, tmpForm, groups);
            disciplinesList.push_back(newDiscipline);
            qDebug() << "[DataBases::loadDisciplines] Load discipline: " << tmpName << tmpDisciplinesID << tmpForm;
        }
        qDebug() << "[DataBases::loadDisciplines] End. " << disciplinesList.length();
    }
}

void DataBases::loadGroups()
{
    QFile inFile("data/Groups.bin");

    if (inFile.open(QIODevice::ReadOnly))
    {
        QDataStream inStream(&inFile);
        inStream >> nextGroupID;
        while (!inStream.atEnd())
        {
            QString tmpNumber;
            int tmpGroupID;

            inStream >> tmpGroupID >> tmpNumber;

            QList <User*> GroupsStudents;
            for (User &i : usersList)
            {
                //Если найден студент, прикрепленный к группе - добавляем в список студентов
                if (i.getRole() == 0 && i.mGroupID == tmpGroupID)
                {
                    GroupsStudents.append(&i);
                }
            }
            QList <Discipline*> GroupsDisciplines;
            for (Discipline &i : disciplinesList)
            {
                //Если найдена дискиплина с прекрепленной группой - добавляем в список
                if (i.mGroups.contains(tmpGroupID))
                {
                    GroupsDisciplines.append(&i);
                }
            }
            qDebug() << "[DataBases::loadGroups] Load group: " << tmpGroupID << tmpNumber;
            Group newGroup(tmpGroupID, tmpNumber, GroupsStudents, GroupsDisciplines);
            groupsList.push_back(newGroup);
        }
    }
    inFile.close();
}

void DataBases::reloadGroups()
{
    groupsList.clear();
    loadGroups();
}

void DataBases::coinsideGroups()
{
    for (User i : usersList)
    {
        if (i.mGroupID != -1 && i.getRole() == 0)
        {
            bool ind = false;
            for (Group j : groupsList)
            {
                if(i.mGroupID == j.mGroupID)
                {
                    ind = true;
                     break;
                }
            }
            if (!ind)
            {
                i.mGroupID = -1;
                qDebug() << "[DataBases::coinsideGroups] Fix for " << i.getLogin();
            }
        }
    }
    for (Discipline i : disciplinesList)
    {
        QList<int> newGroups;
        for (int j : i.mGroups)
        {
            bool ind = false;
            for (Group k : groupsList)
            {
                if(j == k.mGroupID)
                {
                    ind = true;
                    break;
                }
            }
            if (ind) newGroups.append(j);
            else qDebug() << "[DataBases::coinsideGroups] Fix for " << i.mName;
        }
        i.mGroups = newGroups;
    }
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

void DataBases::overwriteUsers()
{
    qDebug() << "[DataBases::overwriteUsers]";
    QFile outFile("data/Users.bin");

    if (outFile.open(QIODevice::WriteOnly))
    {
        QDataStream outStream(&outFile);
        qDebug() << "[DataBases::overwriteUsers] usersList.length(): " << usersList.length();
        for (auto &i : usersList)
        {
            outStream << i.getLogin() << i.getPassword() << i.getRole();
            qDebug() << "[DataBases::overwriteUsers] Now: " << i.getLogin();
            //Если студент - заносятся поля студента
            if (i.getRole() == 0)
            {
                outStream << i.mID << i.mGroupID << i.mSurname << i.mName
                          << i.mPatronymic << i.mGrant << i.mGrades.length();
                for (auto &j : i.mGrades)
                {
                    outStream << j;
                }
            }
        }
    }
    outFile.close();
}

void DataBases::overwriteDisciplines()
{
    qDebug() << "[DataBases::overwriteDisciplines]";
    QFile outFile("data/Disciplines.bin");

    if (outFile.open(QIODevice::WriteOnly))
    {
        QDataStream outStream(&outFile);
        outStream << nextDisciplineID;
        qDebug() << "[DataBases::overwriteUsers] disciplinesList.length(): " << disciplinesList.length();
        for (auto &i : disciplinesList)
        {
            outStream << i.mName << i.mDisciplineID << i.mForm << i.mGroups.length();
            for (auto &j : i.mGroups)
            {
                    outStream << j;
            }
        }
    }
    outFile.close();
}

void DataBases::overwriteGroups()
{
    QFile outFile("data/Groups.bin");

    if (outFile.open(QIODevice::WriteOnly))
    {
        QDataStream outStream(&outFile);
        outStream << nextGroupID;
        for (auto &i : groupsList)
        {
            outStream << i.mGroupID << i.mNumber;
        }
    }
    outFile.close();
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

User* DataBases::findStudent(int fID)
{
    for (User &i : usersList)
    {
        if (i.mID == fID) return(&i);
    }
}

Group* DataBases::findGroup(int fID)
{
    for (Group &i : groupsList)
    {
        if (i.mGroupID == fID) return(&i);
    }
    Group* none = new Group(0, "", {}, {});
    return(none);
}

Group* DataBases::findGroupName(QString fName)
{
    for (Group &i : groupsList)
    {
        if (i.mNumber == fName) return(&i);
    }
    Group* none = new Group(0, "", {}, {});
    return(none);
}

int DataBases::getNextDisciplineID()
{
    return(nextDisciplineID + 1);
}

int DataBases::getNextGroupID()
{
    return(nextDisciplineID + 1);
}

void DataBases::incrementNextDisciplineID()
{
    nextDisciplineID++;
}

void DataBases::incrementNextGroupID()
{
    nextDisciplineID++;
}
