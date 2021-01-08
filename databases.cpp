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
    //Загрузка из двоичных файлов.
    loadUsers();
    loadDisciplines();
    loadGroups();
    //Устранение несоответсвий в группах.
    coinsideGroups();
}

void DataBases::loadUsers()
{
    QFile inFile("data/Users.bin");

    if (inFile.open(QIODevice::ReadOnly)) {
        QDataStream inStream(&inFile);

        //Пока в потоке есть данные:
        while (!inStream.atEnd()) {
            QString tmpPassword;
            QString tmpLogin;
            int tmpRole;

            inStream >> tmpLogin >> tmpPassword >> tmpRole;

            //Если роль == 0(соответствует студенту) - читаем дальше в поля студента, используем перегруженный конструктор.
            if (tmpRole == 0) {
                //Временные переменные студента.
                QString tmpsSurname;
                QString tmpName;
                QString tmpPatronymic;
                int tmpID;
                int tmpGroupID;
                int tmpLen;
                int tmpGrade;
                int tmpGrant;
                int tmpDisc;
                QList<int> tmpGrades;

                inStream >> tmpID >> tmpGroupID >> tmpsSurname >> tmpName >> tmpPatronymic >> tmpGrant >> tmpLen;

                //Чтение всех оценок.
                for (int i = 0; i < tmpLen; i++) {
                    inStream >> tmpDisc >> tmpGrade;
                    tmpGrades.push_back(tmpDisc);
                    tmpGrades.push_back(tmpGrade);
                }

                User newUser(tmpLogin, tmpPassword, tmpRole, tmpID, tmpGroupID,
                             tmpsSurname, tmpName, tmpPatronymic, tmpGrant, tmpGrades);
                usersList.push_back(newUser);
            } else {
                User newUser(tmpLogin, tmpPassword, tmpRole);
                usersList.push_back(newUser);
            }
        }
    }
    inFile.close();
}

void DataBases::loadDisciplines()
{
    QFile inFile("data/Disciplines.bin");

    if (inFile.open(QIODevice::ReadOnly)) {
        QDataStream inStream(&inFile);

        //Первым читается следующий ID.
        inStream >> nextDisciplineID;

        //Пока в потоке есть данные:
        while (!inStream.atEnd()) {
            QString tmpName;
            int tmpDisciplinesID;
            int tmpForm;
            int tmpLength;
            int tmpGroupID;
            QList <int> tmpGroups;

            inStream >> tmpName >> tmpDisciplinesID >> tmpForm >> tmpLength;

            //Чтение ID групп.
            for (int i = 0; i < tmpLength; i++) {
                inStream >> tmpGroupID;
                tmpGroups.append(tmpGroupID);
            }

            Discipline newDiscipline(tmpName, tmpDisciplinesID, tmpForm, tmpGroups);
            disciplinesList.push_back(newDiscipline); 
        }
    }
}

void DataBases::loadGroups()
{
    QFile inFile("data/Groups.bin");

    if (inFile.open(QIODevice::ReadOnly)) {
        QDataStream inStream(&inFile);

        //Первым читается следующий ID.
        inStream >> nextGroupID;

        //Пока в потоке есть данные:
        while (!inStream.atEnd()) {
            QString tmpNumber;
            int tmpGroupID;
            QList <User*> tmpStudents;
            QList <Discipline*> tmpDisciplines;

            inStream >> tmpGroupID >> tmpNumber;

            for (User &i : usersList) {
                //Если найден студент, прикрепленный к группе - добавляем в список tmpStudents.
                if ((i.getRole() == 0) && (i.mGroupID == tmpGroupID)) {
                    tmpStudents.append(&i);
                }
            }

            for (Discipline &i : disciplinesList) {
                //Если найдена дисциплина с прекрепленной группой - добавляем в список tmpDisciplines.
                if (i.mGroups.contains(tmpGroupID)) {
                    tmpDisciplines.append(&i);
                }
            }
            Group newGroup(tmpGroupID, tmpNumber, tmpStudents, tmpDisciplines);
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
    for (User i : usersList) {
        if ((i.mGroupID != -1) && (i.getRole() == 0)) {
            bool ind = false;
            for (Group j : groupsList) {
                if(i.mGroupID == j.mGroupID) {
                    ind = true;
                    break;
                }
            }
            if (!ind) {
                i.mGroupID = -1;
            }
        }
    }
    for (Discipline i : disciplinesList) {
        QList<int> newGroups;
        for (int j : i.mGroups) {
            bool ind = false;
            for (Group k : groupsList) {
                if(j == k.mGroupID) {
                    ind = true;
                    break;
                }
            }
            if (ind) {
                newGroups.append(j);
            }
        }
        i.mGroups = newGroups;
    }
}

void DataBases::overwriteUsers()
{
    QFile outFile("data/Users.bin");

    if (outFile.open(QIODevice::WriteOnly)) {
        QDataStream outStream(&outFile);

        for (auto &i : usersList) {
            outStream << i.getLogin() << i.getPassword() << i.getRole();

            //Если студент - заносятся поля студента
            if (i.getRole() == 0) {
                outStream << i.mID << i.mGroupID << i.mSurname << i.mName
                          << i.mPatronymic << i.mGrant << i.mGrades.length();
                for (auto &j : i.mGrades) {
                    outStream << j;
                }
            }
        }
    }
    outFile.close();
}

void DataBases::overwriteDisciplines()
{
    QFile outFile("data/Disciplines.bin");

    if (outFile.open(QIODevice::WriteOnly)) {
        QDataStream outStream(&outFile);
        outStream << nextDisciplineID;

        for (auto &i : disciplinesList) {
            outStream << i.mName << i.mDisciplineID << i.mForm << i.mGroups.length();
            for (auto &j : i.mGroups) {
                    outStream << j;
            }
        }
    }
    outFile.close();
}

void DataBases::overwriteGroups()
{
    QFile outFile("data/Groups.bin");

    if (outFile.open(QIODevice::WriteOnly)) {
        QDataStream outStream(&outFile);
        outStream << nextGroupID;
        for (auto &i : groupsList) {
            outStream << i.mGroupID << i.mNumber;
        }
    }
    outFile.close();
}

User *DataBases::findAuthUser(QString fLogin, QString fPassword)
{
    for (int i = 0; i < usersList.length(); i++) {
        if (usersList[i].getLogin() == fLogin) {
            if (usersList[i].getPassword() == fPassword) {
                User *found = &usersList[i];
                return(found);
            }
        }
    }
    User *unfound = new User("", "", -1);
    return(unfound);
}

User *DataBases::findStudent(int fID)
{
    for (User &i : usersList) {
        if (i.mID == fID) return(&i);
    }
}

Group *DataBases::findGroup(int fID)
{
    for (Group &i : groupsList) {
        if (i.mGroupID == fID) return(&i);
    }
    Group *none = new Group(0, "", {}, {});
    return(none);
}

Group *DataBases::findGroupName(QString fName)
{
    for (Group &i : groupsList) {
        if (i.mNumber == fName) return(&i);
    }
    Group *unfound = new Group(0, "", {}, {});
    return(unfound);
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
