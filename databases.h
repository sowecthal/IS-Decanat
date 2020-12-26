#ifndef DATABASES_H
#define DATABASES_H

#include "dataclasses/user.h"

#include <QString>
#include <QList>
#include <QTableView>

class DataBases
{

public:
    QList<User> usersList;

    DataBases();

    void loadAll();

    void insertUser(QString iLogin, QString iPassword, int iRole, int sID = -1, int sGroupID = -1, QString sSurname = " ",
                    QString sName = " ", QString sPatronymic = " ", int sGrant = -1, QList<int> sGrades = {});

    //! Поиск пользователя для авторизации
    int findAuthUser(QString fLogin, QString fPassword);
    /* Возвращает значение поля mRole, найденного пользователя;
     * В противном случае, возвращает -1
     */

};
#endif // DATABASES_H
