#include "grade.h"

User someStudent;
Discipline someDiscipline;

Grade::Grade() :
    mStudent(someStudent),
    mDiscipline(someDiscipline)
{
}

Grade::Grade(const User &sStudent, const Discipline &sDiscipline, grades sGrade) :
    mStudent(sStudent),
    mDiscipline(sDiscipline)
{
    mValue = getSuitable(sGrade);
}

void Grade::write(QDataStream &ost)
{
    ost << mStudent.mID << mDiscipline.mDisciplineID << mValue;
}

Grade::grades Grade::getSuitable(grades cValue)
{
    /* Если ф.к. дисциплины "Экзамен", а значение оценки соответствует оценкам
     * за зачёт (равно как и наоборот) - вернуть подходящую оценку
     */
    if (mDiscipline.mForm == Discipline::EXAM) {
        if (cValue == grades::NOPASSED) {
            return(grades::BAD);
        } else {
            if (cValue == grades::PASSED) {
                return(grades::EXCELLENT);
            }
        }
    } else {
        if (mDiscipline.mForm == Discipline::PASS) {
            if (cValue == grades::BAD) {
                return(grades::NOPASSED);
            } else {
                if (cValue == grades::OKAY || cValue == grades::GOOD || cValue == grades::EXCELLENT) {
                    return(grades::PASSED);
                }
            }
        }
    }
    return(cValue);
}

bool Grade::itsMe(int fStudentID, int fDisciplineID)
{
    if (mStudent.mID == fStudentID && mDiscipline.mDisciplineID == fDisciplineID) {
        return(true);
    }
    return(false);
}

bool Grade::belongsDiscipline(int bDisciplineID)
{
    if (mDiscipline.mDisciplineID == bDisciplineID) {
        return(true);
    }
    return(false);
}

bool Grade::belongsStudent(int bStudentID)
{
    if (mStudent.mID == bStudentID) {
        return(true);
    }
    return(false);
}

Grade::grades Grade::find(int fStudentID, int fDisciplineID)
{
    if (itsMe(fStudentID, fDisciplineID)) {
        return(mValue);
    }
    return(grades::NONE);
}

void Grade::reset(grades newGrade)
{
    mValue = getSuitable(newGrade);
}

int Grade::getStudentID()
{
    return(mStudent.mID);
}

int Grade::getDisciplineID()
{
    return(mDiscipline.mDisciplineID);
}

Grade::grades Grade::getValue()
{
    return(mValue);
}
