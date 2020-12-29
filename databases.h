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

    //! Поиск по id
    User* findStudent(int fID);
    Group* findGroup(int fID);

    //! Поиск по имени
    Group* findGroupName(QString fName);

    //! Перезапись файлов
    void overwriteUsers();
    void overwriteDisciplines();
    void overwriteGroups();

    //! Перезагрузка
    void reloadGroups();

    //! Получение доступного id
    int getNextDisciplineID();
    int getNextGroupID();

    //! Инкремент id
    void incrementNextDisciplineID();
    void incrementNextGroupID();

    //! Сопоставление групп со студентами и дисциплинами
    void coinsideGroups();

    //! Списки объектов
    QList<User> usersList;
    QList<Group> groupsList;
    QList<Discipline> disciplinesList;

private:
    //! Загрузка файлов
    void loadUsers();
    void loadGroups();
    void loadDisciplines();

    //! Поля следующих id
    int nextDisciplineID = 0;
    int nextGroupID = 0;
};
#endif // DATABASES_H
