#include "group.h"

Group::Group(int gGroupID, QString gNumber, QList <User*> gStudents, QList <Discipline*> gDisciplines) :
    mStudents(gStudents),
    mDisciplines(gDisciplines)
{
    mGroupID = gGroupID;
    mNumber = gNumber;
}
