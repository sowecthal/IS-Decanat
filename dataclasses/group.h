#ifndef GROUP_H
#define GROUP_H

#include "dataclasses/user.h"
#include "dataclasses/discipline.h"

#include <QString>
#include <QList>

class Group
{
public:
    Group(int gGroupID, QString gNumber, QList <User*> gStudents, QList <Discipline*> gDisciplines);

    int mGroupID;
    QString mNumber;
    QList <User*> mStudents;
    QList <Discipline*> mDisciplines;
};

#endif // GROUP_H
