#include "grade.h"

Grade::Grade(User *sUser, Discipline *sDiscipline, grades sGrade) :
    mStudent(sUser),
    mDiscipline(sDiscipline)
{
    mValue = sGrade;
}

void Grade::reset(grades newGrade)
{
    mValue = newGrade;
}

Grade::grades Grade::value() const
{
    return(mValue);
}

Grade::grades Grade::getSuitable(grades cValue)
{
    return(grades::BAD);
}
