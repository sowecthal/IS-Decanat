#include "databases.h"
#include "dataclasses/user.h"
#include "dataclasses/group.h"
#include "dataclasses/discipline.h"
#include "dataclasses/grade.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>

DataBases::DataBases()
{
    //Загрузка из двоичных файлов.
    loadUsers();
    loadDisciplines();
    loadGrades();
    loadGroups();
    //Устранение несоответсвий.
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
            User::roles tmpRole;

            inStream >> tmpLogin >> tmpPassword >> tmpRole;

            //Если роль == 0(соответствует студенту) - читаем дальше в поля студента, используем перегруженный конструктор.
            if (tmpRole == User::roles::STUDENT) {
                //Временные переменные студента.
                QString tmpsSurname;
                QString tmpName;
                QString tmpPatronymic;
                int tmpID;
                int tmpGroupID;
                User::grants tmpGrant;

                inStream >> tmpID >> tmpGroupID >> tmpsSurname >> tmpName >> tmpPatronymic >> tmpGrant;

                User newUser(tmpLogin, tmpPassword, tmpRole, tmpID, tmpGroupID,
                             tmpsSurname, tmpName, tmpPatronymic, tmpGrant);
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
            Discipline::forms tmpForm;
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
    inFile.close();
}

void DataBases::loadGrades()
{
    QFile inFile("data/Grades.bin");

    if (inFile.open(QIODevice::ReadOnly)) {
        QDataStream inStream(&inFile);

        //Пока в потоке есть данные:
        while (!inStream.atEnd()) {
            int tmpStudentID;
            int tmpDisciplineID;
            Grade::grades tmpValue;

            inStream >> tmpStudentID >> tmpDisciplineID >> tmpValue;

            createGrade(tmpStudentID, tmpDisciplineID, tmpValue);
        }
    }
    inFile.close();
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
                if ((i.getRole() == User::roles::STUDENT) && (i.mGroupID == tmpGroupID)) {
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

void DataBases::reloadAll()
{
    usersList.clear();
    disciplinesList.clear();

    loadUsers();
    loadDisciplines();

    reloadGroups();
    reloadGrades();
}

void DataBases::reloadGrades()
{
    gradesList.clear();
    loadGrades();
}

void DataBases::reloadGroups()
{
    groupsList.clear();
    loadGroups();
}

void DataBases::coinsideGroups()
{
    for (User &i : usersList) {
        if ((i.mGroupID != -1) && (i.getRole() == User::roles::STUDENT)) {
            bool ind = false;
            for (Group &j : groupsList) {
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
    for (Discipline &i : disciplinesList) {
        QList<int> newGroups;
        for (int &j : i.mGroups) {
            bool ind = false;
            for (Group &k : groupsList) {
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

void DataBases::overwriteAll()
{
    overwriteUsers();
    overwriteDisciplines();
    overwriteGroups();
}

void DataBases::overwriteUsers()
{
    QFile outFile("data/Users.bin");

    if (outFile.open(QIODevice::WriteOnly)) {
        QDataStream outStream(&outFile);

        for (auto &i : usersList) {
            outStream << i.getLogin() << i.getPassword();

            // Запись роли.

            outStream << i.getRole();

            if (i.getRole() == User::roles::STUDENT) {
                //Для студента, помимо роли, записываются поля студента;
                outStream << i.mID << i.mGroupID << i.mSurname << i.mName
                          << i.mPatronymic << i.mGrant;
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

void DataBases::overwriteGrades()
{
    QFile outFile("data/Grades.bin");

    if (outFile.open(QIODevice::WriteOnly)) {
        QDataStream outStream(&outFile);

        for (Grade &nowGrade : gradesList) {
            nowGrade.write(outStream);
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
    User *unfound = new User("", "", User::roles::UNKNOWN);
    return(unfound);
}

User *DataBases::findStudent(int fID)
{
    for (User &found : usersList) {
        if (found.mID == fID) return(&found);
    }
    User *unfound = new User("", "", User::roles::UNKNOWN);
    return(unfound);
}

Group *DataBases::findGroup(int fID)
{
    for (Group &found : groupsList) {
        if (found.mGroupID == fID) return(&found);
    }
    Group *unfound = new Group(0, "", {}, {});
    return(unfound);
}

Group *DataBases::findGroupName(QString fName)
{
    for (Group &i : groupsList) {
        if (i.mNumber == fName) return(&i);
    }
    Group *unfound = new Group(0, "", {}, {});
    return(unfound);
}

void DataBases::createGrade(int cStudentID, int cDisciplineID, Grade::grades cGrade)
{
    User *tmpStudent  = nullptr;
    Discipline *tmpDiscipline = nullptr;

    for (User &nowUser : usersList) {
        if (nowUser.mID == cStudentID) {
            tmpStudent = &nowUser;
            break;
        }
    }
    for (Discipline &nowDiscipline : disciplinesList) {
        if (nowDiscipline.mDisciplineID == cDisciplineID) {
            tmpDiscipline = &nowDiscipline;
            break;
        }
    }

    if (tmpStudent != nullptr && tmpDiscipline != nullptr) {
        Grade newGrade(*tmpStudent, *tmpDiscipline, cGrade);
        gradesList.append(newGrade);
    }
}

Grade::grades DataBases::findGrade(int fStudentID, int fDisciplineID)
{
    for (Grade &nowGrade : gradesList) {
        if (nowGrade.find(fStudentID, fDisciplineID) != Grade::NONE) {
            return(nowGrade.find(fStudentID, fDisciplineID));
        }
    }
    return(Grade::NONE);
}

void DataBases::resetGrade(int rStudentID, int rDisciplineID, Grade::grades rGrade)
{
    for (Grade &nowGrade : gradesList) {
        if (nowGrade.itsMe(rStudentID, rDisciplineID)) {
            nowGrade.reset(rGrade);
            return;
        }
    }
}

void DataBases::deleteGrade(int dStudentID, int dDisciplineID)
{
    for (int index = 0; index < gradesList.length(); index++) {
        if (gradesList[index].itsMe(dStudentID, dDisciplineID)) {
            gradesList.removeAt(index);
            return;
        }
    }
}

void DataBases::deleteGradesByDiscipine(int dDisciplineID)
{
    QMutableListIterator<Grade> i(gradesList);
    while(i.hasNext()) {
        Grade nowGrade = i.next();
        if (nowGrade.belongsDiscipline(dDisciplineID)) {
           i.remove();
        }
    }
}

void DataBases::deleteGradesByStudent(int dStudentID)
{
    QMutableListIterator<Grade> i(gradesList);
    while(i.hasNext()) {
        Grade nowGrade = i.next();
        if (nowGrade.belongsStudent(dStudentID)) {
           i.remove();
        }
    }
}

int DataBases::getNextDisciplineID()
{
    return(nextDisciplineID + 1);
}

int DataBases::getNextGroupID()
{
    return(nextGroupID + 1);
}

void DataBases::incrementNextDisciplineID()
{
    nextDisciplineID++;
}

void DataBases::incrementNextGroupID()
{
    nextGroupID++;
}
