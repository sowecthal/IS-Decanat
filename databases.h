#ifndef DATABASES_H
#define DATABASES_H

#include "dataclasses/user.h"

#include <QString>
#include <QList>


class DataBases
{

public:

    QList<User> *users;

    DataBases();

    void loadAll();

    void insert(QString iPassword, QString iLogin, int iRole);
};
#endif // DATABASES_H
