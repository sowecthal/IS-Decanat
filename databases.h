#ifndef DATABASES_H
#define DATABASES_H

#include "dataclasses/user.h"

#include <QString>
#include <QList>


class DataBases
{

public:

    QList<User> users;

    DataBases();

    void loadAll();

    void insertUser(QString iPassword, QString iLogin, int iRole);

    int findUser(User fUser);
};
#endif // DATABASES_H
