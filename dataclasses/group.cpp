#include "group.h"

Group::Group(int gGroupID, QString gNumber, QList <User*> gStudents) : mStudents(gStudents)
{
    mGroupID = gGroupID;
    mNumber = gNumber;
}
