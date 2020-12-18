#ifndef DATABASES_H
#define DATABASES_H

#include <QString>
#include <QList>

class DataBases
{
    struct  user {
        QString password, login;
        int role;
        //! 0 - Учащийся
        //! 1 - Диспетчер деканата
        //! 2 - Администратор ИС

        user create(QString cPassword, QString cLogin, int cRole);
    };

public:

    QList<user> *Users;

    DataBases();

    void loadAll();

    void insert(QString iPassword, QString iLogin, int iRole);
};

