#include "userstable.h"

UsersTable::UsersTable()
{

}

int UsersTable::rowCount(const QModelIndex &parent) const
{
    return 5; // сделаем фиксированно 5 строк в таблице
    //если вы станете использовать скажем QList, то пишите return list.size();
}
int UsersTable::columnCount(const QModelIndex &parent) const
{
    return 4; // количество колонок сделаем также фиксированным
}

