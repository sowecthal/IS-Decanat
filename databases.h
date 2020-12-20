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

    void insertUser(QString iLogin, QString iPassword, int iRole);

    int findUser(User fUser);

};
#endif // DATABASES_H
