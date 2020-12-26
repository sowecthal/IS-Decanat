#include "group.h"

group::group(int gGroupID, QString gNumber, QList <User&> gStudents) : mStudents(gStudents)
{
    mGroupID = gGroupID;
    mNumber = gNumber;
}
