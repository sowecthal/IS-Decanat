#ifndef USERSTABLE_H
#define USERSTABLE_H


#include <QAbstractTableModel>

class UsersTable : public QAbstractTableModel
{
public:
    UsersTable();
private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

};

#endif // USERSTABLE_H
