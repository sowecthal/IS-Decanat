#include "discipline.h"

Discipline::Discipline(QString sName, int sDisciplinesID, forms sForm, QList<int> sGroups)
{
    mDisciplineID = sDisciplinesID;
    mName = sName;
    mForm = sForm;
    mGroups = sGroups;
}
