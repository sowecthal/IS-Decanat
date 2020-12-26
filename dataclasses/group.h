#ifndef GROUP_H
#define GROUP_H

#include "dataclasses/user.h"

#include <QString>
#include <QList>

class group
{
public:
    group(int gGroupID, QString gNumber, QList <User*> gStudents);

    int mGroupID;
    QString mNumber;
    QList <User*> mStudents;
};

#endif // GROUP_H
