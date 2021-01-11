#ifndef GRADE_H
#define GRADE_H

#include "user.h"
#include "discipline.h"

#include <QDataStream>

class Grade
{
public:
    enum grades {NONE, NOPASSED, PASSED, BAD, OKAY, GOOD, EXCELLENT};
    //! Конструктор по умолчанию
    Grade();
    //! Конструктор оценки
    Grade(const User &sStudent, const Discipline &sDiscipline, grades sGrade);
    //! Устанавливает новое значение
    void reset(grades newGrade);
    //! Запись в поток
    void write(QDataStream &ost);
    //! Возвращает оценку студента по дисциплине, если ID совпали
    Grade::grades find(int fStudentID, int fDisciplineID);
    //! Возвращает True, если совпал ID дисциплины
    bool belongsDiscipline(int fDisciplineID);
    //! Возвращает True, если совпал ID студента
    bool belongsStudent(int fStudentID);
    //! Возвращает True, если совпали ID
    bool itsMe(int fStudentID, int fDisciplineID);
private:
    const User &mStudent;
    const Discipline &mDiscipline;
    Grade::grades mValue;

    //! Проверяет соответсвие дисциплыны и оценки, возвращает валидное  значение
    grades getSuitable(grades cValue);
};

#endif // GRADE_H
