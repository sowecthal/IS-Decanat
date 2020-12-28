#ifndef DATABASES_H
#define DATABASES_H

#include "dataclasses/user.h"
#include "dataclasses/discipline.h"
#include "dataclasses/group.h"

#include <QString>
#include <QList>
#include <QTableView>

class DataBases
{

public:
    DataBases();

    //! Метод добавления пользователя
    void insertUser(QString iLogin, QString iPassword, int iRole, int sID = -1, int sGroupID = -1, QString sSurname = " ",
                    QString sName = " ", QString sPatronymic = " ", int sGrant = -1, QList<int> sGrades = {});
    //! Поиск пользователя для авторизации
    int findAuthUser(QString fLogin, QString fPassword);
    /* Возвращает значение поля mRole, найденного пользователя;
     * В противном случае, возвращает -1
     */
    //! Поиск студента по id
    User* findStudent(int fID);
    //! Метод перезаписи файла пользоватей
    void overwriteUsers();

    QList<User> usersList;
    QList<Group> groupsList;
    QList<Discipline> disciplinesList;
private:
    void loadUsers();
    void loadGroups();
    void loadDisciplines();
    void printKAL();
};
#endif // DATABASES_H
